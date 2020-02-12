#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"

void msg_open_pipe(int fd, char* path) {
    if (check_log_level(LOG_LEVEL_INFO))
        fprintf(stderr,
            "The sxhkd pipe \"%s\" has open as fd[%d]\n", path, fd);
}

void msg_init_server(int fd, char* path) {
    if (check_log_level(LOG_LEVEL_INFO))
        fprintf(stderr,
            "The server socket has initialized at \"%s\", as fd[%d]\n",
            path, fd);
}

void msg_accept(int fd) {
    if (check_log_level(LOG_LEVEL_INFO))
        fprintf(stderr, "new client accepted as fd[%d]\n", fd);
}

void msg_sxhkd(int fd, char* msg) {
    if (check_log_level(LOG_LEVEL_VERBOSE))
        fprintf(stderr, "sxhkd event from fd[%d]: %s", fd, msg);
}

void msg_close(int fd) {
    if (check_log_level(LOG_LEVEL_INFO))
        fprintf(stderr, "client fd[%d] has closed\n", fd);
}

void msg_help(char* pname) {
    printf(
"%s\n"
"    The daemon redirects sxhkd status from named pipe to unix domain socket\n"
"    for accessing from multiple clients.\n"
"\n"
"Usage:\n"
"    %s [options] [source]\n"
"\n"
"source:\n"
"    The sxhkd status pipe to read.\n"
"    Make sure the sxhkd-statusd is the only process is reading the pipe.\n"
"\n"
"    The clients can access sxhkd-statusd by connect to\n"
"    \"[source].sxhkd-statusd\"\n"
"\n"
"options:\n"
"    [--help|-h]\n"
"        Show this help message and exit.\n"
"\n"
"    [--log|-l]\n"
"        Set log level as following argument. The default value is \"info\".\n"
"\n"
"        error: Log only the error messages.\n"
"        info: Log the error messages and some additional information.\n"
"            (eg. open/closing file descriptor)\n"
"        verbose: Log more information.\n"
"            (eg. sxhkd event)\n"
"        silent: Do not log any messages, including the error messages.\n"
"\n"
"Example:\n"
"   # launch the daemon\n"
"   %s -l error /run/user/$UID/sxhkd.fifo\n"
"\n"
"   # connect to the daemon from a client process\n"
"   socat UNIX_CONNECT:/run/user/$UID/sxhkd.fifo.sxhkd-statusd -\n"
"\n",
        pname, pname, pname);
}
