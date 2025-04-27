#ifndef STACK_H
#define STACK_H
#define STRING_LEN 255
#include <string.h>
#include <syslog.h>
#include <sys/types.h>
#include <unistd.h>
typedef char path_t[STRING_LEN];
typedef struct
{
	path_t stk[STRING_LEN];
	int sp;
}stack_t;
init(s);
push(s, val);
pop(s);
const char* top(s);
#endif
