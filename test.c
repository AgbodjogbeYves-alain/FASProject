#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */



int main(){
	system("export DISPLAY=:0");
	system("eog --fullscreen carre_rouge.1240723866.thumbnail.png &");
	system("eog --fullscrenn invisible.png &");
	return 0;
}