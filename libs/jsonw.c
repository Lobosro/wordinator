#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readjson(char *filename, int line){
	// READ FILE
	FILE *pF = fopen(filename, "r"); // SETS THE FOPEN
	char buffer[255]; // MAKES A BUFFER
	for(int i = 1; i <= line; i++){ // USES THIS TO FIND THE CORRECT LINE
		fgets(buffer, 255, pF);
	}
	// DATA SIMPLYFING
	// BLOCK 1 REMOVES EVERYTHING AFTER INCLUDING }
	int g;
	for(g = 0; buffer[g] != '}'; g++);
	char semi[g];
	for(int f=0; buffer[f] != '}'; f++){
		semi[f] = buffer[f];
	}
	// BLOCK 2 REMOVES EVERYTHING BEFORE INCLUDING { 
	int h;
	for(h = 0;semi[h] != '{'; h++);
	char full[g-h];
	for(int w = g;semi[w] != '{'; w--){
		full[w-h-1] = semi[w];
	}
	// BLOCK 3 MAKE FULL RETURNABLE BY COPYING INTO FINAL
	size_t len = strlen(full);
	char *final = malloc(len+1);
	strcpy(final, full);

	return final;
}

char* cleardata(const char *data){
	size_t len = strlen(data);
	char *full = malloc(len);
	strcpy(full, data + 1);
	full[strlen(full) - 1] = '\0';
	return full;
}

