//programmme for udp client
#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#include<fcntl.h>
#define PORT_NUM 1500  //port number on which message will recieve and send
#define SERVER_IP "127.127.127.127"//loop back address as i am using same system for botth server and client

int main()
{
	int sock;  //variable for socket descriptor(client)
	int len;   //variable for initialize structure length
	char out_buf[100],in_buf[100];  //variable for input and output message initialize
	
	struct sockaddr_in server;        //server address is required by client but viceversa is not needed
	sock=socket(AF_INET,SOCK_DGRAM,0);//socket descripter for server(using ipv4)
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT_NUM);  //host to network short byte word
	server.sin_addr.s_addr=inet_addr(SERVER_IP);//function 'inet_addr()' converts  the Internet host address cp from
                                                    // IPv4 numbers-and-dots notation into binary data in network byte  order.

	len=sizeof(struct sockaddr_in);    //storing length of structure (define below)
	//strcpy(out_buf,"hey server i am connecting with you..");//storing stream at out_buf for sending to server
	while(1)
	{
		printf("\n\tEnter MEssage:=");
		scanf("%[^\n]%*c",out_buf);
		sendto(sock,out_buf,(strlen(out_buf)+1),0,(struct sockaddr *)&server,len);//stream send to client through socket
                                                                                   //(here length is increase by 1 because to assign null 
										   //explicitely at the end of the stream 'out_buf')

		recvfrom(sock,in_buf,sizeof(in_buf),0,(struct sockaddr *)&server,&len);  //recieve byte by byte stream from client 
										  //at 'in_buf' through server socket
		printf("recieve from server message:=%s\n",in_buf);
	}
	close(sock);


}
