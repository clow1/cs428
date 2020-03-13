#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <algorithm>

#define PORT	30000
#define MAX		1024

int main() {
	char buffer1[MAX], buffer2[MAX];
	char greet[] = "Server: hello";
	int client_socket[2] = {0};

	std::string temp;
	std::string msg[20];

	int sockfd, connfd1, connfd2, cli_len, n,
		max_sd, sd, activity, info_rec;
		int opt = 1;
	fd_set readfd;


	int num_clients = 2;
	struct sockaddr_in servaddr, cli;
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cli, 0, sizeof(cli));

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd <0) {
		perror("socket creation failed...\n");
		exit(0);
	}

	//bzero(&servaddr, sizeof(servaddr));


	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &opt, sizeof(int))<0) {
		perror("setsockopt error\n");
		exit(0);
	}

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	if ((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr) )) !=0) {
		perror("Sock bind failed");
		exit(0);
	} else printf("Successfully bound to socket.\n");

	if ((listen(sockfd, 3)) <0) {
		printf("Failed to listen.\n");
		exit(0);
	} else printf("Listening\n");

	cli_len = sizeof(cli);


	if	((connfd1 = accept(sockfd, (struct sockaddr*)&cli, (socklen_t *)&cli_len)) < 0) {
		printf("Server connfd1 accepted failed.\n");
		exit(0);
	} else {
	printf("Server accepted connfd1\n");
	}
	std::cout<<"Connection from " << inet_ntoa(cli.sin_addr)
	<<" at port" <<ntohs(cli.sin_port) << "  (1)"  << connfd1 << std::endl;

	if((connfd2 = accept(sockfd, (struct sockaddr*)&cli,(socklen_t *)&cli_len))<0){
		printf("Server connfd2 accept failed.\n");
		exit(0);
	} else {
		printf("Server accepted connfd2\n");
	}

	std::cout<<"Connection from " << inet_ntoa(cli.sin_addr)
	<<" at port" <<ntohs(cli.sin_port) << " (2)"  << connfd2 << std::endl;

	

	for (int i = 0; i < num_clients; i++) {
			FD_ZERO(&readfd);
			FD_SET(sockfd, &readfd);
			FD_SET(connfd1, &readfd);
			FD_SET(connfd2, &readfd);
			max_sd = sockfd;
			if (connfd1 > max_sd) max_sd = connfd1;
			if (connfd2 > max_sd) max_sd = connfd2;
			
			
			printf("Selecting...");
			activity = select(max_sd+1, &readfd, NULL, NULL, NULL);

			if ((activity < 0) && (errno!=EINTR)) {
				printf("Select failed.\n");
			}else printf("Selected successfully.\n");

				if (FD_ISSET(connfd1, &readfd)) {

					printf("client 1 sent a message\n");

					n = read(connfd1, buffer1, sizeof(buffer1));
					temp = buffer1;
					msg[i] = temp;

			}
		
			if (FD_ISSET(connfd2, &readfd)) {
				printf("client 2 sent a message\n");
				n = read(connfd2, buffer2, sizeof(buffer2));
				temp = buffer2;
				msg[i] = temp;
				

			} 

			std::cout<<msg[i] << std::endl;
	}

	close(sockfd);
	return 0;
}
