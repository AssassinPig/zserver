#include "zmini_web_server.hpp"
#include "zlog.hpp"
#include "com_inc.hpp"
#include "com_macro.hpp"
#include "zsocket.hpp"
#include "zsocket_util.hpp"
#include "zprocess_util.hpp"

//ZModule* g_network = NULL;

void child_process(int i, int readfd, sem_t* pmutex, ZMiniWebServer::child_process_status* status)
{
	for(;;) {
		int newconnfd = -1;
                ZRecvFD(readfd, &newconnfd);

		char recvbuf[1024];
		memset(recvbuf, 0, 1024);
		int nread;
		while( (nread = recv(newconnfd, recvbuf, 1024, 0)) <= 0) {
			if(errno == EINTR || errno == EAGAIN) {
				continue;
			} 	
			
			if(nread == 0) 
				perror("recv failed");

			printf("error = %s\n", strerror(errno));
		}  
		//printf("child %d recv %s\n", i, recvbuf);

		sprintf(recvbuf, "hello world");
		int nsend = send(newconnfd, recvbuf, strlen(recvbuf), 0);
                
                sem_wait(pmutex);
                *status = ZMiniWebServer::child_process_status_available; 
                sem_post(pmutex);

		close(newconnfd);
	}
}

ZMiniWebServer::ZMiniWebServer(int child_num) : ZServer()
{
    m_childnum = child_num;
}

ZMiniWebServer::~ZMiniWebServer()
{

}

int ZMiniWebServer::init()
{   
    set_signal();
    m_active = true;

    m_thread = new AcceptThread;
    m_listensocket = new ZSocket(ZTCPSocket());

    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZMiniWebServer::startup(const char* bind_ip, int port)
{
    m_childprocess = (child_process_info*)malloc(sizeof(child_process_info)*m_childnum);
    memset(m_childprocess, 0, sizeof(child_process_info)*m_childnum);

   m_childstatus = (child_process_status*)malloc(sizeof(child_process_status)*m_childnum);

        for(int i=0;i<m_childnum;++i) {
            m_childstatus[i] = child_process_status_available;
        }

        sem_t mutex; 
	int fd = open("/tmp/mini_web_server_sem", O_RDWR|O_CREAT, S_IRWXU);
	write(fd, &mutex, sizeof(sem_t)); 
	m_childmutex = (sem_t*)mmap(NULL, sizeof(sem_t), PROT_EXEC|PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0); 
	if(!m_childmutex) 
		perror("mmap memory failed");

        if(!sem_init( m_childmutex, 1, 1) == 0) {
            perror("sem_init failed"); 
        }

	int fd2 = open("/tmp/mini_web_server_status", O_RDWR|O_CREAT, S_IRWXU);
	write(fd2, &m_childstatus, sizeof(child_process_status)*m_childnum); 
	child_process_status* childstatus = (child_process_status*)mmap(NULL, sizeof(child_process_status)*m_childnum, PROT_EXEC|PROT_WRITE|PROT_READ, MAP_SHARED, fd2, 0); 
        if(!childstatus) {
            perror("map childstatus failed");
        }

        for(int i=0;i<m_childnum;++i) {
            childstatus[i]= child_process_status_available;
        }

    for(int i=0; i<m_childnum; ++i) {
        pid_t pid = -1;
        ZLocalSocketpair(m_childprocess[i].sockfd);
        if((pid = fork()) < 0) {
            perror("fork failed");
        } else if(pid > 0) {
            m_childprocess[i].child_pid = pid;     
            close(m_childprocess[i].sockfd[0]);
            //close(m_childprocess[i].notifyfd[1]);
        } else {
            //child process
            close(m_childprocess[i].sockfd[1]);
            //close(m_childprocess[i].notifyfd[0]);
            child_process(i, m_childprocess[i].sockfd[0], m_childmutex, &(childstatus[i]));          
            _exit(0); 
        }
    }
    close(fd);

    m_thread->Startup(this);  
    m_listensocket->Bind(bind_ip, port);
    m_listensocket->Listen(m_listensocket->GetFD(), 10);
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZMiniWebServer::loop()
{
    while(m_childnum) {
        int status = -1;
        waitpid(-1, &status, 0);
        m_childnum--;
    }

    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

int ZMiniWebServer::exit()
{
    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}

ZMiniWebServer::child_process_info* ZMiniWebServer::GetChildInfo()
{
    return m_childprocess;
}

ZSocket* ZMiniWebServer::GetSocket()
{
    return m_listensocket;
}

sem_t* ZMiniWebServer::GetChildSem()
{
    return m_childmutex; 
}

int ZMiniWebServer::GetChildNum()
{
    return m_childnum;
}

ZMiniWebServer::child_process_status* ZMiniWebServer::GetChildStatus()
{
    return m_childstatus;
}

int ZMiniWebServer::AcceptThread::ThreadFun(void* param) 
{
   ZMiniWebServer* server = (ZMiniWebServer*)param;
   ZSocket* socket = server->GetSocket();
   sem_t* pmutex = server->GetChildSem();
   int childnum = server->GetChildNum(); 
   ZMiniWebServer::child_process_status* childstatus = server->GetChildStatus();
    ZMiniWebServer::child_process_info* childinfo = server->GetChildInfo();

   while(Status() == ZThread::zthread_status_idle) {
       int recvFD = ZAccept(socket->GetFD(), NULL, 0);

       sem_wait(pmutex);
       int i=0;
       for(; i<childnum; ++i) {
           //printf("child process access count %d\n", (*pcount)++);	
            if(childstatus[i] == child_process_status_available) {
                ZSendFD(childinfo[i].sockfd[1], recvFD);  
                childstatus[i] = child_process_status_busy;
                break;
            }
       }

       if(i==childnum) {
            //no enough resource
            //to do
            close(recvFD);
       }
       
       sem_post(pmutex);
   }

    FUN_NEEDS_RET_WITH_DEFAULT(int, 0)
}
