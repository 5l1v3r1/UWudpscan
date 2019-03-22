/*
 * X-MAS Special :)
 */

#define                 RED             printf("\033[1;31m")
#define                 CLEAR           printf("\033[2J\033[1;1H")

void merry_xmas(void)
{
	 CLEAR;
	 fflush(stdout); sleep(1);
	 printf("\033[1;31m                                  |\n");
	 printf("\033[1;31m                                \\ ' /\n");
	 printf("\033[1;31m                              -- (*) --\n");
	 printf("\033[1;31m                                 >*<\n");
	 printf("\033[1;31m                                >0<@<\n");
	 printf("\033[1;31m                               >>>@<<*\n");
	 printf("\033[1;31m                              >@>*<0<<<\n");
	 printf("\033[1;31m                             >*>>@<<<@<<\n");
	 printf("\033[1;31m                            >@>>0<<<*<<@<\n");
	 printf("\033[1;31m                           >*>>0<<@<<<@<<<\n");
	 printf("\033[1;31m                          >@>>*<<@<>*<<0<*<\n");
	 printf("\033[1;31m            '~'          >0>>*<<@<>0><<*<@<<\n");
	 printf("\033[1;31m        ___''U''___     >*>>@><0<<*>>@><*<0<<\n");
	 printf("\033[1;31m        |   | |   |    >@>>0<*<0>>@<<0<<<*<@<<\n");
	 printf("\033[1;31m        |  | | _(UU)_ >((*))_>0><*<0><@<<<0<*<\n");
	 printf("\033[1;31m        | | || / //||.*.*.*.|>>@<<*<<@>><0<<<\n");
	 printf("\033[1;31m        |  _|_|&&_// ||*.*.*.*|__db//\n");
	 printf("\033[1;31m        """"|'.'.'.|~~|.*.*.*|     ____|\n");
	 printf("\033[1;31m            |'.'.'.|   ^^^^^^|____|>>>>>>|\n");
	 printf("\033[1;31m            ~~~~~~~~         '""""`------'\n\n\n");
	 fflush(stdout); sleep(1);
	 
	 RED;
	 printf("\033[01A\t\t\t\t     M e r r y  X - M A S\n\n");
	 fflush(stdout); sleep(1);
	 RED;
	 fflush(stdout); sleep(1);
	 printf("\n\n");
	 printf("\t\t\t\033[02A   from coma@uberwall.org\n\n");
	 sleep(3);

}

