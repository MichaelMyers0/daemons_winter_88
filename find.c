#include "find.h"

static stack_t s;
static flag = 0;
static char buf[STRING_LEN];

static open_dir(dirp, path);
static close_dir(dirp);
static path_builder(dst, src1, src2);

static open_dir(dirp, path)
DIR** dirp;
const char* path;
{
	errno = 0;
	*dirp = opendir(path);
	if (!*dirp)
	{
		syslog(LOG_ERR, "ERROR: Failed to open a directory\n");
		_exit(4);
	}
}

static close_dir(dirp)
DIR* dirp;
{
	int res;
	errno = 0;
	res = closedir(dirp);
	if (res == -1)
	{
		syslog(LOG_ERR, "ERROR: Failed to close a directory\n");
		_exit(5);
	}
}

static path_builder(dst, src1, src2)
char* dst;
const char* src1;
const char* src2;
{
	int len;
	strcpy(dst, src1);
	strcat(dst, src2);
	len = strlen(dst);
	*(dst + len) = 0;
}

find(path, date)
const char* path;
const char* date;
{
	DIR* dirp;
	struct dirent* ent;
	int res;
	struct stat statbuf; 
	if (!flag)
	{
		init(&s);
		push(&s, path);
	}
	open_dir(&dirp, path);
	while ((ent = readdir(dirp)))
	{
		if (0 == strcmp(ent->d_name, ".") || 0 == strcmp(ent->d_name, ".."))
			continue;
		switch (ent->d_type)
		{
			case DT_REG :
				errno = 0;
				res = stat(path, &statbuf);	
				if (res == -1)	
					break;
				if (0 == strcmp(date, ctime(&(statbuf.st_mtim.tv_sec))))
				{
					printf("DEBUG_PRINT find\n");
					errno = 0;
					res = unlink(path);
					if (res == -1)
					{
						syslog(LOG_ERR, "ERROR: Failed to delete a file\n"); 
						_exit(6);
					}
				}
				break;
			case DT_DIR :
				path_builder(buf, top(&s), ent->d_name);
				push(buf);
				*buf = 0;
				find(top(&s), date);
				break;
		}
	}
	close_dir(dirp);
}
