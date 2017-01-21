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
void change_color(int increment,int cmd,char ip[]){
	//char commande[256];

	char set_on[256];
	char new_color[256];
	//char ip_bulb[] = ip;
	sprintf(set_on,"yee --ip=%s turn on",ip);
	system(set_on);

	if(cmd == 0){
		increment-=5;
		sprintf(new_color,"yee --ip=%s hsv %d 100",ip,increment);
		system(new_color);
	}
	else if(cmd==1){
		increment+=5;
		sprintf(new_color,"yee --ip=%s hsv %d 100",ip,increment);
		system(new_color);
	}
}

int definirCouleur(int actu,int prec, int limitH){
	int p = prec; // le volume enregistré précedemment
	int a = actu; // Le volume envoyé a l'instant par le capteur
	int commande = 0; //La commande
	if(p<a && p < limitH && a-p>200){ //Si le volume precedemment enregistré est inferieur au volume enregistré a l'instant

		while(p < a && p < limitH) { //On a 10 images et on fixe la limite du volume a 500mdb. Donc a chaque changement de 50 decibels on change d'image
			commande+=1;
			p+=200;
		}
	}
		
	else if(p>a && p > 0 && p-a > 200){
		while(p>a && p > 0) {
			p-=50;
			commande-=1;
		}
	}
	return commande;
}

int main(){

	
	int volumeactuel = 0;
	int increment = 60;
	int nbpers=25;
	int seuil_db = 25 * nbpers;
	//char ip[256];
	int volumeprecedent=0;
	//printf("Entrez l'ip de la lampe\n");
	//scanf("%s",ip);
	int commande = 1;
	int commandeprec = 0;
	//int i =0;
	//Exit on failure to start communications with the GrovePi
  	if(init()==-1)
    		exit(1);
    // Capteur de son sur le port A0 en lecture
  	int PIN = 1;
  	pinMode(PIN,0);
  	int value;
  	change_image(commande);
	while(1){

		//printf("Entrez le volume sonore ambiant\n");
		//scanf("%d",&volumeactuel);
		//printf("Entrez le volume precedent de la salle\n");
		//scanf("%d",&volumeprecedent);
		commandeprec = commande;
		value = analogRead(PIN);
		printf("Sensor value = %d\n", value);
		commande = definirCouleur(value,volumeprecedent,seuil_db);
		if (commandeprec != commande and commande>=1){
			change_image(commande);
		}

		volumeprecedent = value;
		sleep(10);
		
	
	}	
		
		/*while(1){
			printf("Entrez le volume sonore ambiant\n"); // a remplacer pr les valeurs du capteur sonore ou du nombre de personne * 50
			scanf("%d",&db);
			printf("Entrez le volume precedent dans la salle\n"); //a remplacer par les valeurs du capteur ultason
			scanf("%d",&volume_actuel);
			
			if (db>volume_actuel && db-volume_actuel>50){
				while (db-volume_actuel > 50 ){
					
					if(increment-10>=0){
						while(i<10){
							increment -=2;
							change_color(increment,0,ip);
							i+=2;
						}
							
					}
					volume_actuel += 50;
				} 
			}

			if (db<volume_actuel && volume_actuel-db > 50){
				while (volume_actuel-db > 50 ){
					volume_actuel -= 50;
					if(increment+10 <=60){
						while(i<10){
							increment +=2;
							change_color(increment,0,ip);
							i+=2;
						}
					}
					volume_actuel -= 50;
				}
				
			}

			volume_actuel = db;
				//system("yee --ip=192.168.43.167 turn off");


		}*/
	//}
	return 0;
	
}
