/*
 * Uberwall UDP Scanner v1.0
 *
 * code crapp by coma
 * The scanner sends UDP messages to the target, if it don't responds
 * with a ICMP PORTUNREACH we count it as open/filtered.
 *
 * The code is very crappy because it's the first version, and it's
 * my first c programm ever written (after the hello_world.c) :p
 *
 * shoutz to: csk and khorben to take care of me :)
 * 	      all ppl from #uberwall and #phenoelit
 * 	      mercy, andrewg, nemo from ptp
 *	      and special shoutz to asia ( :) )
 *
 * 0sec r0x !!! :)
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <getopt.h>

#include "UWudpscan.h"
#include "xmas.h"

/*
 * Usage Banner
 */
char usage (char *program)
{
	/*
	 * X-Mas Special :D
	 */
	merry_xmas();
	
	fprintf(stdout, "****** ./UWudpscan UberWall UDP scanner ******\n");
	fprintf(stdout, "****** c0ded by coma <www.uberwall.org> ******\n");
	fprintf(stdout, "Usage: %s -h host -l lowerport -u higherport [-t timeout] [-n threadnumber]\n", program);
	fprintf(stdout, "\t-l\tLowerport\n");
	fprintf(stdout, "\t-u\tHigherport\n");
	fprintf(stdout, "\t-h\tHostname\n");
	fprintf(stdout, "\t-t\tTimeout\n");
	fprintf(stdout, "\t-n\tNumber of threads\n");
	fprintf(stdout, "\t-f\tSave to file\n");
	exit(EXIT_SUCCESS);
}

/*
 * Main function 
 */
int main(int argc, char *argv[])
{
	char cmdarg, *times;
	int lowerport, higherport;
	int sendport;
	int i=0, j=0;
	int jend, ttcalc;
	void *retval;
	struct timeval X;
	double x,y,total,totaltwo,totalthree,time;

	pthread_t threads[THREADS_MAX];
	pthread_t rid;

	if (argc < 3) {
		usage(argv[0]);
	}

	/*
	 * Set all to 0
	 */
	memset(dst_ip, 0, sizeof(dst_ip));
	memset(filename, 0, sizeof(filename));

	/*
	 * Default values
	 */
	ttimeout = 5;
	numthreads = 10;

	/*
	 * optarg loop
	 */
	while((cmdarg = getopt(argc, argv, "l:u:h:t:n:f:")) != EOF)
	{
		switch(cmdarg)
		{
			case 'l':
				lowerport = atoi(optarg);
				break;

			case 'u':
				higherport = atoi(optarg);
				break;

			case 'h':
				strncpy(dst_ip, addrlookup(optarg), sizeof(dst_ip));
				break;

			case 't':
				ttimeout = atoi(optarg);
				break;

			case 'n':
				ttcalc = (atoi(optarg) / numthreads);
				numthreads = atoi(optarg);
				ttimeout = (ttimeout * ttcalc -2);
				printf("%d : %d : %d\n", ttcalc, numthreads, ttimeout);
				break;
	
			case 'f':
				strncpy(filename, optarg, sizeof(filename));
				break;
			
			default:
				usage(argv[0]);
			}
	}
	
	/*
	 * checking loops
	 */
	if (lowerport < MINPORT) 
	{
		fprintf(stderr, "The staring port needs to be higher than 1\n");
		exit(EXIT_FAILURE);
	}
  	if (higherport > MAXPORT) 
	{
		fprintf(stderr, "The ending port needs to lower than 65535\n");
		exit(EXIT_FAILURE);	
	}

	/*
	 * Timing options
	 */
	gettimeofday(&X,NULL); 
	x = (double) X.tv_sec + ((double) X.tv_usec / 1.0e6);

	/*
	 * Threading stuff
	 */
	results[(higherport)] = 5;	
	if (pthread_create(&rid, NULL, (void *)recvudp, 0) < 0)
		perror("pthread_create()");

	for(i=lowerport; i<=higherport; i+=numthreads)
	{
		sendport=i;
		jend = (sendport + numthreads);

		if (higherport < jend) 
		{
			jend = (higherport);
			sendport++;
		}

		for (j=sendport; j<=jend-1; j++)
		{

			if (pthread_create (&threads[j], NULL, (void *)sendudp, (int *)j) < 0)
			{
				perror ("pthread_create()");
			} else {
			}
			if (pthread_join (threads[j], &retval) < 0)
			{
				perror ("pthread_join()");
			} else {
			}
		
		}
		sleep(ttimeout);	
	
	}
	
	while (results[higherport] != 5)
        {
		pthread_join(rid,&retval);      
		break;
	}	

	/*
	 * Calculate the used time for the scan
	 */
	gettimeofday(&X,NULL); 
	y = (double) X.tv_sec + ((double) X.tv_usec / 1.0e6);
	total = y-x;
	time = total;
	times = "seconds";
	
	if (total > 60)
	{
		totaltwo = (total/60);
		time = totaltwo;
		times = "minutes";
	} 
	if (totaltwo > 60)
	{
		totalthree = (totaltwo/60);
		time = totalthree;
		times = "hours";
	}
	
	/*
	 * Print the results
	 */
	print_res((double)time, (char *)times);

	return 0;
}
