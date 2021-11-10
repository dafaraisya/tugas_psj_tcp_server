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
  unsigned char dataread[2];
  int  i,ifd;
  FILE *fileoutput;
  time_t rawtime;
  struct tm * timeinfo;
  
  if((fileoutput = fopen("send.txt","w"))==NULL){
  	fprintf(stderr, "Tidak bisa membuka file");
  	exit(0);
  }
  
  for (i = 0; i<30; i++) {
  	time (&rawtime);
	timeinfo = localtime (&rawtime);
	ifd = read(fd, &ichar, 1);
	printf("%d\n", ichar);
	if(i%1==0){
	    fprintf (fileoutput,"\nCurrent local time and date: %s", asctime(timeinfo));
	}
        if (ichar == 101) {
	    printf("Suhu Terdeteksi : ");
	    ifd = read(fd, &dataread, 2);
	    printf("%d\n", dataread[1]);	
	    fprintf(fileoutput,"Suhu : %d", dataread[1]);
	}
/*
	if (ichar == 102) {
	   printf("data ke dua : ");
	   ifd = read(fd, &dataread, 2);
	   printf("%.2x,%.2x\n",dataread[0],dataread[1]);	
	   fprintf(fileoutput,"Kelembaban Tanah : %.2x,%.2x",dataread[0],dataread[1]);
	}
	if (ichar == 103) {
	   printf("data ke tiga : ");
	   ifd = read(fd, &dataread, 2);
	   printf("%.2x,%.2x\n",dataread[0],dataread[1]);	
	   fprintf(fileoutput,"Intensitas Cahaya : %.2x,%.2x",dataread[0],dataread[1]);
	}
*/
	fprintf(fileoutput,"\n");
	sleep(1);
  }
  close(fd);
  fclose(fileoutput);
}

