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


#define PORT 12000

int
main() {
  int sockfd, n;
  //struct sockaddr_in cliaddr;
  struct sockaddr_in servaddr;

  socklen_t len;
  char buffer[1024];
  struct timeval tv;
  tv.tv_sec = 1;
  tv.tv_usec = 0;



  memset(&servaddr, 0, sizeof(servaddr));
	//memset(&cliaddr, 0, sizeof(cliaddr));
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);





   //fill server information here too.
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = INADDR_ANY;

      len = sizeof(servaddr);


  //std::cout<<"Server address client side:" << servaddr.sin_family << servaddr.sin_port << servaddr.sin_addr.s_addr << std::endl;
  /*if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) <0) {
    perror("BIND FAILED");
  }*/



  if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        exit(0);
    } else {
      std::cout<<"Connected successfully."<<std::endl;
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
        perror("Error");
        std::cout<<"Timed out." << std::endl;
    }
//  std::cout<<sockfd <<std::endl;
  for (int i = 0; i < 10; i++) {
    //  std::cout<<&servaddr<<std::endl;
    std::cout<<"\nPlease enter msg to be sent\n"<<std::endl;
    fgets(buffer, 1024, stdin);

    /*sendto(sockfd, (char* )buffer, sizeof buffer,
          MSG_CONFIRM, (const struct sockaddr *)&servaddr, len);*/
    if (sendto(sockfd, (char* )buffer, sizeof buffer,
          MSG_CONFIRM, (const struct sockaddr *)&servaddr, len) <0 ) {
            perror("ERROR!");
            exit(0);
          }


    n = recvfrom(sockfd, (char *)buffer, sizeof(buffer),
          MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
      //    buffer[n]='\0';
          std::cout<<n<<std::endl;
          if (n==-1) {
            std::cout<<"failed to receive response." <<std::endl;
            continue;
          }
    std::cout<<"Server:"<< buffer <<  std::endl;



  }
  close(sockfd);
  return 0;
}
