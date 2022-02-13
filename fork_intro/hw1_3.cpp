#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <sys/wait.h>
using namespace std;

#define MAX_LINE 80

vector<char *> split(const string& input_string, const string& seperate_string){
	vector<char *> Output_vector;
	if(input_string == "") return Output_vector;

	char * c_input_string = new char[input_string.length() + 1];
	strcpy(c_input_string, input_string.c_str());

	char * c_seperate_string = new char[seperate_string.length() + 1];
	strcpy(c_seperate_string, seperate_string.c_str());

	char *c_splited = strtok(c_input_string, c_seperate_string);
	while(c_splited){
		//string splited_string = c_splited;
		Output_vector.push_back(c_splited);
		c_splited = strtok(NULL, c_seperate_string);
	}
	return Output_vector;
}

int main(void)
{
	char *arg[MAX_LINE/2+1]; /*command line arguments*/
	string input_line;
	vector<char *> Input_vector;
	int should_run = 1; /*flag to determine when to exit program*/
	
	while(should_run){
		printf("osh>");
		fflush(stdout);

		//get user input command......
		getline(cin, input_line);

		//split command string with self defined split() function......
		Input_vector = split(input_line, " ");
		Input_vector.push_back(NULL);
		char **args = &Input_vector[0];
		
		//check if the command is "exit" and break the while loop......
		string args_string(args[0]);
		if (args_string == "exit"){
			break;
		}

		//fork a child......
		pid_t pid = fork();

		if(pid == 0){
			//if command not found or command error occurs......
			if (execvp(args[0], args) == -1){
				cout << "command not found: " << input_line << endl;
				exit(EXIT_FAILURE);
			}
			exit(0);
		}

		//parent program must wait until child program finish......
		else if (pid > 0) wait(NULL);
		else{
			cout << "Fork Error!!! (pid < 0)" << endl;
			break;
		}
		/**
		* your code!
		* After reading user input, the step are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		*/
	}

	return 0;
}


