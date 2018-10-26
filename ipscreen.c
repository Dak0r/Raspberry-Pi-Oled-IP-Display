//
// oled test program
// Written by Larry Bank
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include<errno.h> //errno
#include<sys/socket.h>
#include<netdb.h>
#include<ifaddrs.h>


#include "oled96.h"
#include "ipscreen.h"

extern unsigned char ucSmallFont[];

int main(int argc, char *argv[])
{


    char *ip;
	ip = getIp ();
    printf("printing ip to oled: %s", ip);

    int i;
    ////int oledInit(int iChannel, int iAddr, int bFlip, int bInvert)
    do{
	i=oledInit(1, 0x3c, 0, 0); // for Raspberry Pi, use channel 1
    }while(i!=0);
	if (i == 0)
	{
		oledFill(0); // fill with black
		/*oledWriteString(0,0,"OLED 96 Library!",FONT_NORMAL);
		oledWriteString(2,2,"BIG!",FONT_BIG);
		oledWriteString(3,5,"Narrow Font (6x8)", FONT_SMALL);
		for (i=0; i<64; i++)
		{
			oledSetPixel(i, 16+i, 1);
			oledSetPixel(127-i, 16+i, 1);
		}*/
        oledWriteString(3,5, ip, FONT_SMALL);
		printf("Press ENTER to quit\n");
		getchar();
		oledShutdown();
	}

    free(ip);
   return 0;
} /* main() */


char* getIp(){
    FILE *f;
    char line[100] , *p , *c;
     
    f = fopen("/proc/net/route" , "r");
     
    while(fgets(line , 100 , f))
    {
        p = strtok(line , " \t");
        c = strtok(NULL , " \t");
         
        if(p!=NULL && c!=NULL)
        {
            if(strcmp(c , "00000000") == 0)
            {
                printf("Default interface is : %s \n" , p);
                break;
            }
        }
    }
     
    //which family do we require , AF_INET or AF_INET6
    int fm = AF_INET;
    struct ifaddrs *ifaddr, *ifa;
    int family , s;
    //char host[NI_MAXHOST];
    char *host;
	host = malloc (sizeof (char) * NI_MAXHOST);
 
    if (getifaddrs(&ifaddr) == -1) 
    {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }
 
    //Walk through linked list, maintaining head pointer so we can free list later
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) 
    {
        if (ifa->ifa_addr == NULL)
        {
            continue;
        }
 
        family = ifa->ifa_addr->sa_family;
 
        if(strcmp( ifa->ifa_name , p) == 0)
        {
            if (family == fm) 
            {
                s = getnameinfo( ifa->ifa_addr, (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6) ,host , NI_MAXHOST , NULL , 0 , NI_NUMERICHOST);
                 
                if (s != 0) 
                {
                    printf("getnameinfo() failed: %s\n", gai_strerror(s));
                    exit(EXIT_FAILURE);
                }
                 
                printf("address: %s \n", host);
            }
        }
    }
 
    freeifaddrs(ifaddr);
     
    return host;
}