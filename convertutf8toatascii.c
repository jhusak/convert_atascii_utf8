#include <stdio.h>
int main(int argc, char ** argv) {
	FILE *inputFile, *outputFile;
	int character;
	int err=0;

	if (argc!=3) {
		printf("Usage: %s fileATASCII fileUTF8\n",argv[0]);
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
		if (character==0xa) {
			fputc(155, outputFile);
		}
		else if (character<128){
			fputc((character), outputFile);
		}
		else {
			int chrarr[8];
			chrarr[0]=character<<1;

			int cnt=0;
			while (chrarr[0]&0x80) {
				if ((chrarr[++cnt]= fgetc(inputFile)) == EOF) {
					printf("Unexpected eof. exiting.\n");
					err=1;
					break;
				}
				chrarr[0]<<=1;
			}
			if (err) break;

			character&=(1<<(6-cnt))-1;
			int c2;
			for (c2=1; c2<=cnt; c2++) {
				character<<=6;
				character|=chrarr[c2]&0x3f;
			}
			if ((character&0xfc80)==0xe080)
			{
				fputc(character&0xff, outputFile);
			}
		}
	}

	fclose(inputFile);
	fclose(outputFile);
	return err;
}
