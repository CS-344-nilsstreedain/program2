//
//  main.c
//  program2
//
//  Created by Nils Streedain on 2/4/23.
//

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>

void processFile(char *filename) {
	printf("Now processing the chosen file named %s\n", filename);
	printf("Created directory with name %s\n\n", "unknown");
}

void getEst(int getMin) {
	char filename[256];
	DIR* currDir = opendir(".");
	struct dirent *aDir;
	off_t size = !getMin ? 0 : OFF_MAX;
	struct stat dirStat;
	
	while ((aDir = readdir(currDir)) != NULL) {
		if (strncmp(aDir->d_name,"movies_", 7) == 0 && strcmp(aDir->d_name + aDir->d_namlen - 4, ".csv") == 0) {
			stat(aDir->d_name, &dirStat);

			if ((!getMin && dirStat.st_size > size) || (getMin && dirStat.st_size < size)) {
				size = dirStat.st_size;
				memset(filename, '\0', sizeof(filename));
				strcpy(filename, aDir->d_name);
			}
		}
	}
	closedir(currDir);
	processFile(filename);
}

int getName(void) {
	char filename[256];
	printf("Enter the complete file name: ");
	scanf("%s", filename);
	
	if (access(filename, F_OK) == -1) {
		printf("The file %s was not found. Try again\n", filename);
		return 1;
	}
	processFile(filename);
	return 0;
}

void fileToProcess(void) {
	int userInput;
	char fileNotFound = 1;
	while (fileNotFound) {
		printf("\nWhich file you want to process?\nEnter 1 to pick the largest file\nEnter 2 to pick the smallest file\nEnter 3 to specify the name of a file\n\nEnter a choice from 1 to 3: ");
		scanf("%d", &userInput);
		if (userInput == 1 || userInput == 2) {
			getEst(userInput - 1);
		} else if (userInput == 3) {
			fileNotFound = getName();
		} else {
			printf("You entered an incorrect choice. Try again.");
		}
	}
}

int main(int argc, const char * argv[]) {
	int userInput = 0;
	while (userInput != 2) {
		printf("1. Select file to process\n2. Exit the program\n\nEnter a choice 1 or 2: ");
		scanf("%d", &userInput);
		switch(userInput) {
			case 1:
				fileToProcess();
			case 2:
				break;
			default:
				printf("You entered an incorrect choice. Try again.\n");
		}
	}
	return 0;
}
