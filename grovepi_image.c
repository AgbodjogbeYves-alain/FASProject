#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */


void change_image(int commande){
	char new_image[256];
	sprintf(new_image,"eog --fullscreen imageColor_%d.png &",commande);
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
	if(p<a && p < limitH){ //Si le volume precedemment enregistré est inferieur au volume enregistré a l'instant

		while(p < a && p < limitH) { //On a 10 images et on fixe la limite du volume a 500mdb. Donc a chaque changement de 50 decibels on change d'image
			commande+=1;
			p+=50;
		}
	}
		
	else if(p>a && p > 0){
		while(p>a && p > 0) {
			p-=50;
			commande-=1;
		}
	}
	return commande;
}

int main(){

	/*PyObject *module,*fonction,*arguments,*retour;
	Py_Initialize(); 
	PySys_SetPath(".");
	module = PyImport_ImportModule("cli");
	fonction = PyObject_GetAttrString(module, "turn");
	arguments = Py_BuildValue("(s)", "on");
	PyEval_CallObject(fonction, arguments);
	Py_Finalize();*/
	//system("yee --ip=192.168.0.20 turn on");
	int seuil_db = 500;
	int volumeactuel = 0;
	//int volumepers = 50;
	int increment = 60;
	//int nbpers=0;
	char ip[256];
	int volumeprecedent=0;
	//printf("Entrez l'ip de la lampe\n");
	//scanf("%s",ip);
	int i =0;
	printf("Entrez le volume sonore ambiant\n");
	scanf("%d",&volumeactuel);
	printf("Entrez le volume precedent de la salle\n");
	scanf("%d",&volumeprecedent);
	//commande = definirCouleur(volumeactuel,volumeprecedent,500);
	change_image(1);
	return 0;
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


	}
	return 0;
	
}*/