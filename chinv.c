#include <stdio.h>
int main(int argc, char ** argv) {
	FILE *inputFile, *outputFile;
	int character;
	int err=0;

	if (argc!=1) {
		printf("Usage: %s\n\n"
		"This command changes inverse of ATASCII characters,\n"
		"when inversed characters are stored as unicode codes\n\n"
		"You may use it in vim as a block text filter, for example:\n"
		"first select text to be changed and then press\n"
		"shift-: and append !chinv, then press enter.\n\n"
		"Under the hood it changes all characters from stdin, and\n"
		"when <128 (but 0xa) it outputs them to stdout as unicode inversed,\n"
		"and when in unicode inversed form - outputs  back to plain\n"
		"ATASCII uninversed.\n"
		"Special font EightBit Atari-Standard.ttf must be used to\n"
		"properly display inversed ATASCII characters.\n\n"
		"please use it as you wish :)\n\n"
		"wishes author, Jakub Husak (11.2023)\n\n"
		,argv[0]);
		return(64);
	}

	inputFile = stdin;
	outputFile = stdout;

	while ((character = fgetc(inputFile)) != EOF) {
		if (character==0xa) {
			fputc(0xa, outputFile);
		}
		else if (character<128){
			character|=0x80;
			fputc(0xee, outputFile);
			fputc(0x80|(character>>6), outputFile);
			fputc(0x80|(character&0x3f), outputFile);
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
				fputc(character&0x7f, outputFile);
			}
		}
	}
	return err;
}
