#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>        
#include <stdlib.h> 
#include <time.h>  

void openfile(void);
void readfile(void);
int fd=0;
 

int  main()
{
	openfile();
	readfile();
        return 0;
}

void openfile(void)
{
    if ((fd=open("/dev/ttyUSB0", O_RDONLY)) < 0) {
        perror("Error Open File");
      	exit (1);
    } 
}

void  readfile(void)
{
  unsigned char ichar; 
  unsigned char dataread;
  int  i,ifd;
  FILE *fileoutput;
  time_t rawtime;
  struct tm * timeinfo;
  
  if((fileoutput = fopen("send.txt","w"))==NULL){
  	fprintf(stderr, "Tidak bisa membuka file");
  	exit(0);
  }
  
  for (i = 0; i<10; i++) {
  	time (&rawtime);
	timeinfo = localtime (&rawtime);
	ifd = read(fd, &ichar, 1);
	//printf("%d\n", ichar);
	fprintf (fileoutput,"\nCurrent local time and date: %s", asctime(timeinfo));
        if (ichar == 1) {
	    printf("Suhu Terdeteksi : ");
	    ifd = read(fd, &dataread, 1);
	    printf("\n%d\n", dataread);	
	    fprintf(fileoutput,"Suhu : %d", dataread);
	}
	fprintf(fileoutput,"\n");
	sleep(1);
  }
  close(fd);
  fclose(fileoutput);
}

