#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if (argc != 3)  fprintf(stderr,"Wrong number of parameters\n");
	else if (strcmp(argv[1], argv[2]) != 0)
	{
		int op1, op2;
		if ((op1 = open(argv[1], O_RDONLY)) && (op2 = open(argv[2], O_WRONLY | O_CREAT)))
		{
			FILE *f1, *f2;
			if ((f1 = fdopen(op1,"r")) && (f2 = fdopen(op2,"w")))
			{
				char ch = getc(f1);
				while (ch != EOF) 
				{
					if (putc(ch,f2) == EOF)  fprintf(stderr,"Writing character error\n");
					ch = getc(f1);
				}	
				struct stat buf;
				if (fstat(op1,&buf) == -1)  perror("fstat() ");
				else if (fchmod(op2,buf.st_mode) == -1)  perror("fchmod() ");	
			}
			else perror("fdopen() ");
			if (fclose(f1) != 0)  perror("fclose() ");
			if (fclose(f2) != 0)  perror("fclose() ");
		}
		else perror("open() ");
	}
	else fprintf(stderr,"Parameters can't be the same\n");
	return 0;
}
