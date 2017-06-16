#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <limits>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

static const int MAXNUMBEROFCLIENTS = 20;

struct threadargs{
	int clients[MAXNUMBEROFCLIENTS];
	int connfd;
};

int menu();
int connect(int portno);
void *client(void *arguments);
int broadcast(threadargs* args, char buffer[1024]);


int main(int argc, char* argv[]){
	int portno = menu();
	connect(portno);
}

int menu(){
	int portno;

	cout << "Please enter a Port Number to connect over: " << endl;
	cin >> portno;
	while(cin.fail()){
		cout << "Enter an Integer for the port number. \n" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please enter a Port Number to connect over: " << endl;
		cin >> portno;
	}

	if(portno > 65536 || portno < 1024){
		cout << "The portno must be between 1024 and 65536" << endl;
		menu();
	}
	return portno;
}

int connect(int portno){
	int sockfd, option = 1;
	struct sockaddr_in serv_addr;
	threadargs args;

	for(int i = 0; i < MAXNUMBEROFCLIENTS; ++i){
		args.clients[i] = -1;
	}

	cout << portno << endl;

	cout << "Creating Socket......" << endl;
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		cout << "Error creating Socket" << endl;
		exit(1);
	}

	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&option, sizeof(int)) < 0){
		cout << "unable to set socket options to reuse address" << endl;
		cout << "Try another port..." << endl;
		menu();
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);



	cout << "Binding Socket......." << endl;
	if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
		cout << "Error Binding Socket, Try another port" << endl;
		menu();
	}

	cout << "Listening on Socket....." << endl;
	if(listen(sockfd, MAXNUMBEROFCLIENTS) < 0){
		cout << "Unable to Listen on Socket" << endl;
		exit(1);
	}

	//will need to change based on number of client connects
	pthread_t thread[MAXNUMBEROFCLIENTS];
	int threadcount = 0; 
	int numberofclients = 0;
	for(;;){
		struct sockaddr_in client_addr;
		int connfd;
		cout << "accepting client...." << endl;
		if((connfd = accept(sockfd, (struct sockaddr*)&client_addr, (socklen_t*)sizeof(client_addr))) < 0){
			cout << "Unable to accept connection" << endl;
			//do something 
		}

		args.clients[numberofclients] = connfd;
		++numberofclients;
		args.connfd = connfd;

		cout << "Spawning New Thread" << endl;
		if(pthread_create(&thread[threadcount++], NULL, &client, (void *)&args) < 0){
			cout << "Thread Creation Error" << endl;
			//do something with error
		}
		if(threadcount == MAXNUMBEROFCLIENTS){
			cout << "Max Number of Clients Reached" << endl;
		}
	}
	close(sockfd);
}

void *client(void *arguments){
	threadargs *args = (threadargs *)arguments;
	fd_set readfds;
	struct timeval tv;
	char buffer[1024];
	int sockfd, n, rv, nbytes;

	sockfd = args ->connfd;
	FD_ZERO(&readfds);
	FD_SET(sockfd, &readfds);

	//Timeout client after 25min
	tv.tv_sec = 1600;
	n = sockfd + 1;
	//Let Everyone know someone has Joined

	//while loop const checking for recv data
	for(;;){
		if((rv = select(n, &readfds, NULL, NULL , &tv)) < 0){
			cout << "Select Error on thread" << endl;
			//do we want to exit here??
			exit(1);
		}
		//zero buffer
		bzero(buffer, sizeof(buffer));
		if((nbytes = recv(sockfd, buffer, sizeof(buffer), 0)) < 0){
			cout << "Error in Recv Data" << endl;
			//do we want to exit here??
			exit(1);
		}
		//check if recv whole message?
		broadcast(args, buffer);

	}
	return NULL;

	//allow sending of message and receieving of messages here
	//allow link to broadcast/ private message for username

}

int broadcast(threadargs* args, char buffer[1024]){
	fd_set sendfds;
	struct timeval tv;
	FD_ZERO(&sendfds);
	int n, sd;

	for(int i = 0; i < MAXNUMBEROFCLIENTS ; i++){
		if(args->clients[i] != -1 && args->clients[i] != args->connfd){
			FD_SET(args->clients[i], &sendfds);
			n = args -> connfd + 1;
		}
	}

	if((sd = select(n, &sendfds, NULL, NULL , &tv)) < 0){
			cout << "Select Error on thread send" << endl;
			//do we want to exit here??
			exit(1);
	}

	//send
	return 0;
	//loop through connfds stored in args and send message
}


//allows mult client connects
//recvs and broadcast
	// socket
	//bind
	//listen
	//accept
	//send()
	//recv()

//Things to keep in mind
	// if someone leaves need to shift values in conn arry in pthread args