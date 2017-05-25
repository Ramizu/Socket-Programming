#include<stdio.h> 	
#include<string.h>    	
#include<sys/socket.h>	
#include<arpa/inet.h> 	
#include <unistd.h>  
#include <netdb.h>   

const int MAX_HOSTNAME = 255;


int main(int argc , char *argv[])
{
    int sock ,la_len ,ret ,hostName , i ,j , len ,retrn;
    struct sockaddr_in localaddr, peeraddr, addr; 
    int getsockname(int sock, struct sockaddr *addr, socklen_t *len);
    char hostbuffer[MAX_HOSTNAME+1];
    struct hostent *hp;
    struct servent *sp;

     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

	//CHAPTER 4

	

	la_len = sizeof(localaddr);
	ret = getsockname(sock,(struct sockaddr *)&localaddr,&la_len);		//func 1
	
	if (ret == 0) {
	  printf("Local Address is : %s\n", inet_ntoa(localaddr.sin_addr));
	  printf("Local Port is : %d\n", localaddr.sin_port);
	}

	hostName = gethostname (hostbuffer, MAX_HOSTNAME);						//func 2
	if (hostName == 0){
			printf("Hostname is %s\n", hostbuffer);
	}

	hp = gethostbyname( "www.microsoft.com");							//func 3
	
	if (hp){
		printf("h_name is %s\n", hp->h_name);
		printf("h_addrtype is %d\n", hp->h_addrtype);
		
		i=0;
		printf("Aliases: \n" );
		while(1){
			if ( hp->h_aliases[i] ) 
			{
				printf( "h_aliases[%d] = %s\n", i, hp->h_aliases[i] );
				i++;
			}
			else break;
		}
		
		i=0;
		printf( "Addresses:\n" );
		while (1) 
		{
			if ( hp->h_addr_list[i] ) 
			{
				struct in_addr theAddr;
				memcpy( &theAddr.s_addr, hp->h_addr_list[i], sizeof(theAddr.s_addr) );
				printf( "  h_addr_list[%d] = %s\n", i, inet_ntoa( theAddr ) );
				i++;
			}
			else break;
		}
	}

	sp = getservbyname( "smtp", "tcp" );								//func 4

	if (sp) 
	{
	  printf( "s_name  = %s\n", sp->s_name );
	  printf( "s_port  = %d\n", ntohs(sp->s_port) );
	  printf( "s_proto = %s\n", sp->s_proto );

	  j = 0;
	  printf( "Aliass:\n" );
	  while (1) 
	  {
		if ( sp->s_aliases[j] ) 
		{
		  printf(" s_aliases[%d] = %s\n", j, sp->s_aliases[j] );
		  j++;
		} else break;
	  }

	}

	sp = getservbyport(htons(80), NULL);									//func 5
	if (sp)
	{
		printf("Service %s is at port %d\n", sp->s_name, ntohs( sp->s_port));
	}


	//CHAPTER 6
	
	

	//func 1
	struct sockaddr_in saddr;
	char address[]={"192.168.1.1"};

	saddr.sin_addr.s_addr = inet_addr(address);

	if(saddr.sin_addr.s_addr = 0xffffffff){
		struct hostent *hptr = (struct hostent *)gethostbyname(address);
		if (hptr == NULL)
		{
			printf("Can't esolve the address");
		}
		else 
		{
			struct in_addr **addrs;
			addrs = (struct in_addr **)hptr->h_addr_list;
			memcpy( &saddr.sin_addr, *addrs, sizeof(struct in_addr) );
		}
	}

	//func 2
	sock = socket (AF_INET, SOCK_STREAM, 0);

	len = sizeof(peeraddr);
	retrn = getpeername(sock, (struct sockaddr *)&peeraddr, &len);
	printf("Peer address: %s\n", inet_ntoa(peeraddr.sin_addr));
	printf("Peer port: %d\n",ntohs(peeraddr.sin_port));
	
	return 0;

		

}