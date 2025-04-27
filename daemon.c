#include "daemon.h"
static close_descriptors();
static open_descriptors();
static close_descriptors()
{
	int i;
	for (i = 0; i < NUM_OF_DESCRIPTORS; i++)
		close(i);
}
static open_descriptors()
{
	open("/dev/null", O_RDONLY);
	open("/dev/null", O_WRONLY);
	open("/dev/null", O_WRONLY);
}
become_daemon(path, date)
const char* path;
const char* date;
{
	int i;
	pid_t pid, ppid, sid, pgrpid, child;
	time_t t;
//	close_descriptors();
//	open_descriptors();
	t = time(NULL);
	openlog("main", LOG_PID, LOG_USER);
	syslog(LOG_INFO, ctime(&t));
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
			pid = getpid();
			ppid = getppid();
			pgrpid = getpgrp();
			syslog(LOG_INFO, "second child pid = %d\tppid = %d\tsid = %d\tpgrpid = %d\n", pid, ppid, sid, pgrpid);
			syslog(LOG_INFO, "Second child was finished\n");
			find(path, date);
			closelog();
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
