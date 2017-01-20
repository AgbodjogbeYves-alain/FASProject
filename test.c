#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */



int main(){
	system("eog --fullscreen carre_rouge.1240723866.thumbnail.png &");
	sleep(3);
	system("eog --fullscreen invisible.png &");
	return 0;
}