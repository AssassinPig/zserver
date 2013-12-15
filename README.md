这是一个自用网络框架
目前只如下几个模型
1， simple_server 这是单进程 异步 非阻塞的简单实例
2， mini web server 这是一个父进程负责管理 多个子进程当worker进程的server (html方面没有太多的涉及, 准备放在爬虫工程里面来搞)
3， proxy logic proxy将逻辑hash散射到logic 准备把proxy当成一个有负载的调度server， 而logic作为纯worker server(跟2的区别是logic可以放在其他物理机上) 
4， gateway center worker gateway实现负载 center管理所有worker worker是业务的服务器

其他测试程序稍后继续, 目前只有对simple的测试， 72m无线网卡+100m无线路由器，开虚拟机可以达到20~30%的网络流量，物理机上应该可更高一些


依赖的库
pthread
boost
protobuf

author: assassinpig
email: assassinpig@gmail.com

目前版本的问题:
zstream 目前只有10k的缓冲区大小 这样就不支持连续读取大数据了，准备着手进行改造一下
