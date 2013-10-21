#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>

#include <event.h>

#include <netinet/in.h>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <event2/event.h>

#include <signal.h>
#include <unistd.h>

#include "std_inc.hpp"

#include <sys/socket.h>
#include <sys/types.h>

#define MAX_LINE 16834

//zserver
//#define LISTEN_PORT 27149 

//libevent
//#define LISTEN_PORT 30356 
//#define LISTEN_PORT 9876 

//spider
#define LISTEN_PORT 80 

#define MAX_BUF 1024

#include "../zpacket.hpp"
#include "../cmd_def.hpp"

int main(int argc, char* argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);
	
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	//sin.sin_addr.s_addr = inet_addr("119.75.217.56");
	sin.sin_addr.s_addr = inet_addr("192.168.0.107");
	sin.sin_port = htons(LISTEN_PORT);
	int s = socket(AF_INET, SOCK_STREAM, 0);

	if(connect(s, (sockaddr*)&sin, sizeof(sin)) == 0) {
		printf("connect server\n");
	} else {
		printf("unlink server\n");
		return 0;
	}
	
	fd_set read_set;
	fd_set write_set;
	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	while(true) {
		FD_ZERO(&read_set);
		FD_ZERO(&write_set);
		FD_SET(s, &read_set);	
		FD_SET(0, &read_set);	
		FD_SET(s, &write_set);	
		if(select(s+1, &read_set, &write_set, NULL, &tv) < 0) {
			break;
		}

		if(FD_ISSET(s, &read_set))	{
			int recv_size=0;
			char recv_buf[MAX_BUF];
			recv_size = recv(s, recv_buf, MAX_BUF, 0);

			if(recv_size == 0) {
				printf("unlink server\n");
				break;
			}
			
			if(recv_size < 0) {
				printf("nonblock error\n");
				break;
			}
			
			printf("revc:%s\n", recv_buf);	
		}		
		
		if(FD_ISSET(0, &read_set)) {
			int n = 0;
			int send_size=0;
			char buf[MAX_BUF];
			if (( n = read(0, buf, MAX_BUF-1))) {
				buf[n] = '\n';	
				//sscanf(buf, "%s", cmd);
				if (strcmp(buf, "quit") == 0) {
					break;
				} 
				
		    	char* request = "GET http://192.168.0.107/ HTTP/1.1 \
								 Host: 192.168.0.107\r\n";
				send_size = send(s, request, strlen(request), 0);
				printf("client send_size:%d\n", send_size);
			} 
		}
	
		/*	
		if(FD_ISSET(s, &write_set))	{
			int send_size=0;
			char send_buf[MAX_BUF];
			//sprintf(send_buf,"client send\n");
			//zpacket_t ZPacket::generate_head();

			zpacket_t pk;
			//pk.len = sizeof(zpacket_t);
			pk.len = 0;
			pk.cmd = cmd_login;
			pk.uid = 9999;
			pk.seq = 1234;
			pk.ret = 0;
		
			//send_size = send(s, send_buf, strlen(send_buf), 0);
			//char* pt = (char*)(&pk);
			//char* pt="send";	
			send_size = send(s, &pk, sizeof(zpacket_t), 0);
			printf("client send_size:%d\n", send_size);
		}	
		*/


		//break;
	}	
				
	close(s);	
	
    return 0;
}

