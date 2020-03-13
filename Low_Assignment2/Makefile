CC = g++
CFLAGS = -Wall -Wextra -pedantic -g -o

all: client server rs rc

##Compile client
client:
	$(CC) $(CFLAGS) client client.cpp

##Compile server
server:
	$(CC) ${CFLAGS} server server.cpp


##Run server
rs:
	./server&

##Run client
rc:
	./client


clean:
	-rm client
	-rm server
