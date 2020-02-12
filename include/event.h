void server_event(int server_fd, fd_set* fds);
void client_event(int client_fd, fd_set* fds);
void sxhkd_event(int pipe_fd);
