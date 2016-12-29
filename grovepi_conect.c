#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#include <fcntl.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;


int main(void){

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	int flag = fcntl(socket,F_SETFL, O_NONBLOCK);
        int listen_socket = socket(AF_INET, SOCK_DGRAM);
	listen_socket.bind(("", 1982));
	fcntl(listen_socket,F_SETFL, O_NONBLOCK);
	

	if(sock == INVALID_SOCKET)
	{
    		perror("socket()");
    		printf("Dans le if\n");
		return 0;
	}
	printf("en dehors du if\n");
	return 0;
}
