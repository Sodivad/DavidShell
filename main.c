#include <stdio.h>
#include <string.h>
#include "font.c"
#include <stdint.h>
#include <stdlib.h>
 
char getByte(uint64_t number, int byte){
	return number >> (56 - (8 * byte));
}

char* getPixels(char* in){
	char *data = malloc(8 * sizeof(char));
	int i;
	for (i = 0; i < 8; i++){//zeilen
		int j;
		for (j = 0; j < strlen(in); j++){ //zeichen
			char towrite = getByte(font[in[j]], i);
			int index = i *strlen(in) + j;
			data[index] = towrite;
		}
	}
	return data;
}
void write(char* in){
	FILE* file;
	fopen_s(&file, "test.pbm", "wb");
	fprintf(file, "P4 %i 8\n",strlen(in)*8); //HEADER
	char* data = getPixels(in);
	size_t size = strlen(in) * 8;
	int h =  fwrite(data, sizeof(char), size , file);
	fclose(file);
}
int main(char** argv, int argc){
	write("Hallo");
}

