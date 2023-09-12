#include "headers.h"

void iMan(char* command)
{
    const char *hostname = "man.he.net";
    struct hostent *hostinfo;

    hostinfo = gethostbyname(hostname);

    if (hostinfo == NULL) {
        perror("gethostbyname");
        return ;
    }

    struct in_addr *address = (struct in_addr *)hostinfo->h_addr;
    char ip_address[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, address, ip_address, INET_ADDRSTRLEN);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return;
    }

    int port = 80;

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr = *address;

    if(connect(sockfd, (struct sockaddr *)&server_addr,sizeof(server_addr))==-1) 
    {
        perror("connect");
        close(sockfd);
        return;
    }
 
    char http_request[256];
    sprintf(http_request,"GET /?topic=%s&section=all HTTP/1.0\r\nHost: man.he.net\r\n\r\n",command);
    if (write(sockfd, http_request, strlen(http_request)) == -1) 
    {
        perror("write");
        close(sockfd);
        return;
    }



    char buffer[1024];
    int bytes_read;
    int name_flag = 0;
    int tag_flag=0;
    char ch;

    char search_string[] = "Search Again";
    size_t search_len = strlen(search_string);

    int found = 0;

    while ((bytes_read = read(sockfd, buffer, 1024 - 1)) > 0) {
        buffer[bytes_read] = '\0'; 

        char* search_result = strstr(buffer, search_string);
        if (search_result!=NULL) 
        {
            found = 1;
            break; 
        }
    }
    close(sockfd);

    if(found) 
    {
        printf("No manual entry for %s\n",command);
        return;
    }

    int sockfd2 = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd2 == -1) {
        perror("socket");
        return;
    }

    struct sockaddr_in server_addr1;
    memset(&server_addr1, 0, sizeof(server_addr1));
    server_addr1.sin_family = AF_INET;
    server_addr1.sin_port = htons(port);
    server_addr1.sin_addr = *address;

    if(connect(sockfd2, (struct sockaddr *)&server_addr1,sizeof(server_addr1))==-1) 
    {
        perror("connect");
        close(sockfd);
        return;
    }

    if(write(sockfd2, http_request, strlen(http_request)) == -1) 
    {
        perror("write");
        close(sockfd);
        return;
    }

    int bytes_read2;
    while ((bytes_read2 = read(sockfd2, &ch, 1)) == 1) 
    {
        if(tag_flag==0 && name_flag==0 && ch=='N')
        {
            name_flag++;    
        }
        if(tag_flag==0 && name_flag==1 && ch=='A')
        {
            name_flag++;
        }
        if(tag_flag==0 && name_flag==2 && ch=='M')
        {
            name_flag++;
        }
        if(tag_flag==0 && name_flag==3 && ch=='E')
        {
            name_flag++;
            printf("NAM");
        }


        if(ch=='<')
            tag_flag=1;

        if(tag_flag==0 && name_flag>3)
            putchar(ch);
        
        if(ch=='>')
            tag_flag=0;
    
    }
    close(sockfd2);
}
