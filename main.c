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

void getEstFile(int mode, char* filename) {
	DIR* currDir = opendir(".");
	struct dirent *aDir;
	off_t size = --mode ? OFF_MAX : 0;
	struct stat dirStat;
	
	while ((aDir = readdir(currDir)) != NULL) {
		if (strncmp(aDir->d_name,"movies_", 7) == 0 && strcmp(aDir->d_name + aDir->d_namlen - 4, ".csv") == 0) {
			stat(aDir->d_name, &dirStat);
			
			if ((!mode && dirStat.st_size > size) || (mode && dirStat.st_size < size)) {
				size = dirStat.st_size;
				memset(filename, '\0', 256 * sizeof(char));
				strcpy(filename, aDir->d_name);
			}
		}
	}
	closedir(currDir);
}

// 1 = max
// 2 = min
// 3 = custom
void getName(int mode) {
	char filename[256];
	if (mode == 3) {
		printf("Enter the complete file name: ");
		scanf("%s", filename);
		
		if (access(filename, F_OK) == -1) {
			printf("The file %s was not found. Try again\n", filename);
			return;
		}
	} else
		getEstFile(mode, filename);
	processFile(filename);
}

void fileToProcess(void) {
	int input;
	char fileNotFound = 1;
	while (fileNotFound) {
		printf("\nWhich file you want to process?\nEnter 1 to pick the largest file\nEnter 2 to pick the smallest file\nEnter 3 to specify the name of a file\n\nEnter a choice from 1 to 3: ");
		scanf("%d", &input);
		input > 0 && input < 4 ? getName(input) : printf("You entered an incorrect choice. Try again.");
	}
}

int main(int argc, const char * argv[]) {
	int input = 0;
	while (input != 2) {
		printf("1. Select file to process\n2. Exit the program\n\nEnter a choice 1 or 2: ");
		scanf("%d", &input);
		switch(input) {
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
