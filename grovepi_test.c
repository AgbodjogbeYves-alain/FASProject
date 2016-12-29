#include "grovepi.h"

//Compilation : gcc grovepi_ultrasonic.c grovepi.c -Wall -o grovepi_ultrasonic
//Execution : sudo ./grovepi_ultrasonic

#define us_cmd 7

int main(void)
{		
	//Exit on failure to start communications with the GrovePi
	if(init()==-1)
		exit(1);
	
	int PIN1 = 2;
	int PIN2 = 4;// Capteur branché sur le port D4 (digital 4)

	int data1,data2;
	int distance = 150;
	int nbpersonne =0;
	while(1) // boucle infinie
	{
	  write_block(us_cmd, PIN2, 0, 0);
	  pi_sleep(200);
	  read_byte();
	  read_block();
	  data1=r_buf[1]* 256 + r_buf[2];

	  

	  
	  if (data1 < distance)
	  {
		data1=distance;
		write_block(us_cmd,PIN1,0,0);
		pi_sleep(200);
		read_byte();
		read_block();
		data2=r_buf[1]*256 + r_buf[2];

	  	if(data2 < distance)
	  	{	nbpersonne=nbpersonne+1;
			data2=distance;
	  		printf("Une personne vient de rentrer\n");
			printf("Nombre de personne : %d\n",nbpersonne);
	  		pi_sleep(200);

	  	}
	  	else
	  	{
	  		printf("la personne a fait demi tour avant d'entrer\n");
			pi_sleep(200);
	  	}
	  }
	
	write_block(us_cmd,PIN1,0,0);
	read_byte();
	read_block();
	data2= r_buf[1]*256 + r_buf[2];

	if (data2 < distance)
          {
                data2=distance;
                write_block(us_cmd,PIN2,0,0);
                pi_sleep(200);
                read_byte();
                read_block();
                data1=r_buf[1]*256 + r_buf[2];

                if(data1 < distance)
                {       nbpersonne=nbpersonne-1;
                        data1=distance;
                        printf("Une personne vient de sortir\n");
                        printf("Nombre de personne : %d\n",nbpersonne);
                        pi_sleep(200);

                }
                else
                {
			 printf("la personne a fait demi tour avant d'entrer\n");
                         pi_sleep(200);
                }
          }
	  
	  	

	   pi_sleep(300);// attend 500ms
	}
   	return 1;
}

