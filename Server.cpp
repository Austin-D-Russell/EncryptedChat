using namespace std;

int menu();
int connect(int portno);

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

	cout << "Creating Socket......" << endl;
	if(sockfd = socket(AF_INET, SOCK_STREAM, 0) < 0){
		cout << "Error creating Socket" << endl;
		//exit or return to menu?
	}

	//setsockopt
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&option, sizeof(int)) < 0){
		cout << "unable to set socket options to reuse address" << endl;
		//exit or return to menu
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);



	cout << "Binding Socket......." << endl;
	if(bind(sockfd, (struct sockaddr*)&remote, sizeof(serv_addr)) < 0){
		cout << "Error Binding Socket" << endl;
		//exit or return to menu
	}

	cout << "Listening on Socket....." << endl;
	if(listen(sockfd, 1024) < 0){
		cout << "Unable to Listen on Socket" << endl;
		//exit or return to menu
	}

	int connfd;
	for(;;){
		if((connfd = accept(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))){
			
		}
	}


}
//allows mult client connects
//recvs and broadcast
	// socket
	//bind
	//listen
	//accept
	//send()
	//recv()