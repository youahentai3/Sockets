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

    const string ip=argv[1];
    int port=atoi(argv[2]);

    struct sockaddr_in server_address;
    bzero(&server_address,sizeof(sockaddr));
    server_address.sin_family=AF_INET;
    inet_pton(AF_NET,ip.c_str(),&server_address.sin_addr);
    server_address.sin_port=htonts(port);

    int sockfd=socket(PF_INET,SOCK_STREAM,0);
    assert(sockfd>=0);
    if(connect(sockfd,(struct sockaddr*)&server_address,sizeof(server_address))<0)
    {
        cout<<"connection failed"<<endl;
    }
    else
    {
        const string oob_data="abc";
        const string normal_data="123";
        send(sockfd,normal_data.c_str(),normal_data.length(),0);
        send(sockfd,oob_data.c_str,oob_data.length(),MSG_OOB);
        send(sockfd,normal_data.c_str(),normal_data.length(),0);
    }
    close(sockfd);

    return 0;
}