//Includes
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <limits>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ncurses.h>
#include <form.h>

// static FIELD *fields[2];

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
void input_driver(int ch);

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

	// cout << "connecting to socket..." << endl;
	// if(connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
	// 	cout << "Error connecting" << endl;
	// 	cout << "Please Try again, if error persists restart program" << endl;
	// 	menu(user);
	//

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

void input_driver(int ch){
	// if(ch != ERR){
	// 	srtcat
	// }
}

int startprogram(){
	cout << "About to Init Screens" << endl;
	int ch;
	WINDOW *input;
	WINDOW *inputBox;
	WINDOW *output;

	initscr();
	cbreak();
	start_color();
	keypad(stdscr, TRUE);
	echo();

	//the one will change when username is inputed
	// move(LINES-4, 1);

	output = create_new_win(LINES-5,COLS,0,0);
	inputBox = create_new_win(5, COLS, LINES-5, 0);
	input = subwin(inputBox, 3, COLS-2, LINES-4, 1);

	wmove(input, 0, 0);

	// immedok(input, TRUE); // Didnt Work yet
	// scrollok(input,TRUE); //This should add Scrolling as need be
	// wsetscrreg(top,1,maxy/2-2); //Not sure what this does yet. To the Man Pages!
 

	// box(output, 0, 0);
	// box(input, 0, 0);
	// fields[0] = new_field(LINES-5,COLS,0,0,0,0);
	// fields[1] = new_field(5,COLS,LINES-5,0,0,0);

	// can use this field to set a welcome message when logging on
	// set_field_buffer(fields[0], 0, val1)
	

	// set_field_opts(fields[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
	// set_field_opts(fields[1], O_VISIBLE | O_ACTIVE | O_PUBLIC | O_EDIT | O_WRAP);

	//might wanna window/ text refresh here

	refresh();
	wrefresh(inputBox);
	wrefresh(input);
	wrefresh(output);

	//get char is registering input.
	while((ch = getch()) != KEY_F(1)){
		input_driver(ch);
		// Might want to read into Char Buffer as key is pressed.
		// Call send when enter is pressed
		continue; 
	}

	// free_field(fields[0]);
	// free_field(fields[1]);
	delwin(output);
	delwin(input);
	endwin();

	return 0;

}

WINDOW *create_new_win(int height, int width, int starty, int startx){
	WINDOW *temp_win = newwin(height, width, starty, startx);
	box(temp_win,'*','*');
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