#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#define __FAVOR_BSD
#include <netinet/udp.h>

#include "UWudpscan.h"

/*
 * Receiving thread
 * It's just an icmp socket, if we get an PORTUNREACH back the port is closed
 * if we get nothing back the port is open for us.
 */
void *recvudp()
{
        int icmpsocket, recvcheck, packetcheck;
	char recvbuff[MAX_BUFF_SIZE];
        struct sockaddr_in src_addr;
        fd_set socks;
        struct timeval timeout;

	struct icmphdr *icmph;
        struct iphdr *iph;
        struct udphdr *udph;
		
	if ( (icmpsocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP) ) < 0)
        {
                perror("socket()");
                exit(EXIT_FAILURE);
        }

        src_addr.sin_family = AF_INET;
        src_addr.sin_addr.s_addr = INADDR_ANY;
        src_addr.sin_port = htons(0);

        /*
	 * The for loop is as long until the main function joins this thread
	 * to finish it.
        */

        for (;;)
        {
                timeout.tv_sec = (ttimeout-2);
                timeout.tv_usec = 400;
                
		FD_ZERO(&socks);
                FD_SET(icmpsocket,&socks);
                
                if((recvcheck = select(FD_SETSIZE, &socks, (fd_set *)0, (fd_set *)0, &timeout)) < 0)
                {
                        perror("select");
                        exit(EXIT_FAILURE);
                
                } 
                if (recvcheck != 0)
                {
                        if (FD_ISSET(icmpsocket, &socks))
                                if ((packetcheck = recvfrom(icmpsocket, &recvbuff, sizeof(recvbuff), 0x0, NULL, NULL)) < 0)
                                {
                                        perror("recvfrom()");
                                        exit(EXIT_FAILURE);
                                }
			
			iph = (struct iphdr *)recvbuff;
			icmph = (struct icmphdr *)(recvbuff + sizeof(struct iphdr));
			udph = (struct udphdr *)((char *)icmph +  sizeof(struct icmphdr) + sizeof(struct iphdr));
			
			results[htons(udph->uh_dport)] = PORT_CLOSED;
												
		} 
        }       
        
        close(icmpsocket);
        pthread_exit(0);
}

