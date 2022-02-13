#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;


int main(){
	pid_t pid;
	int main_pid;
	main_pid = getpid();
	cout << "Main Process ID: "<< main_pid <<endl;
	pid = fork(); //fork 1
	if(pid == 0){
		cout << "Fork 1. I'm the child "<< getpid() << ", my parent is "<< getppid() <<"."<<endl;
		pid = fork(); //fork 4
		if(pid == 0){
			cout << "Fork 4. I'm the child "<< getpid() << ", my parent is "<< getppid() <<"."<<endl;
			pid = fork(); //fork 5
			if(pid == 0){
				cout << "Fork 5. I'm the child "<< getpid() << ", my parent is "<< getppid() <<"."<<endl;
			}
			else if(pid > 0){
				wait(NULL);
			}
		}
		else if(pid > 0){
				wait(NULL);
			}
	}
	else if(pid > 0){
		wait(NULL);
		pid = fork(); //fork 2
		if(pid == 0){
			cout << "Fork 2. I'm the child "<< getpid() << ", my parent is "<< getppid() <<"."<<endl;
		}
		else if(pid > 0){
				wait(NULL);
			}
		pid = fork(); //fork 3
		wait(NULL);
		if(pid == 0){
			cout << "Fork 3. I'm the child "<< getpid() << ", my parent is "<< getppid() <<"."<<endl;
		}
	}




	return 0;
}