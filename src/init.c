#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "err.h"
#include "msg.h"

/* Open the sxhkd status pipe. return is the pipe fd */
int open_pipe(char* path, fd_set* fds) {

    // Open the pipe
    int fd = open(path, O_RDONLY);
    if (fd < 0) open_error(path);

    // Lock the pipe fd, assure the single process for the pipe.
    if (flock(fd, LOCK_EX | LOCK_NB) != 0)
        flock_error(path);

    // Register the pipe fd to fd set
    FD_SET(fd, fds);

    msg_open_pipe(fd, path);
    return fd;
}

/* Init the server socket. return is the server socket fd */
int init_server(char* path, fd_set* fds) {

    // Unlink pre-used socket path
    if (access(path, F_OK) == 0) unlink(path);

    // Init the address
    struct sockaddr_un addr;
    memset(&addr, 0x00, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, path);

    // Init the socket fd
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0)
        socket_error();

    // Bind the address to the socket fd
    if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
        bind_error(path);

    // Register the socket fd to fd set
    FD_SET(fd, fds);

    // Listen
    if (listen(fd, 5) < 0)
        listen_error();

    msg_init_server(fd, path);
    return fd;
}
