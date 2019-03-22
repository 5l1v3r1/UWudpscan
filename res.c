#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#include "UWudpscan.h"

void *print_res(double time, char *times)
{
        int i;
        struct servent *serv;
        FILE *log;

        fprintf(stdout, "Port\tState\t\tService\n");
        if (strcmp(filename, "") != 0)
        {
                log = fopen(filename, "a");
                if(log == NULL)
                {
                        fprintf(stderr, "Error opening logfile: %s\n", filename);
                        exit(EXIT_FAILURE);
                }
                fprintf(log, "\nLogfile created by UWudpscan\n\n");
                fprintf(log, "Port\tState\t\tService\n");                                                               
        }
        
        for (i=0;i<MAXPORT;i++)
        {
                if (sports[i] == SENT_PORT) {
                        if (results[i] == PORT_CLOSED)
                        {
                                if ((serv = getservbyport(htons(i), "udp")) != (struct servent *) NULL)
                                {
                                } else {
                                }
                        } else { 
                        
                                if ((serv = getservbyport(htons(i), "udp")) != (struct servent *) NULL)
                                {
                                        if (strcmp(filename, "") != 0)
                                        {
                                                fflush(log);
                                                fprintf(log, "%d\tOPEN/FILTERED\t%s\n", i, serv->s_name);
                                                fflush(log);
                                        }
                                        fprintf(stdout, "%d\tOPEN/FILTERED\t%s\n", i, serv->s_name);
                                } else {
                                        if (strcmp(filename, "") != 0)
                                        {
                                                fflush(log);
                                                fprintf(log, "%d\tOPEN/FILTERED\tUnknown\n", i );
                                                fflush(log);
                                        }
                                        fprintf(stdout, "%d\tOPEN/FILTERED\tUnknown\n", i );
                                }                       
                        }
                }
        }
        if (strcmp(filename, "") != 0)
                fclose(log);

        if (strcmp(filename, "") != 0)
        {
                log = fopen(filename, "a");
                if(log == NULL)
                        fprintf(stderr, "Error opening logfile: %s\n", filename);
                fprintf(log, "\nFinished scan for a total of %lu %s\n", (long)time, (char *)times);
                fclose(log);
	}
	fprintf(stdout, "\nFinished scan for a total of %lu %s\n", (long)time, (char *)times);

	return 0;
}
