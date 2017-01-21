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

int definirCouleur(int actu,int prec, int limitH){
	int p = prec; // le volume enregistré précedemment
	int a = actu; // Le volume envoyé a l'instant par le capteur
	int commande = 0; //La commande
	if(p<a && a-p>=limitH/10){ //Si le volume precedemment enregistré est inferieur au volume enregistré a l'instant

		while(p < a && commande<10 ) { //On a 10 images et on fixe la limite du volume a 500mdb. Donc a chaque changement de 50 decibels on change d'image
			commande+=1;
			p+=50;
		}
	}
		
	else if(p>a && p > 0 && p-a >limitH/10){
		while(p>a && p > 0 && commande>0) {
			p-=50;
			commande-=1;
		}
	}
	return commande;
}

int main(){

	int nbpers=5;
	int seuil_db = 100 * nbpers;
	int volumeprecedent=0;
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
		commande = definirCouleur(value,volumeprecedent,seuil_db);
		if (commandeprec != commande && commande>=1){
			printf("%d ",commande);
			commandeprec = commande;
			change_image(commande);
		}

		volumeprecedent = value;
		sleep(10);
		
	
	}	
	return 0;
	
}
