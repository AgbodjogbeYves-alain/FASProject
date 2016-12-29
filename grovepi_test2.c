#include "grovepi.h"

//Compilation : gcc grovepi_ultrasonic.c grovepi.c -Wall -o grovepi_ultrasonic
//Execution : sudo ./grovepi_ultrasonic

#define us_cmd 7

int main(void)
{		
	//Exit on failure to start communications with the GrovePi
	if(init()==-1)
		exit(1);
	
	int PIN = 4;
	int PIN1 = 3;// Capteur branché sur le port D4 (digital 4)

	int data1,data2;
	int distance = 210;
	while(1) // boucle infinie
	{
	  write_block(us_cmd, PIN, 0, 0);
	  read_byte();
	  read_block();
	  data1=r_buf[1]* 256 + r_buf[2];
	  
	  if (data1 < distance)
	  {
	  	write_block(us_cmd, PIN1, 0, 0);
	  	read_byte();
	  	read_block();
	  	data2=r_buf[1]* 256 + r_buf[2];
		pi_sleep(200);
	  	
		if(data2 < distance)
	  	{
	  		printf("Une personne vient de rentrer\n");
	  		

	  	}
	  	else
	  	{
	  		printf("la personne a fait demi tour avant d'entrer\n");
	  	}
	  	pi_sleep(250);
	  }
	}
}
