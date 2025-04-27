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
		perror("fork()\n");
		_exit(1);
	}
	if (child == 0)
	{
		errno = 0;
		sid = setsid();
		if (sid == -1)
		{
			perror("ERROR: Failed to start a new session\n");
			_exit(2);
		}
		pid = getpid();
		ppid = getppid();
		pgrpid = getpgrp();
		printf("child pid = %d\tppid = %d\tsid = %d\tpgrpid = %d\n", pid, ppid, sid, pgrpid);
		errno = 0;
		child = fork();
		if (child == -1)
		{
			perror("second fork()\n");
			_exit(3);
		}		
		if (child == 0)
		{
			for (i = 0; i < CYCLE; i++)
			{
				sleep(SLEEP_T);
				printf("Hello World\n");
			}
			pid = getpid();
			ppid = getppid();
			pgrpid = getpgrp();
			printf("second child pid = %d\tppid = %d\tsid = %d\tpgrpid = %d\n", pid, ppid, sid, pgrpid);
			printf("Second child was finished\n");
			_exit(0);
		}
		else
		{
			printf("Child process was finished\n");
			_exit(0);
		}
	}
	else
	{
		printf("pid = %d\tppid = %d\tsid = %d\tpgrpid = %d\n", pid, ppid, sid, pgrpid);
		printf("Parent process was terminated\n");
		_exit(0);
	}
}
