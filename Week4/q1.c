#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
//0 is fildes for std input, 1 - std output, 2 - std error
int main()
{
	char word[128];
	int nread = read(0,word,128);
	write(1,word,nread);
	int file1=open("q1_read",O_RDONLY);
	char curchar;
        off_t start=0;
        int run =1;
	while(run)
	{
          char line[256];
	  int found=0;
	  int i=0;
	  int linelen=0;
	  start=lseek(file1,0,SEEK_CUR);
	  int checkend;
	  do
	  {
	    linelen++;//increment regardless of found or not to get line length
            checkend = read(file1,&curchar,1);
      
            
            if(checkend <= 0)
              break;
            if(!found)
            {
            if(curchar==word[i])
            {
             
             i++;
             if(i==nread-1)
              {
                found=1;
              }
            }
            else
              i=0;
             }
	  }while(curchar!='\n');
          if(checkend <= 0)
              break;
	  if(found)
	   {
	      lseek(file1,start,SEEK_SET);
              linelen = read(file1,line,linelen);
              write(1,line,linelen);
           }
           
	 }
}


