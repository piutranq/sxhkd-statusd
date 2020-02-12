void msg_open_pipe(int fd, char* path);
void msg_init_server(int fd, char* server);

void msg_accept(int fd);
void msg_sxhkd(int fd, char* msg);
void msg_close(int fd);

void msg_help(char* pname);
