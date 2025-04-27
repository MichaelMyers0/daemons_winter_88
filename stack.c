#include "stack.h"

init(s)
stack_t* s;
{
	s->sp = 0;
	openlog("stack", LOG_PID, LOG_USER);
}

push(s, val)
stack_t* s;	
const char* val;
{
	int len;
	len = strlen(val);
	if (len >= STRING_LEN)
	{
		syslog(LOG_ERR, "ERROR: String is too long\n");
		_exit(5);
	}
	if (s->sp < STRING_LEN)
	{
		strcpy(s->stk[s->sp], val);
		(s->sp)++;
		return 1;
	}
	syslog(LOG_ERR, "ERROR: Stack overflow\n");
}

pop(s)
stack_t* s;	
{
	if (s->sp == 0)
	{
		syslog(LOG_ERR, "ERROR: Stack underflow\n");
		closelog();
		_exit(6);
	}
	(s->sp)--;
}

const char* top(s)
stack_t* s;	
{
	return &(s->stk[s->sp - 1][0]);
}


