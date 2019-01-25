//Dane Halle (dmh148)
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void get_line(char* buffer, int size) {
	fgets(buffer, size, stdin);
	int len = strlen(buffer);
	// this is a little more robust than what we saw in class.
	if(len != 0 && buffer[len - 1] == '\n')
		buffer[len - 1] = '\0';
}

// returns 1 if the two strings are equal, and 0 otherwise.
int streq(const char* a, const char* b) {
	return strcmp(a, b) == 0;
}

// returns 1 if the two strings are equal ignoring case, and 0 otherwise.
// so "earth" and "Earth" and "EARTH" will all be equal.
int streq_nocase(const char* a, const char* b) {
	// hohoho aren't I clever
	for(; *a && *b; a++, b++) if(tolower(*a) != tolower(*b)) return 0;
	return *a == 0 && *b == 0;
}

float weight_on_planet(const char* planet_name, int user_weight) {
	if(streq_nocase(planet_name, "mercury")){
		return user_weight*.38;
	}else if(streq_nocase(planet_name, "venus")){
		return user_weight*.91;
	}else if(streq_nocase(planet_name, "mars")){
		return user_weight*.38;
	}else if(streq_nocase(planet_name, "jupiter")){
		return user_weight*2.54;
	}else if(streq_nocase(planet_name, "saturn")){
		return user_weight*1.08;
	}else if(streq_nocase(planet_name, "uranus")){
		return user_weight*.91;
	}else if(streq_nocase(planet_name, "neptune")){
		return user_weight*1.19;
	}else if(streq_nocase(planet_name, "earth")){
		return -2;
	}else{
		return -1;
	}
}

int main() {
	printf("How much do you weigh? ");
	char input[100];
	get_line(input, sizeof(input));
	int weight; 
	sscanf(input, "%d", &weight);	
	
	while(1){
		printf("What planet do you wanna go to ('exit' to exit)? ");
		char in[100];
		get_line(in, sizeof(in));
		if(streq_nocase(in, "exit")){
			break;	
		}
		float new_weight=weight_on_planet(in,weight);
		if(new_weight==-1){
			printf("That's not a planet.\n");
		}else if(new_weight==-2){
			printf("You already are there.\n");
		}else{
			printf("You'd weigh %f there.\n", new_weight);
		}
	}	

	return 0;
}
