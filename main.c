#include "daemon.h"
main()
{
	time_t t;
	char* s;
	t = time(NULL);
	s = ctime(&t);
	become_daemon("./test", s);
}
