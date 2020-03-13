#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<sys/time.h>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>


#define PORT 30000

int
main() {

	//Initialization.
  int sockfd;
  int n, inforec, msg;
  struct sockaddr_in servaddr, cliaddr;
  
  char buffer[1024] = {0};
	char sub[] = "bye";
  std::string temp;

  memset(&servaddr, 0, sizeof(servaddr));
  memset(&cliaddr, 0, sizeof(cliaddr));


  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) <0) {
    perror("failed to  create client socket");
    exit(0);
  }


  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = INADDR_ANY;
	

  if((n = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)))<0)
    {
      perror("Connection failed");
      exit(0);

    }

		std::cout<<"Write:" << std::endl;
		std::cin>>buffer;
		if ((msg = write(sockfd, buffer, sizeof(buffer))) < 0) {
     	 perror("Client:Msg cannot be sent.");
     	 exit(0);
    } temp = buffer;
		
				bzero(buffer, sizeof(buffer));

		if ((inforec = read(sockfd, buffer, sizeof(buffer)))<0) {
  		  perror("Could not read");
  		  exit(0);
  	} 

	
  	
	
    //std::cout<<"Buffer: " << buffer << std::endl;

    close(sockfd);

}
