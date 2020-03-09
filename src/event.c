#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "err.h"
#include "msg.h"

#define BUF_SIZE 1024

/* If event occured on server, handel the server event. */
void server_event(int server_fd, fd_set* fds) {

    // Init the client address and socket
    struct sockaddr_un client_addr;
    int client_fd;
    int client_len = sizeof(client_addr);

    // Accept the client
    client_fd = accept(
        server_fd,
        (struct sockaddr *)&client_addr,
        (socklen_t *)&client_len);

    // If the client fd is valid, register to fds
    if (client_fd < 0)
        accept_error(server_fd);
    else {
        FD_SET(client_fd, fds);
        msg_accept(client_fd);
    }
}

void sxhkd_event(int pipe_fd) {
    char msg[BUF_SIZE];
    memset(&msg, 0x00, BUF_SIZE);
    int msglen = read(pipe_fd, msg, BUF_SIZE-1);

    if (msglen <= 0)
        read_error(pipe_fd);

    msg_sxhkd(pipe_fd, msg);

    for (int ifd = 3; ifd < FD_SETSIZE; ifd++)
        send(ifd, msg, strlen(msg), MSG_NOSIGNAL);
}

/* If event occured on the clients, handle the client event. */
void client_event(int client_fd, fd_set* fds) {
    char msg[BUF_SIZE];
    memset(&msg, 0x00, BUF_SIZE);
    int msglen = read(client_fd, msg, BUF_SIZE-1);

    if (msglen < 0)
        read_error(client_fd);

    if (msglen == 0) {
        close(client_fd);
        FD_CLR(client_fd, fds);
        msg_close(client_fd);
    }
}
