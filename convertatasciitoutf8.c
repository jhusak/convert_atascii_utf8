#include <stdio.h>
int main(int argc, char ** argv) {
	FILE *inputFile, *outputFile;
	int character;

	if (argc!=3) {
		printf("Usage: %s fileatascii fileutf-8\n",argv[0]);
		return(64);
	}

	inputFile = fopen(argv[1], "r");
	if (inputFile == NULL) {
		printf("Error opening %s\n",argv[1]);
		return 1;
	}

	outputFile = fopen(argv[2], "w");
	if (outputFile == NULL) {
		printf("Error opening %s\n",argv[2]);
		fclose(inputFile);
		return 1;
	}

	while ((character = fgetc(inputFile)) != EOF) {
		if (character==155) {
			fputc(0x0a, outputFile);
		}
		else if (character<128){
			fputc((character), outputFile);
		}
		else {
			fputc(0xee, outputFile);
			fputc(0x80|(character>>6), outputFile);
			fputc(0x80|(character&0x3f), outputFile);
		}


	}

	fclose(inputFile);
	fclose(outputFile);
	return 0;
}
