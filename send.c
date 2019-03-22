#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "UWudpscan.h"

/*
 * Sending UDP thread
 */
void *sendudp(unsigned short port) 
{
        int udpsocket;
        struct sockaddr_in trgt_addr;

        trgt_addr.sin_family = AF_INET;
        trgt_addr.sin_addr.s_addr = inet_addr(dst_ip);
        trgt_addr.sin_port = htons(port);

        if (( udpsocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        {
                perror("socket()");
                exit(EXIT_FAILURE);
        }

        
	if (( connect(udpsocket, (struct sockaddr*)&trgt_addr, sizeof(trgt_addr))) < 0)
        {
                perror("Connect()");
                exit(EXIT_FAILURE);
        }
                
        if (( sendto(udpsocket, NULL, 0, 0, (struct sockaddr*)&trgt_addr, sizeof(trgt_addr))) < 0)
        {
                perror("sendto");
                exit(EXIT_FAILURE);
        } else {
                sports[port] = SENT_PORT;
        }

        close(udpsocket);       
        pthread_exit(0);
}
