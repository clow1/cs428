CC = g++
CLIENT = udp_ping_client
SERVER = udp_ping_server
all: ./server& ./client

##Compile client
client:
	$(CC) -o udp_ping_client udp_ping_client.cpp

##Compile server
server:
	$(CC) -o udp_ping_server udp_ping_server.cpp


##Run server
rs:
	./$(SERVER)&

##Run client
rc:
	./$(CLIENT)


clean:
	-rm $(CLIENT) $(SERVER)
