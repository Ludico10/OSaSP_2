#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <locale.h>
#include <fcntl.h>

int Searcher(char* sch_d, char* sch_f, int* cnt_d, int* cnt_f)
{
	DIR* opd = opendir(sch_d);
	if (opd != NULL)
	{
		struct dirent *dir;
		char path[PATH_MAX];
		while((dir = readdir(opd)) != NULL)
		{
			if (dir->d_type == DT_REG)	
			{
				(*cnt_f)++;
				if (strcmp(sch_f,dir->d_name) == 0)
				{	
					if (realpath(sch_d, path) != NULL)
            				{
	            				strcat(path,"/");
	            				strcat(path,sch_f);
	            			}
	            			else perror("realpath() ");
	            			struct stat buf;
	            			int res = stat(path, &buf);
	            			if (res == 0) 
	            			{
	            				char str[128];
						struct tm lt;
						localtime_r(&buf->st_mtime,&lt);
						strftime(str, 128, "%d %b %Y", &lt);				
						fprintf(stdout, "%s %ld %lo %ld %s\n", path, buf->st_size, (unsigned long)buf->st_mode,(long)buf->st_ino, str);
	            			}	
	            			else perror("stat() ");			
				}
			}
			if (((dir->d_type == DT_DIR)) && ((strcmp(dir->d_name,".")) != 0) && ((strcmp(dir->d_name,"..")) != 0))
			{
				(*cnt_d)++;
				if (realpath(sch_d, path) != NULL)
            			{
	            			strcat(path,"/");
	            			strcat(path,dir->d_name);
	            			Searcher(path,sch_f,cnt_d,cnt_f);
	            		}
	            		else perror("realpath() ");
			}			
		}
		if (closedir(opd)) perror("closedir() ");
	}
	else perror("opendir() ");	
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 3)  fprintf(stderr,"Wrong number of parameters\n");
	else
	{
		if (strlen(argv[2]) > NAME_MAX) fprintf(stderr,"Too long filename\n");
		else
		{
			int cd = 1, cf = 0;
			Searcher(argv[1],argv[2],&cd,&cf);
			fprintf(stdout, "Dirrectores: %d; Files: %d\n", cd,cf);

		}
	}
	return 0;
}
