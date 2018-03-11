#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    struct stat attributes;
    struct dirent *directory;
	DIR *dir;
	
	dir = opendir (".");
    if (dir == NULL)
    { 
		printf ("ERROR");
        return -1;
	}
        
	while ((directory = readdir(dir)) != NULL) {
 
		if(directory->d_name[0] == '.')
        {
            continue;
		}
    
		int s = lstat(directory->d_name,&attributes);
		
		if(s != 0)
		{
			printf("ERROR");
			return -1;
		}
			
		if(S_ISREG(attributes.st_mode))
			printf("-");
		else if(S_ISDIR(attributes.st_mode))
			printf("d");
		else if(S_ISCHR(attributes.st_mode))
			printf("c");
		else if(S_ISBLK(attributes.st_mode))
			printf("b");
		else if(S_ISFIFO(attributes.st_mode))
			printf("f");
		else if(S_ISLNK(attributes.st_mode))
			printf("l");
		else
			printf("s");	
	   
		printf(" ");
		printf( (attributes.st_mode & S_IRUSR) ? "r" : "-");
		printf( (attributes.st_mode & S_IWUSR) ? "w" : "-");
		printf( (attributes.st_mode & S_IXUSR) ? "x" : "-");
		printf( (attributes.st_mode & S_IRGRP) ? "r" : "-");
		printf( (attributes.st_mode & S_IWGRP) ? "w" : "-");
		printf( (attributes.st_mode & S_IXGRP) ? "x" : "-");
		printf( (attributes.st_mode & S_IROTH) ? "r" : "-");
		printf( (attributes.st_mode & S_IWOTH) ? "w" : "-");
		printf( (attributes.st_mode & S_IXOTH) ? "x" : "-");
		
		printf(" ");
		
		printf("%-5ld ", (long) attributes.st_uid);
		printf("%-5ld ", (long) attributes.st_gid);
		printf("%-5lld ", (long long) attributes.st_size);
		char buffer[50];
		strftime(buffer,sizeof buffer,"%m.%d %H:%M",localtime(&attributes.st_mtime));
		printf(" %s ",buffer);
		printf("%-5s\n",directory->d_name);

    
 }
   return 0;
}
