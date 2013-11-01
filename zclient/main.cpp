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

#define MAX_LINE 16834

//zserver
#define LISTEN_PORT 27149 

#define MAX_BUF 1024

#include "../zpacket.hpp"
#include "../cmd_def.hpp"

int main(int argc, char* argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);
	
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(LISTEN_PORT);
	int s = socket(AF_INET, SOCK_STREAM, 0);

	connect(s, (sockaddr*)&sin, sizeof(sin));
	
	fd_set read_set;
	fd_set write_set;
	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	FD_ZERO(&read_set);
	FD_ZERO(&write_set);

	char buf[MAX_BUF];

	while(true) {
		FD_SET(0, &read_set);	

		if(select(s+1, &read_set, &write_set, NULL, &tv) < 0) {
			break;
		}

		if(FD_ISSET(s, &read_set))	{
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
			FD_SET(s, &write_set);	
		}		
		
		if(FD_ISSET(0, &read_set)) {
			int n = 0;
			int send_size=0;
			memset(buf, 0, MAX_BUF);
			if (( n = read(0, buf, MAX_BUF-1))) {
				printf("kb input %s\n", buf);
			}

			FD_SET(s, &write_set);	
		}
		
		if(FD_ISSET(s, &write_set))	{
			int send_size=0;
			if(strlen(buf)){
				send_size = send(s, buf, strlen(buf)+1, 0);
				printf("client send_size:%d\n", send_size);
			}

			FD_SET(s, &read_set);	
		}	
	}	
				
	close(s);	
	
    return 0;
}

