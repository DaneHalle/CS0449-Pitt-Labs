//Dane Halle (dmh148)
#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <unistd.h>
#include <pthread.h>

#define streq(a, b) (strcmp((a), (b)) == 0)

void exit_main_thread();
void show_status();
void set_alarm(long duration);

void get_line(char* input, int size) {
	fgets(input, size, stdin);
	int len = strlen(input);
	if(len > 0)
		input[len - 1] = '\0';
}

int main(int argc, char** argv) {
	while(true) {
		printf("> ");
		char buf[100];
		get_line(buf, sizeof(buf));

		char* saveptr;
		char* command = strtok_r(buf, " ", &saveptr);

		if(command == NULL) {
			continue;
		} else if(streq(command, "exit")) {
			exit_main_thread();
		} else if(streq(command, "status")) {
			show_status();
		} else if(streq(command, "alarm")) {
			char* duration = strtok_r(NULL, " ", &saveptr);

			if(duration == NULL) {
				printf("please give a duration in seconds.\n");
			} else {
				set_alarm(atoi(duration));
			}
		}
	}
	return 0;
}

int num_threads = 0;
pthread_mutex_t num_threads_mutex = PTHREAD_MUTEX_INITIALIZER;

void change_thread_counter(int delta) {
	if(delta>0){
		pthread_mutex_lock(&num_threads_mutex);
		num_threads++;
		pthread_mutex_unlock(&num_threads_mutex);
		// for(int i=0; i<delta; i++) {
		// 	pthread_mutex_lock(&num_threads_mutex);
		// 	num_threads++;
		// 	pthread_mutex_unlock(&num_threads_mutex);
		// }
	}else if(delta<0){
		pthread_mutex_lock(&num_threads_mutex);
		num_threads--;
		pthread_mutex_unlock(&num_threads_mutex);
		// delta*=-1;
		// for(int i=0; i<delta; i++) {
		// 	pthread_mutex_lock(&num_threads_mutex);
		// 	num_threads--;
		// 	pthread_mutex_unlock(&num_threads_mutex);
		// }
	}
}

void exit_main_thread() {
	if(num_threads!=0){
		printf("\tstill %d alarm(s) pending...\n", num_threads);
	}
	pthread_exit(&num_threads);
}

void show_status() {
	printf("\t%d alarm(s) pending.\n", num_threads);
}

void* thread_main(void* duration)
{
	long time=(long)duration;
	sleep(time);
	printf(" [RING RING!]\a ");
	fflush(stdout);
	change_thread_counter(-1);
	return NULL;
}

void set_alarm(long duration) {
	if(duration<=0){
		printf("\tduration must be greater than 0\n");
	}else{
		change_thread_counter(1);
		pthread_t t1;
		pthread_create(&t1, NULL, &thread_main, (void*)duration);
	}
}

