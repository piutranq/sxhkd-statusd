#include <stdbool.h>

#define PATH_SUFFIX ".sxhkd-statusd"

enum LogLevel {
    LOG_LEVEL_ERROR = 0,
    LOG_LEVEL_INFO = 1,
    LOG_LEVEL_VERBOSE = 2,
    LOG_LEVEL_SILENT = -1,
};

struct Config {
    char sxhkd_path[94];
    char server_path[108];
    enum LogLevel log_level;
};

void config_init(int argc, char** argv);

char* config_sxhkd_path();
char* config_server_path();
enum LogLevel config_log_level();
bool check_log_level();
