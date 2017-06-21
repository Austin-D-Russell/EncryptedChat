//Includes
#include <stdio.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <limits>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ncurses.h>

using namespace std;

//Object Declarations
typedef struct{
	int portno;
	string IP;
	int sockfd;
}UserInput;

//Functions
int menu(UserInput *user);
int connect(UserInput *user);
int handleUserInput(UserInput *user);
int startprogram();
WINDOW *create_new_win(int height, int width, int starty, int startx);
void remove_win(WINDOW *temp_win);

int main(int argc, char *argv[]){

	UserInput user;
	UserInput *userpt = &user;

	menu(userpt);
	connect(userpt);
	startprogram();
	handleUserInput(userpt);

	return 0;
}

int menu(UserInput *user){
	int portno;
	string IP;

	cout << "Please Enter a Port Number: " << endl;
	cin >> portno;
	while(cin.fail()){
		cout << "Enter an Integer for the port number. \n" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please Enter a Port Number: " << endl;
		cin >> portno;
	}

	cout << "Please Enter IP address: " << endl;
	cin >> IP;

	user->portno = portno;
	user->IP = IP;
	return 0;
}

int connect(UserInput *user){
	int sockfd;
	struct sockaddr_in serv_addr;


	cout << "Creating Socket...." << endl;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		cout << "Unable to Create Socket" << endl;
		cout << "Please Try again, if error persists restart program" << endl;
		menu(user);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(user->portno);
	const char* IP = user->IP.c_str();
	inet_aton(IP, &serv_addr.sin_addr);

	cout << "connecting to socket..." << endl;
	if(connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
		cout << "Error connecting" << endl;
		cout << "Please Try again, if error persists restart program" << endl;
		menu(user);
	}

	user->sockfd = sockfd;

	return 0;
	// send connnect with User/ password
	// once connected allow message to be entered and broadcasted private
	// message to come after
	// constantly check for incoming messages
}
int handleUserInput(UserInput *user){
	//check if sending or recving
	//if recving display message
	//lock bottom input line
	//if sending, send to server
	return 0;
}

int startprogram(){
	WINDOW *input;
	WINDOW *output;

	cout << "About to Init Screens" << endl;

	initscr();
	start_color();

	input = create_new_win(1, COLS, 0, 0);
	output = create_new_win(LINES - 1, COLS, 0, 1);

	return 0;

}

WINDOW *create_new_win(int height, int width, int starty, int startx){
	WINDOW *temp_win;

	temp_win = newwin(height, width, starty, startx);
	//Update here to make boarders to box ect. look nice
	box(temp_win, 0, 0);

	wrefresh(temp_win);

	return temp_win;
}

//May not need this for scrolling
//check out move command
void remove_win(WINDOW *temp_win){
	wborder(temp_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(temp_win);
	delwin(temp_win);
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