#include <stdlib.h>
#include <string.h>

char* cleardata(const char *data){
	size_t len = strlen(data);
	char *full = malloc(len);
	strcpy(full, data + 2);
	full[strlen(full) - 2] = '\0';
	return full;
}

