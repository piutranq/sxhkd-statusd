#include <stddef.h>
#include <sys/select.h>

#include "err.h"
#include "event.h"
#include "init.h"
#include "config.h"

int main(int argc, char** argv) {
    config_init(argc, argv);

    /* Init the fd set */
    fd_set active_fds;
    FD_ZERO(&active_fds);

    /* Init the sxhkd pipe and register to fdset */
    int sxhkd_fd = open_pipe(config_sxhkd_path(), &active_fds);
    int server_fd = init_server(config_server_path(), &active_fds);

    while (1) {
        fd_set copied_fds = active_fds;

        if (select(FD_SETSIZE, &copied_fds, NULL, NULL, NULL) < 0)
            select_error();

        for (int ifd = 3; ifd < FD_SETSIZE; ++ifd)
        if (FD_ISSET(ifd, &copied_fds)) {
            if (ifd == server_fd)
                server_event(server_fd, &active_fds);
            else if (ifd == sxhkd_fd)
                sxhkd_event(sxhkd_fd);
            else
                client_event(ifd, &active_fds);
        }
    }
}
