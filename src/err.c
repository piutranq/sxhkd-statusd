#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <config.h>

void print_errno() {
    fprintf(stderr, "%s (errno: %d)\n", strerror(errno), errno);
}

void err_exit(char* msg) {
    if (check_log_level(LOG_LEVEL_ERROR) == true) {
        fprintf(stderr, "%s\n", msg);
        print_errno();
    }
    exit(EXIT_FAILURE);
}

void open_error(char* path) {
    if (check_log_level(LOG_LEVEL_ERROR) == true) {
        fprintf(stderr,
            "Failed to open the file \"%s\"\n", path);
        print_errno();
    }
    exit(EXIT_FAILURE);
}


void flock_error(char* path) {
    if (check_log_level(LOG_LEVEL_ERROR) == true) {
        fprintf(stderr,
            "Failed to lock the file \"%s\"\n", path);
        if (errno == EAGAIN)
            fprintf(stderr,
                "Is the sxhkd-statusd already running for the status pipe?\n");
        else print_errno();
    }
    exit(EXIT_FAILURE);
}

void socket_error() {
    if (check_log_level(LOG_LEVEL_ERROR) == true) {
        fprintf(stderr,
            "Failed to create the socket\n");
        print_errno();
    }
    exit(EXIT_FAILURE);
}

void bind_error(char* path) {
    if (check_log_level(LOG_LEVEL_ERROR) == true) {
        fprintf(stderr,
            "Failed to bind the path to the socket \"%s\"\n", path);
        print_errno();
    }
    exit(EXIT_FAILURE);
}

void listen_error() {
    if (check_log_level(LOG_LEVEL_ERROR) == true) {
        fprintf(stderr,
            "failed to listen\n");
        print_errno();
    }
    exit(EXIT_FAILURE);
}

void accept_error(int fd) {
    if (check_log_level(LOG_LEVEL_ERROR) == true) {
        fprintf(stderr,
            "Failed to accept client on the server fd[%d]\n", fd);
    }
    print_errno();
}

void read_error(int fd) {
    if (check_log_level(LOG_LEVEL_ERROR) == true) {
        fprintf(stderr,
            "Failed to read the message from the fd[%d]\n", fd);
        print_errno();
    }
    exit(EXIT_FAILURE);
}

void select_error() {
    if (check_log_level(LOG_LEVEL_ERROR) == true) {
        fprintf(stderr,
            "Failed to select() the fds");
        print_errno();
    }
    exit(EXIT_FAILURE);
}
