#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <syslog.h>
#define SLEEP_T 10
#define CYCLE 4
main()
{
	int i;
	pid_t pid, ppid, sid, pgrpid, child;
	openlog("main", LOG_PID, LOG_USER);
	pid = getpid();
	ppid = getppid();
	sid = getsid(0);
	pgrpid = getpgrp();
	errno = 0;
	child = fork();
	if (child == -1)
	{		
		syslog(LOG_ERR, "Failed to create a process\n");
		_exit(1);
	}
	if (child == 0)
	{
		errno = 0;
		sid = setsid();
		if (sid == -1)
		{
			syslog(LOG_ERR, "ERROR: Failed to start a new session\n");
			_exit(2);
		}
		pid = getpid();
		ppid = getppid();
		pgrpid = getpgrp();
		syslog(LOG_INFO, "child pid = %d\tppid = %d\tsid = %d\tpgrpid = %d\n", pid, ppid, sid, pgrpid);
		errno = 0;
		child = fork();
		if (child == -1)
		{
			syslog(LOG_ERR, "second fork()\n");
			_exit(3);
		}		
		if (child == 0)
		{
			for (i = 0; i < CYCLE; i++)
			{
				sleep(SLEEP_T);
				syslog(LOG_INFO, "Hello World\n");
			}
			pid = getpid();
			ppid = getppid();
			pgrpid = getpgrp();
			syslog(LOG_INFO, "second child pid = %d\tppid = %d\tsid = %d\tpgrpid = %d\n", pid, ppid, sid, pgrpid);
			syslog(LOG_INFO, "Second child was finished\n");
			_exit(0);
		}
		else
		{
			syslog(LOG_INFO, "Child process was finished\n");
			_exit(0);
		}
	}
	else
	{
		syslog(LOG_INFO, "pid = %d\tppid = %d\tsid = %d\tpgrpid = %d\n", pid, ppid, sid, pgrpid);
		syslog(LOG_INFO, "Parent process was terminated\n");
		_exit(0);
	}
}
