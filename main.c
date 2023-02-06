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
#include <stdlib.h>
#include <time.h>

void processFile(char *filename) {
	char newPath[100];
	srandom((unsigned int) time(NULL));
	sprintf(newPath, "./streedan.movies.%d", (int) random() % 100000);
	if (mkdir(newPath, 0750))
 		perror("mkdir");
	
//	char *currLine = NULL;
//	size_t len = 0;
	FILE *movieFile = fopen(filename, "r");
	printf("Now processing the chosen file named %s\n", filename);
	
//	getline(&currLine, &len, movieFile);
//	while (getline(&currLine, &len, movieFile) != -1) {
	char line[100];
	while (fgets(line, 100, movieFile)) {
//		char *saveptr;
		
//		char *title = strtok_r(currLine, ",", &saveptr);
//		int year = atoi(strtok_r(NULL, ",", &saveptr));
		char *title = strtok(line, ",");
		int year = atoi(strtok(NULL, ","));
		
		char tempPath[100];
		sprintf(tempPath, "%s/%i.txt", newPath, year);
		
//		int fd = open(tempPath, 521, 0640);
//		write(fd, title, strlen(title));
		FILE *file = fopen(tempPath, "a");
		fprintf(file, "%s\n", title);
		fclose(file);
		chmod(tempPath, 0640);
	}
	fclose(movieFile);
	printf("Created directory with name %s\n\n", newPath);
}

void getEstFile(int mode, char* filename) {
	DIR* currDir = opendir(".");
	struct dirent *aDir;
	off_t size = --mode ? OFF_MAX : 0;
	struct stat dirStat;
	
	while ((aDir = readdir(currDir)) != NULL) {
		if (!strncmp(aDir->d_name,"movies_", 7) && !strcmp(aDir->d_name + aDir->d_namlen - 4, ".csv")) {
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

// mode = 1 -> maxSize
// mode = 2 -> minSize
// mode = 3 -> customName
void getFilename(int mode) {
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
		input > 0 && input < 4 ? getFilename(input) : printf("You entered an incorrect choice. Try again.");
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
