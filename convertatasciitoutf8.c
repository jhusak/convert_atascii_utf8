#include <stdio.h>
int main(int argc, char ** argv) {
	FILE *inputFile=NULL, *outputFile=NULL;
	char *inputfilename=NULL, *outputfilename=NULL;
	int character;
	int sevenbitout=0;
	int  processed=0;

	if ((argc!=3)&&(argc!=4)) {
		printf("Usage: %s [-7] infileatascii outfileutf8\n",argv[0]);
		return(64);
	}

	for (int i=1; i<argc; i++){
		if (argv[i][0]=='-' && argv[i][1]=='7' && argv[i][2]==0) {
			sevenbitout=1;
			processed=1;
			continue;
		}

		if (argv[i][0]=='-' && argv[i][1]=='8' && argv[i][2]==0) {
			sevenbitout=0;
			processed=1;
			continue;
		}

		if (inputfilename==NULL) {
			inputfilename=argv[i];
			continue;
		}

		if (outputfilename==NULL) {
			outputfilename=argv[i];
			continue;
		}

	}
	if ((!processed && argc==4) || (processed && argc==3)) {
		printf("Usage: %s [-7] infileatascii outfileutf8\n",argv[0]);
		return(64);
	}


	if (inputfilename && outputfilename) {
		inputFile = fopen(inputfilename, "r");
		if (inputFile == NULL) {
			printf("Error opening %s\n",inputfilename);
			return 1;
		}

		outputFile = fopen(outputfilename, "w");
		if (outputFile == NULL) {
			printf("Error opening %s\n",outputfilename);
			fclose(inputFile);
			return 1;
		}
	}

	while ((character = fgetc(inputFile)) != EOF) {
		if (character==155) {
			fputc(0x0a, outputFile);
		}
		else if (character<128 || sevenbitout){
			fputc(character&0x7f, outputFile);
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
