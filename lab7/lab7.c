//Dane Halle (dmh148)
#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		printf("uh, you gotta gimme an executable to run...\n");
		return 0;
	}

	if(fork() == 0)
	{
		// This will execute the program whose name is in the first
		// command-line argument, and whose arguments are after it.
		execvp(argv[1], &argv[1]);
		perror(argv[1]);
		exit(1);
	}
	else
	{
		signal(SIGINT, SIG_IGN);

		// This waits for a child to exit in some way. *How* it exited
		// will be put in the status variable.
		int status;
		int childpid = waitpid(-1, &status, 0);
		printf("----------\n");


		if(childpid==-1){
			perror(argv[1]);
			exit(WEXITSTATUS(status));
		}else if(status==0){
			printf("Program exited successfully\n");
			exit(WEXITSTATUS(status));
		}else if(WIFEXITED(status)){
			printf("Program exited with code %d\n", WEXITSTATUS(status));
			exit(WEXITSTATUS(status));
		}else if(WIFSIGNALED(status)){
			printf("Program terminated due to signal: %s\n", strsignal(WTERMSIG(status)));
			exit(WEXITSTATUS(status));
		}else{
			printf("Program terminated some other way\n");
			exit(WEXITSTATUS(status));
		}
	}

	return 0;
}