//Includes
#include <stdio.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <limits>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

//Object Declarations
typedef struct{
	int portno;
	string IP;
}UserInput;

//Functions
int menu(UserInput *user);
int connect(UserInput *user);


int main(int argc, char *argv[]){

	UserInput user;
	UserInput *userpt = &user;

	menu(userpt);
	connect(userpt);

	return 0;
}

int menu(UserInput *user){
	int portno;
	string IP;

	cout << "Please Enter a Port Number, enter 0 if connecting with IP: " << endl;
	cin >> portno;
	while(cin.fail()){
		cout << "Enter an Integer for the port number. \n" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please Enter a Port Number, enter 0 if connecting with IP: " << endl;
		cin >> portno;
	}

	if(portno == 0){
		cout << "Please Enter IP address: " << endl;
		cin >> IP;
	}

	user->portno = portno;
	user->IP = IP;
	return 0;
}

int connect(UserInput *user){
	int sockfd;
	struct sockaddr_in serv_addr;


	//create socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		cout << "Unable to Create Socket" << endl;
		cout << "Please Try again, if error persists restart program" << endl;
		menu(user);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(user->portno);
	const char* IP = user->IP.c_str();
	inet_aton(IP, &serv_addr.sin_addr);

	if(connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
		cout << "Error connecting" << endl;
		cout << "Please Try again, if error persists restart program" << endl;
		menu(user);
	}
	return 0;
	// send connnect with User/ password
	// once connected allow message to be entered and broadcasted private
	// message to come after
	// constantly check for incoming messages
}



//Functions
	//Menu
	//Connect
		//Create Socket
		//Connect to Socket
		//Send and Recieve
	//Send
	//Recv
	//Encrypt
	//Decrypt

//Questions:

//unique username and password stored in server local.txt?