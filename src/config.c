#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "msg.h"

static struct Config ___conf;

static struct option long_opts[] = {
    {"help", no_argument, 0, 'h'},
    {"log", required_argument, 0, 'l'},
    {0, 0, 0, 0}
};

/* Init the config from arguments */
void config_init(int argc, char** argv) {

    if (argc < 2) {
        msg_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    memset(___conf.sxhkd_path, 0x00, sizeof(___conf.sxhkd_path));
    memset(___conf.server_path, 0x00, sizeof(___conf.server_path));
    ___conf.log_level = LOG_LEVEL_INFO;

    while (1) {
        int opt = getopt_long(argc, argv, "hl:", long_opts, NULL);
        if (opt == EOF) break;

        switch(opt) {
        case 'h':
            msg_help(argv[0]);
            exit(EXIT_SUCCESS);
        case 'l':
            if (strcmp(optarg, "silent") == 0)
                ___conf.log_level = LOG_LEVEL_SILENT;
            else if (strcmp(optarg, "error") == 0)
                ___conf.log_level = LOG_LEVEL_ERROR;
            else if (strcmp(optarg, "info") == 0)
                ___conf.log_level = LOG_LEVEL_INFO;
            else if (strcmp(optarg, "verbose") == 0)
                ___conf.log_level = LOG_LEVEL_VERBOSE;
            break;
        default:
            break;
        }
    }

    sprintf(___conf.sxhkd_path, "%s", argv[optind]);
    sprintf(___conf.server_path, "%s%s", argv[optind], PATH_SUFFIX);
}

char* config_sxhkd_path() {
    return ___conf.sxhkd_path;
}

char* config_server_path() {
    return ___conf.server_path;
}

enum LogLevel config_log_level() {
    return ___conf.log_level;
}

bool check_log_level(enum LogLevel target) {
    if (___conf.log_level >= target) return true;
    else return false;
}


