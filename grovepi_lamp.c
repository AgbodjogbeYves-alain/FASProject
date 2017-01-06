#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */


void change_color(int cmd,char ip[]){
	char commande[256];
	char set_on[256];
	char ip_bulb[] = ip;
	sprintf(on,"yee --ip=%s turn on",ip);
	system(on);

	/*if(cmd == 1){

	}
	else if(cmd==2){

	}
	else if(cmd==3){

	}
	else if (cmd==4){

	}*/
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
	change_color(0,"192.168.43.167");
	return 0;
}