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
//#define LISTEN_PORT 30356
#define LISTEN_PORT 27149 

int main(int argc, char* argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);
	
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(LISTEN_PORT);
	int s = socket(AF_INET, SOCK_STREAM, 0);

	connect(s, (sockaddr*)&sin, sizeof(sin));
	
	do {
		char input[100];
		memset(input, 0, sizeof(input));
		gets(input);

		if(strcmp(input, "quit") == 0) 
		{
			break;
		} else if(strcmp(input, "wait") == 0) {
		    char wait[100];
            recv(s, wait, sizeof(wait), 0);
            puts(wait);
            continue;
		}

		send(s, input, strlen(input), 0);	
	//	puts(input);
	}while(true);

	close(s);
    return 0;
}

