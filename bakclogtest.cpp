#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cassert>
#include <cstring>
#include <unistd.h>

using namespace std;

int main(int argc,char** argv)
{
    if(argc<=2)
    {
        cout<<"error input"<<endl;
    }

    const char* ip=argv[1];
    int port=atoi(argv[2]);

    struct sockaddr_in server_address;
    bzero(&server_address,sizeof(sockaddr));
    server_address.sin_family=AF_INET;
    inet_pton(AF_NET,ip,&server_address.sin_addr);
    server_address.sin_port=htons(port);

    int sockfd=socket(PF_INET,SOCK_STREAM,0);
    assert(sockfd>=0);
    if(connect(sockfd,(struct sockaddr*)&server_address,sizeof(server_address))<0)
    {
        cout<<"connection failed"<<endl;
    }
    else
    {
        const char* oob_data="abc";
        const char* normal_data="123";
        send(sockfd,normal_data,strlen(normal_data),0);
        send(sockfd,oob_data,strlen(oob_data0),MSG_OOB);
        send(sockfd,normal_data,strlen(normal_data),0);
    }
    close(sockfd);

    return 0;
}