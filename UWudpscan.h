#ifndef __header_h__
#define __header_h__

/*
 * UWudpscan.h
 *
 * Header file with global defines and variables
 *
 */

/*
 * Custom defines
 */
#define MAXPORT         65535
#define MINPORT         1
#define MAX_BUFF_SIZE   4096
#define THREADS_MAX     65535

/*
 * Defines for the open ports enumeration
 */
#define PORT_CLOSED     2
#define SENT_PORT       1

/*
 * Global Vars
 */
int ttimeout, numthreads;
int recvtime;
char dst_ip[16];
char filename[32];
int sports[MAXPORT];
int results[MAXPORT];

/*
 * Define all functions as extern
 */
extern void *recvudp();
extern char *addrlookup(char *address);
extern void *print_res(double time, char *times);
extern void *sendudp(unsigned short port);
#endif
