#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>

#include <netinet/in.h>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>

#include <signal.h>
#include <unistd.h>

#include "std_inc.hpp"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define MAX_LINE 16834

//zserver
//#define BIND_IP "127.0.0.1"
#define BIND_IP "192.168.0.105"
#define LISTEN_PORT 12348
//#define LISTEN_PORT 80 

#define MAX_BUF 1024

//#include "../zpacket.hpp"
//#include "../cmd_def.hpp"

int main(int argc, char* argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);
	
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	//sin.sin_addr.s_addr = 0;
	sin.sin_addr.s_addr = inet_addr(BIND_IP);
	sin.sin_port = htons(LISTEN_PORT);
	int s = socket(AF_INET, SOCK_STREAM, 0);

	if( connect(s, (sockaddr*)&sin, sizeof(sin)) < 0) 
	{
		perror("sock connect failed");
		return 0;
	}
	
	fd_set read_set;
	fd_set write_set;
	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	char buf[MAX_BUF];
	FD_ZERO(&read_set);
	FD_ZERO(&write_set);
	FD_SET(0, &read_set);	

	int nfd=0;
	while(true) {
		if( (nfd = select(s+1, &read_set, &write_set, NULL, &tv)) < 0) {
			break;
		}
		
		while(nfd--) {
			if(FD_ISSET(0, &read_set)) {
				perror("kb input");
				int n = 0;
				int send_size=0;
				memset(buf, 0, MAX_BUF);
				if (( n = read(0, buf, MAX_BUF-1))) {
					printf("kb input %s\n", buf);
				}

				FD_SET(s, &write_set);	

				if(strlen(buf)){
					send_size = send(s, buf, strlen(buf)+1, 0);
					printf("client send_size:%d\n", send_size);
					memset(buf, 0, MAX_BUF);
				}

				continue;
			}

			if(FD_ISSET(s, &read_set)) {
				perror("read event");
				int recv_size=0;
				char recv_buf[MAX_BUF];
				memset(recv_buf, 0, MAX_BUF);
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
				//FD_SET(s, &write_set);	
				FD_CLR(s, &write_set);	
				FD_CLR(s, &read_set);	
				close(s);
				FD_SET(0, &read_set);
				continue;
			}		

		//	if(FD_ISSET(s, &write_set))	{
		//		perror("write event");
		//		int send_size=0;
		//		if(strlen(buf)){
		//			send_size = send(s, buf, strlen(buf)+1, 0);
		//			printf("client send_size:%d\n", send_size);
		//			memset(buf, 0, MAX_BUF);
		//		}

		//		FD_SET(s, &read_set);	
		//		FD_CLR(s, &write_set);	
		//		continue;
		//	}	
		}

	}	
				
	close(s);	
	
    return 0;
}

