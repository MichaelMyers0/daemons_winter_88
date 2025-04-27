#ifndef DAEMON_H
#define DAEMON_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <syslog.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include "find.h"
#define SLEEP_T 10
#define CYCLE 4
#define NUM_OF_DESCRIPTORS 3
become_daemon(path, date);
#endif
