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


#define PORT 12000

int
main() {

	//Initialization.
  int sockfd, n;
  struct sockaddr_in servaddr;
  socklen_t len;
  char buffer[1024];

	//used struct timeval because of the types of parameters required in setsockopt() function.
	//in other words, if we don't use struct timeval, then we cannot use setsockopt().
  struct timeval tv;
  tv.tv_sec = 1; //1 second
  tv.tv_usec = 0;


  //set memory. Dangerous but will be used here just like as shown in server code.
  memset(&servaddr, 0, sizeof(servaddr));

	//Create socket on client side.
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);


   //Fill server information here too.
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = INADDR_ANY;

	//set value of len, otherwise uninitialized
  len = sizeof(servaddr);


	//check and see if connection even works. encapsulated in if statement to account for potential error.
  if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
      perror("Connection failed");
      exit(0);
    }else {
      std::cout<<"Connected successfully."<<std::endl;
    }

		//If setting the timeout fails, then error. Not necessary, but is a safeguard.
		//encapsulated in if statement to account for potential error.
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
        perror("Error");
        std::cout<<"Timed out." << std::endl;
    }

	//Loop 10 times for 10 pings.
  for (int i = 0; i < 10; i++) {

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();


   //send empty payload. encapsulated in if statement to account for potential error.
    if (sendto(sockfd, (char* )buffer, sizeof buffer,
          MSG_CONFIRM, (const struct sockaddr *)&servaddr, len) <0 ) {
            perror("ERROR!");
            exit(0);
          }

		//listening.
          n = recvfrom(sockfd, (char *)buffer, sizeof(buffer),
          MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
          std::chrono::steady_clock::time_point done = std::chrono::steady_clock::now();
          buffer[n]='\0';
          std::cout<<"n:"<<n<<std::endl;  //Uncomment to see values of n.


					//n will be -1 if timeout or no response. Therefore check to see if n=-1.
          //Uncomment below to see server response error.
          if (n==-1) {
          //  std::cout<<"failed to receive response." << std::endl;
            continue;
          }

          std::cout<< "RTT:"<< std::chrono::duration<double>(done - start).count() << std::endl;
          //Units of RTT is calculated in seconds.


  }
  close(sockfd);
  return 0;
}
