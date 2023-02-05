//
//  main.c
//  program2
//
//  Created by Nils Streedain on 2/4/23.
//

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdbool.h>

void processFile(char *filename) {
	printf("\nNow processing the chosen file named %s", filename);
}

void getEst(bool largest) {
	DIR* currDir = opendir(".");
	struct dirent *aDir;
	off_t size = 0;
	struct stat dirStat;
	char entryName[256];
	
	if (!largest)
		size = OFF_MAX;
	
	while ((aDir = readdir(currDir)) != NULL) {
		if (strncmp(aDir->d_name,"movies_", 7) == 0 && strcmp(aDir->d_name + aDir->d_namlen - 4, ".csv") == 0) {
			stat(aDir->d_name, &dirStat);

			if ((largest && dirStat.st_size > size) || (!largest && dirStat.st_size < size)) {
				size = dirStat.st_size;
				memset(entryName, '\0', sizeof(entryName));
				strcpy(entryName, aDir->d_name);
			}
		}
	}
	closedir(currDir);
	printf("Largest file is %s", entryName);
}

void getName(void) {
	printf("Enter the complete file name: ");
	
	int file_descriptor;
	char filename[256];
	scanf("%s", filename);
	
	file_descriptor = open(filename, O_RDONLY);
	if (file_descriptor == -1) {
		printf("The file %s was not found. Try again\n", filename);
		return;
	}
	
	processFile(filename);
}

void fileToProcess(void) {
	while (1) {
		printf("\nWhich file you want to process?\nEnter 1 to pick the largest file\nEnter 2 to pick the smallest file\nEnter 3 to specify the name of a file\n\nEnter a choice from 1 to 3: ");
		
		int userInput;
		scanf("%d", &userInput);
		switch(userInput) {
			case 1:
				getEst(1);
				break;
			case 2:
				getEst(0);
				break;
			case 3:
				getName();
				break;
			default:
				printf("You entered an incorrect choice. Try again.");
		}
	}
}

int main(int argc, const char * argv[]) {
	while (1) {
		printf("1. Select file to process\n2. Exit the program\n\nEnter a choice 1 or 2: ");
		
		int userInput;
		scanf("%d", &userInput);
//		if (userInput == 1) {
//			fileToProcess();
//		} else if (userInput == 2) {
//			return EXIT_SUCCESS;
//		} else {
//			printf("You entered an incorrect choice. Try again.\n");
//		}
		
		switch(userInput) {
			case 1:
				fileToProcess();
				break;
			case 2:
				return EXIT_SUCCESS;
			default:
				printf("You entered an incorrect choice. Try again.\n");
		}
	}
	
	return 0;
}
