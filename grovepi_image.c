#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#include "grovepi.h"

void change_image(int commande){
	char new_image[256];
	sprintf(new_image," nohup eog --fullscreen imageColor_%d.png &",commande);
	system(new_image);

}

int definirCouleur(int actu){
	int a = actu; // Le volume envoyé a l'instant par le capteur
	int personne = 50;
	int seuil_0 = personne;
	int seuill_1 = personne * 2;
	int seuill_2 = personne * 4;
	int seuill_3 = personne * 6;
	int seuill_4 = personne * 8;
	int seuill_5 = personne * 10;
	int seuill_6 = personne * 12;
	int seuill_7 = personne * 14;
	int seuill_8 = personne * 16;
	int seuill_9 = personne * 18;
	int seuill_10 = personne * 20;

	if(a>seuil_0){
		return 0;
	}
	else if(a>seuil_1){
		return 1;
	}
	else if(a>seuil_2){
		return 2;
	}
	else if(a>seuil_3){
		return 3;
	}
	else if(a>seuil_4){
		return 4;
	}
	else if(a>seuil_5){
		return 5;
	}
	else if(a>seuil_6){
		return 6;
	}
	else if(a>seuil_7){
		return 7;
	}
	else if(a>seuil_8){
		return 8;
	}
	else if(a>seuil_9){
		return 9;
	}
	else if(a>seuil_10){
		return 10;
	}
}

int main(){

	int commande = 1;
	int commandeprec = 1;
	//Exit on failure to start communications with the GrovePi
  	if(init()==-1)
    		exit(1);
    // Capteur de son sur le port A0 en lecture
  	int PIN = 1;
  	pinMode(PIN,0);
  	int value;
  	change_image(1);
  	sleep(5);
	while(1){

		value = analogRead(PIN);
		printf("Sensor value = %d\n", value);
		commande = definirCouleur(value);
		if (commandeprec != commande){
			commandeprec = commande;
			change_image(commande);
		}
		sleep(5);
		
	
	}	
	return 0;
	
}
