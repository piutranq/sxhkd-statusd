void err_exit(char* msg);

void open_error(char* path);
void flock_error(char* path);
void socket_error();
void bind_error(char* path);
void listen_error();
void accept_error(int fd);
void read_error(int fd);
void select_error();
