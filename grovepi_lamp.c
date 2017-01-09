#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */


void change_color(int cmd,char ip[]){
	//char commande[256];

	char set_on[256];
	int increment=60;
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
		increment-=5;
		sprintf(new_color,"yee --ip=%s hsv %d 100",ip,increment);
		system(new_color);
	}
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
	char ip[256];
	printf("Entrez l'ip du ");
	scanf("%s",ip);

	change_color(0,ip);

	system("yee --ip=192.168.43.167 turn off");
	return 0;
}
