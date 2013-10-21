#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>

#include <event.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <event2/event.h>

#include <signal.h>
#include <unistd.h>

#include "std_inc.hpp"

struct event ev;
struct timeval tv;

#define MAX_LINE 16834
#define LISTEN_PORT 30356
void time_cb(int fd, short event, void* argc)
{
	printf("timer wakeup\n");
	event_add(&ev, &tv);
}

static void signal_cb(evutil_socket_t sig, short events, void* user_data)
{
	printf("in signal_cb\n");
	event_base* base = (event_base*)user_data;
	timeval delay = { 2, 0 };
	
	event_base_loopexit(base, &delay);
}

struct fd_state {
	char buffer[MAX_LINE];
	size_t buffer_used;
	
	size_t n_written;
	size_t write_upto;
	
	struct event* read_event;
	struct event* write_event;
};

void free_fd_state(fd_state *state)
{
	event_free(state->read_event);
	event_free(state->write_event);
	free(state);
}

void do_read(evutil_socket_t fd, short events, void* arg)
{
	struct fd_state *state = (fd_state*)arg;
	//char buf[1024];
	int i;
	ssize_t result;
	puts("do_read");

	result = recv(fd, state->buffer, sizeof(state->buffer), 0);

    puts(state->buffer);
    memset(state->buffer, 0, sizeof(state->buffer_used));

	sleep(1);
	//send(fd, state->buffer, strlen(state->buffer), 0);
	/*
	while(1) {
		assert(state->read_event);
		result = recv(fd, state->buffer, sizeof(state->buffer), 0);
		if(result <= 0)
		{
			break;
		}
	
		if(state->buffer_used < sizeof(state->buffer))
		{
				printf("recv :");
				puts(state->buffer);
				//state->buffer_used += result;
				memset(state->buffer, 0, sizeof(state->buffer_used));

                gets(state->buffer);
		        event_add(state->write_event, NULL);
		        return;
		}

	}	
    
	if(result == 0) 
	{
		free_fd_state(state);
	} 
	else if(result < 0)
	{
		if(errno == EAGAIN)
		{
			return;
		}	

		perror("recv:EAGAIN");
		free_fd_state(state);
	}
	*/
}

void do_write(evutil_socket_t fd, short events, void* arg)
{
	struct fd_state *state = (fd_state*)arg;
	//char buf[1024];
	int i;
	ssize_t result;

	send(fd, state->buffer, strlen(state->buffer), 0);
	puts("do_write");
	 
	/*
	while(1) {
		assert(state->write_event);
        //char *input = gets(state->buffer);
		//if(input == NULL || strlen(state->buffer))
        //{
        //    return;
        //}
	
		if(state->buffer_used < sizeof(state->buffer))
		{
				printf("send :");
				if (strlen(state->buffer) == 0) {
				    gets(state->buffer);
				}
				puts(state->buffer);
				//state->buffer_used += result;
				//char* sendFrom = state->buffer_used + ;
				send(fd, state->buffer, strlen(state->buffer), 0);
				memset(state->buffer, 0, sizeof(state->buffer));
				return;
		}
	}	

	free_fd_state(state);
	*/
}

struct fd_state* alloc_fd_state(struct event_base* base, evutil_socket_t fd)
{
	struct fd_state* state = (fd_state*)malloc(sizeof(struct fd_state));
	if(!state)
	{
		return NULL;
	}
	
	state->read_event = event_new(base, fd, EV_READ|EV_PERSIST, do_read, state);	
	if(!state->read_event) 
	{
		free(state);
		return NULL;
	}
	
	state->write_event = event_new(base, fd, EV_WRITE|EV_PERSIST, do_write, state);
	if (!state->write_event)
	{
		event_free(state->read_event);
		free(state);
		return NULL;
	}

	state->buffer_used = state->n_written = state->write_upto = 0; 
	//assert(!state->buffer_used);
	return state;	
};

void do_accept(evutil_socket_t listener, short event, void *arg)
{
	struct event_base* base = (event_base*)arg;
	struct sockaddr_storage ss;
	socklen_t slen = sizeof(ss);
	int fd = accept(listener, (struct sockaddr*)&ss, &slen);
	if (fd < 0)
	{
		perror("accept");	
	}
	else if(fd > FD_SETSIZE)
	{
		close(fd);
	}
	else
	{
		struct fd_state* state;
		evutil_make_socket_nonblocking(fd);
		state = alloc_fd_state(base, fd);
		assert(state);
		//assert(state->write_event);
		assert(state->read_event);
		//event_add(state->write_event, NULL);
		//event_base_set(base, state->write_event);
		struct timeval five_seconds = {5,0};
		event_add(state->read_event, &five_seconds);
		event_add(state->write_event, NULL);
    	//event_base_set(base, state->read_event);
	} 
}

void run()
{
	evutil_socket_t listener;
	struct sockaddr_in sin;
	struct event_base *base;
	struct event* listener_event;
	struct event *signal_event;

	base = event_base_new();

	if(!base)
	{
		return;	
	}
	
	signal_event = evsignal_new(base, SIGINT, signal_cb, (void *)base);
	if (!signal_event || event_add(signal_event, NULL)<0) {
		//printf(stderr, "Could not create/add a signal event!\n");
		printf("Could not create/add a signal event!\n");
		return ;
	}	  

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(LISTEN_PORT);
	
	listener = socket(AF_INET, SOCK_STREAM, 0);
	evutil_make_socket_nonblocking(listener);
	
#ifndef WIN32
	{
		int one = 1;
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));	
	}
#endif
	
	if(bind(listener, (struct sockaddr*)&sin, sizeof(sin)) < 0)
	{
		perror("bind");
		return;
	}
	
	if(listen(listener, 16)<0)
	{
		perror("listen");
		return;
	}
	
	listener_event = event_new(base, listener, EV_READ|EV_PERSIST, do_accept, (void*)base);
	event_add(listener_event, NULL);
	event_base_dispatch(base);	
	event_free(signal_event);
}

int main(int argc, char* argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);

	run();

/*	
	struct event_base *base = event_init();	
	
	tv.tv_sec = 0;
	tv.tv_usec = 100;
	evtimer_set(&ev, time_cb, NULL);
	event_add(&ev, &tv);
	event_base_dispatch(base);
*/
    return 0;
}

