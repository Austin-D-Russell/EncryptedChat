//Includes
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <limits>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ncurses.h>
#include <form.h>
#include <errno.h>

// static FIELD *fields[2];

using namespace std;

//Object Declarations
typedef struct{
	int portno;
	string IP;
	int sockfd;
}UserInput;

typedef struct{
	WINDOW *inputwindow;
	WINDOW *outputwindow;
}Windows;

//Functions
int menu(UserInput *user);
int connect(UserInput *user);
void eventLoop(Windows *win);
int initScreens();

int main(int argc, char *argv[]){

	UserInput user;
	UserInput *userpt = &user;

	// menu(userpt);
	// connect(userpt);
	initScreens();

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


int initScreens(){
	cout << "About to Init Screens" << endl;
	WINDOW *input;
	WINDOW *inputBox;
	WINDOW *output;
	WINDOW *outputBox;

	stdscr = initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	start_color();

	//the one will change when username is inputed
	// move(LINES-4, 1);

	outputBox = subwin(stdscr, LINES-5,COLS,0,0);
	box(outputBox,'*','*');
	output = subwin(outputBox, LINES-7, COLS-2, 1, 1);
	scrollok(output, TRUE);

	inputBox = subwin(stdscr, 5, COLS, LINES-5, 0);
	box(inputBox,'*','*');
	input = subwin(inputBox, 3, COLS-2, LINES-4, 1);


	Windows win;
	Windows *winpt = &win;
	winpt->inputwindow = input;
	winpt->outputwindow = output;

	cout << winpt->inputwindow << endl;


	refresh();
	wrefresh(inputBox);
	wrefresh(input);
	wrefresh(output);
	wrefresh(outputBox);


	//startevent loop
	eventLoop(winpt);

	//Clean up
	delwin(outputBox);
	delwin(inputBox);
	delwin(output);
	delwin(input);
	endwin();

	return 0;

}

void eventLoop(Windows *win){
	int ch;
	while((ch = getch()) != KEY_F(1)){
		wprintw(win->inputwindow, (char *)&ch);
		wrefresh(win->inputwindow);
	 	// Might want to read into Char Buffer as key is pressed.
	 	// Call send when enter is pressed
	}
}

//Functions
	//Send
	//Recv
	//Encrypt
	//Decrypt

//TODO:

//unique username and password stored in server local.txt
//Window Resize
//Move Cursor for Input
//Change getchar to work appropriatly


//Commands::
// :help
// :quit
// :who
// :file (prompts user to grab file)