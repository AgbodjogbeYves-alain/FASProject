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
#define DEBUGGING false
#define HELLO_PORT 1982
#define HELLO_GROUP "239.255.255.250"
#define MSGBUFSIZE 256

void debug(msg):
  if DEBUGGING:
    printf("%s",msg);

void send_search_broadcast():
{
     int fd, cnt;
     struct ip_mreq mreq;
     char *msg="M-SEARCH * HTTP/1.1\r\n";
     strcat(msg, "HOST: 239.255.255.250:1982\r\n");
  	 strcat(msg,"MAN: \"ssdp:discover\"\r\n");
  	 strcat(msg,"ST: wifi_bulb");
  	 debug("send search request")
     /* create what looks like an ordinary UDP socket */
     if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
	  perror("socket");
	  exit(1);
     }

     /* set up destination address */
     memset(&addr,0,sizeof(addr));
     addr.sin_family=AF_INET;
     addr.sin_addr.s_addr=inet_addr(HELLO_GROUP);
     addr.sin_port=htons(HELLO_PORT);
     
     /* now just sendto() our destination! */
     while (1) {
	  if (sendto(fd,msg,sizeof(msg),0,(struct sockaddr *) &addr,sizeof(addr)) < 0) {
	       perror("sendto");
	       exit(1);
	  }
	  sleep(1);
     }
}

void listner(){

	 struct sockaddr_in addr;
	 int fd, nbytes,addrlen;
	 struct ip_mreq mreq;
	 char msgbuf[MSGBUFSIZE];

	 u_int yes=1;            /*** MODIFICATION TO ORIGINAL */

	 /* create what looks like an ordinary UDP socket */
	 if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
	  perror("socket");
	  exit(1);
	 }


	/**** MODIFICATION TO ORIGINAL */
	/* allow multiple sockets to use the same PORT number */
	if (setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0) {
	   perror("Reusing ADDR failed");
	   exit(1);
	   }
	/*** END OF MODIFICATION TO ORIGINAL */

	 /* set up destination address */
	 memset(&addr,0,sizeof(addr));
	 addr.sin_family=AF_INET;
	 addr.sin_addr.s_addr=htonl(INADDR_ANY); /* N.B.: differs from sender */
	 addr.sin_port=htons(HELLO_PORT);
	 
	 /* bind to receive address */
	 if (bind(fd,(struct sockaddr *) &addr,sizeof(addr)) < 0) {
	  perror("bind");
	  exit(1);
	 }
	 
	 /* use setsockopt() to request that the kernel join a multicast group */
	 mreq.imr_multiaddr.s_addr=inet_addr(HELLO_GROUP);
	 mreq.imr_interface.s_addr=htonl(INADDR_ANY);
	 if (setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0) {
	  perror("setsockopt");
	  exit(1);
	 }

	 /* now just enter a read-print loop */
	 while (1) {
	  addrlen=sizeof(addr);
	  if ((nbytes=recvfrom(fd,msgbuf,MSGBUFSIZE,0,
			       (struct sockaddr *) &addr,&addrlen)) < 0) {
	       perror("recvfrom");
	       exit(1);
	  }
	  puts(message);
	}
}
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
	else{
		printf("en dehors du if\n");
		multicase_address = (MCAST_GRP, 1982) 
	  	debug("send search request")
	  	msg = "M-SEARCH * HTTP/1.1\r\n" 
	  	msg = msg + "HOST: 239.255.255.250:1982\r\n"
	  	msg = msg + "MAN: \"ssdp:discover\"\r\n"
	  	msg = msg + "ST: wifi_bulb"
	  	scan_socket.sendto(msg, multicase_address)
	}
	

}
