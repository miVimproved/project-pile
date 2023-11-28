#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

typedef int bool;
#define true 1
#define false 0

// Sleep function I made bc iirc sleep() in linux uses seconds
static void sleep(float seconds) {
	// Don't sleep if we don't need to
	if (!seconds) {
		return;
	}

	// Setup sleep time
	struct timespec time;
	time.tv_sec = seconds;
	time.tv_nsec = (seconds - time.tv_sec) * 1000000000;

#ifdef _DEBUG
	printf("Seconds: %i, Nanoseconds: %i\n", time.tv_sec, time.tv_nsec);
	fflush(stdout);
#endif

	// Sleep
	nanosleep(&time, &time);
}

void onExit(void) {
	printf("\033[0;37m\n");
}

void handleSignal(int signal) {
	exit(signal);
}

int main(int argc, char** argv) {
	// Check arg count
	if (argc != 6) {
		perror("Invalid Arguments.");
		exit(1);
	}

	// Setup exit and signal handler
	atexit(onExit);
	signal(2, handleSignal);

	// Read the arguments
	float sleep_time = atof(argv[1]);
	char* letters = argv[2];
	bool newline = atoi(argv[3]);
	int prego = atoi(argv[4]);
	
	printf("\033[0;3%sm", argv[5]);

	printf("Sleep Time: %f\nSentence: %s\nInput Newline: %i\nPreprocess: %i\n", sleep_time, letters, newline, prego);
	fflush(stdout);

#ifdef _DEBUG
	sleep(5);
#endif

	// Print the preprocessed runs
	for (int i = 0; i < prego; i++) {
		printf("%s", letters);
		if (newline) {
			printf("\n");
		}
	}

	// Loop
	while (true) {
		for (int i = 0; letters[i]; i++) {
			printf("%c", letters[i]);
			fflush(stdout);
			sleep(sleep_time);
		}
		if (newline) {
			printf("\n");
			fflush(stdout);
			sleep(sleep_time);
		}
	}
}
