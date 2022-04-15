#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>

int main(void)
{
	char dir[PATH_MAX];
	if (getcwd(dir, PATH_MAX) == 0)  perror("getcwd() ");
	else 
	{
		struct dirent *memb;
		puts("\nCurrent dir:\n");
		DIR *cur = opendir(dir);
		if (cur == NULL) perror("opendir(dir) ");
		else
		{
			while ((memb = readdir(cur)) != NULL)  printf("%s\n", memb->d_name);
			if (closedir(cur) == -1)  perror("closedir(dir) ");	
		}
		puts("\nRoot dir:\n");
		cur = opendir("/");
		if (cur == NULL) perror("opendir(root) ");
		else
		{
			while ((memb = readdir(cur)) != NULL)  printf("%s\n", memb->d_name);
			if (closedir(cur) == -1)  perror("closedir(root) ");	
		}
	}
	return 0;	
}
