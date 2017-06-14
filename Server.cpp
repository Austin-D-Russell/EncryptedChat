#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <limits>
#include <netinet/in.h>
#include <pthread.h>

using namespace std;

static int MAXNUMBEROFCLIENTS = 20;

int menu();
int connect(int portno);
void *client(void *arguments);

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
	int i = 0; 

	for(;;){
		struct sockaddr_in client_addr;
		int connfd;
		cout << "accepting client...." << endl;
		if((connfd = accept(sockfd, (struct sockaddr*)&client_addr, (socklen_t*)sizeof(client_addr))) < 0){
			cout << "Unable to accept connection" << endl;
			//do something 
		}

		cout << "Spawning New Thread" << endl;
		if(pthread_create(&thread[i++], NULL, &client, (void *)&connfd) < 0){
			cout << "Thread Creation Error" << endl;
			//do something with error
		}
		if(i == MAXNUMBEROFCLIENTS){
			cout << "Max Number of Clients Reached" << endl;
		}

	}
}

void *client(void *arguments){
	return NULL;

	//allow sending of message and revieving of messages here
	//allow link to broadcast/ private message for username

}
//allows mult client connects
//recvs and broadcast
	// socket
	//bind
	//listen
	//accept
	//send()
	//recv()