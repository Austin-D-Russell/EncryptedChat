//Includes
#include <stdio.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <limits>
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
	struct sockaddrr_in address, serv_addr;


	//create socket
	if ((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0){
		cout << "Unable to Create Socket" << endl;
		exit(1);
	}
	//Connect to Socket

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
//Can you connect over an IP address?
//hostname for Server?