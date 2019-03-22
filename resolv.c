#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "UWudpscan.h"

/*
 * Resolving the hostname
 */
char * addrlookup(char * address)
{
        struct hostent *resolv;
        struct in_addr *addr;

        resolv = (struct hostent *)gethostbyname(address);
        if (resolv == NULL)
        {
                fprintf(stderr, "Address not found for %s\n",address);
                exit(EXIT_FAILURE);
        }
        else
        {
                addr = (struct in_addr *) resolv->h_addr_list[0];
                fprintf(stderr, "The IP address of %s is %s\n",address, inet_ntoa(*addr));
                return (char *)inet_ntoa(*addr);
        }
}
