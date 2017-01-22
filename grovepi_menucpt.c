#include "grovepi.h"

//Compilation : gcc grovepi_ultrasonic.c grovepi.c -Wall -o grovepi_ultrasonic
//Execution : sudo ./grovepi_ultrasonic

#define us_cmd 7

char set_on[256];
char new_color[256];


void change_color(int increment,int cmd,char ip[])
{
	

	if(cmd == 0 && increment <=60){
		increment-=5;
		sprintf(new_color,"yee --ip=%s hsv %d 100",ip,increment);
		system(new_color);
	}
	else if(cmd==1 && increment >=0){
		increment+=5;
		sprintf(new_color,"yee --ip=%s hsv %d 100",ip,increment);
		system(new_color);
	}
}

int main(void)
{		
	//Exit on failure to start communications with the GrovePi
	if(init()==-1)
		exit(1);
	
	int PIN1 = 2; // Capteur branché sur le port D2 (digital 2)
	int PIN2 = 3;// Capteur branché sur le port D3 (digital 3)

	
	int distance = 100;
	int data1,data2;
	int nbpersonne =0;
	char ip[256];
	int increment = 60;
	int choix =0;
	
	printf("Entrez l'ip de la lampe\n");
	scanf("%s",ip);
	sprintf(set_on,"yee --ip=%s turn on",ip);
	system(set_on);
	sprintf(new_color,"yee --ip=%s hsv %d 100",ip,increment);
	system(new_color);


	printf(" \n >>> Bienvenue dans le menu : Faites votre choix ! <<< \n\n ");
	printf(" 1) Tapez 1 pour gérer les entrées sorties a la main \n ");
	printf(" 2) Tapez 2 pour gérer les entrées sorties avec les capteurs \n ");
	printf(" 3) Tapez 3 pour sortir \n ");
	scanf("%d",&choix);


	switch(choix)
	{
		case 1:
    		{	int c = 0;
    			nbpersonne =0;
    			printf("Vous avez choisi de gérer les entrées sortie a la main\nn");
    			while (nbpersonne <21 && nbpersonne >=0)
    			{
    			printf("Appuyer sur 1 pour entrer");
    			printf("Appuyer sur 0 pour sortir");
    			scanf("%d",&c);
    			if(c == 1)
    			{
    				nbpersonne=nbpersonne+1;
	  				increment -=3;
					change_color(increment,0,ip);
	  				printf("Une personne vient de rentrer\n");
					printf("Nombre de personne : %d\n",nbpersonne);
    			}
    			else if(c == 0)
    			{
    				nbpersonne=nbpersonne-1;
                	increment +=3;
					change_color(increment,1,ip);        
               	    printf("Une personne vient de sortir\n");
                    printf("Nombre de personne : %d\n",nbpersonne);
    			}

 				}
        	
    		} break;


    	case 2:
    		{
 				nbpersonne =0;
			while(1) // boucle infinie
			{
			 	pi_sleep(100);
			 	data1=distance;
			 	data2=distance;
			 	// Lecture de la distance sur le premier capteur 
			  	write_block(us_cmd,PIN1,0,0);
			  	pi_sleep(200);
			  	read_byte();
			  	read_block();
			  	data1=r_buf[1]* 256 + r_buf[2];
			 


			  	// Si la distance lu par ce capteur est inferieur a la distance entre le capteur et le mur face au capteur
			    //>>>> detection d'un individu entre le capteur et le mur d'en face  
				if (data1 < distance)
			  	{	

					pi_sleep(100);
					data1=distance;
					write_block(us_cmd,PIN2,0,0);
					pi_sleep(200);
					read_byte();
					read_block();
					data2=r_buf[1]*256 + r_buf[2];
				
			
			  		if(data2 < distance)
			  		{	
			  			nbpersonne=nbpersonne+1;
			  			increment -=3;
						change_color(increment,0,ip);
			  			printf("Une personne vient de rentrer\n");
						printf("Nombre de personne : %d\n",nbpersonne);
			  			data2=distance;
						pi_sleep(100);

			  		}
			  	
			  	}
			
			 	if (nbpersonne > 0)
				{	
					data2 = distance;
					data1 = distance;
					pi_sleep(100);
					write_block(us_cmd,PIN2,0,0);
					pi_sleep(200);
					read_byte();
					read_block();
					data2= r_buf[1]*256 + r_buf[2];
			

					if (data2 < distance)
		         	{
		               	pi_sleep(100);
						data2=distance;
		                write_block(us_cmd,PIN1,0,0);
						pi_sleep(200);
		                read_byte();
		                read_block();
		                data1=r_buf[1]*256 + r_buf[2];
				

		                if(data1 < distance)
		                {       
		                	nbpersonne=nbpersonne-1;
		                	increment +=3;
							change_color(increment,1,ip);        
		               	    printf("Une personne vient de sortir\n");
		                    printf("Nombre de personne : %d\n",nbpersonne);
		                   	data1=distance;
							pi_sleep(100);	 
		         		}
		         	}
				}	
		 	}
		        	
		} break;

	}

	


   	return 1;
}