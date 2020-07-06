#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cassert>
#include <cstring>
#include <unistd.h>

#define BUF_SIZE 1024

using namespace std;

int main(int argc,char** argv)
{
    if(argc<=2)
    {
        cout<<"error input"<<endl;
    }

    const char* ip=argv[1];
    int port=atoi(argv[2]);

    struct sockaddr_in address;
    bzero(&address,sizeof(address));
    address.sin_family=AF_INET;
    inet_pton(AF_INET,ip,&address.sin_addr);
    address.sin_port=htons(port);

    int sock=socket(PF_INET,SOCK_STREAM,0);
    assert(sock>=0);

    int ret=bind(sock,(struct sockaddr*)&address,sizeof(address));
    assert(ret!=-1);

    struct sockaddr_in client;
    socklen_t client_addrlength=sizeof(client);
    int connfd=accept(sock,(struct sockaddr*)&client,&client_addrlength);

    if(confd<0)
    {
        cout<<"error"<<endl;
    }
    else
    {
        char buffer[BUF_SIZE];

        memset(buffer,0,BUF_SIZE);

        ret=recv(connfd,buffer,BUF_SIZE-1,0);
        string rec=buffer;
        cout<<ret<<" "<<rec;

        ret=recv(connfd,buffer,BUF_SIZE-1,MSG_OOB);
        rec=buffer;
        cout<<ret<<" "<<rec;

        ret=recv(connfd,buffer,BUF_SIZE-1,0);
        rec=buffer;
        cout<<ret<<" "<<rec;

        close(connfd);
    }
    close(sock);

    return 0;
}