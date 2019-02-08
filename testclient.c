#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>


int main(int argc, char** argv)
{
	int socket_fd = 0;
	struct sockaddr_in server_address;
	struct hostent *server = NULL;
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd < 0)
	{
		fprintf(stderr, "Error in libnetfiles socket() errno = %d\n", errno);
		return -1;
	}

	server = gethostbyname(argv[1]);
	
	if(server == NULL)
	{
		errno = 0;
		h_errno = HOST_NOT_FOUND;
		printf("stderr, Host Not Found libnetfiles, h_errno");
		return -1;
	}

	bzero((char *) &server_address, sizeof(server_address));
    	server_address.sin_family = AF_INET;
    	memcpy((char *)server->h_addr, (char *)&server_address.sin_addr.s_addr, server->h_length);
    	server_address.sin_port = htons(atoi(argv[2]));
	
	if(connect(socket_fd,(struct sockaddr *)&server_address, sizeof(server_address)) < 0)
	{
        	fprintf(stderr,"Cannot connect : libnetfiles %s, errno= %s\n", argv[1], strerror(errno));
    		return -1;
    	}
	return socket_fd;
}

