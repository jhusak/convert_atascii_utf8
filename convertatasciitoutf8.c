#include <stdio.h>
#include <stdlib.h>

char * converpl_tab[]={
	"a","ą",
	"c","ć",
	"e","ę",
	"l","ł",
	"n","ń",
	"o","ó",
	"s","ś",
	"k","ź",
	"z","ż",
	"d","Ś",
	"X","Ż",
	NULL,""
	};
void usage(char * n) {
	printf("Usage: %s [-h] [-7] [-p] [<infileatascii> <outfileutf8>]\n",n);
	exit(64);
}

int main(int argc, char ** argv) {
	FILE *inputFile=NULL, *outputFile=NULL;
	char *inputfilename=NULL, *outputfilename=NULL;
	int character;
	int sevenbitout=0;
	int convertpl=0;

	for (int i=1; i<argc; i++){
		if (argv[i][0]=='-' && argv[i][1]=='h' && argv[i][2]==0) {
			usage(argv[0]);
		}

		if (argv[i][0]=='-' && argv[i][1]=='7' && argv[i][2]==0) {
			sevenbitout=1;
			continue;
		}

		if (argv[i][0]=='-' && argv[i][1]=='8' && argv[i][2]==0) {
			sevenbitout=0;
			continue;
		}

		if (argv[i][0]=='-' && argv[i][1]=='p' && argv[i][2]==0) {
			convertpl=1;
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

	if (inputfilename) {
		inputFile = fopen(inputfilename, "r");
		if (inputFile == NULL) {
			printf("Error opening %s\n",inputfilename);
			return 1;
		}
	}
	else
		inputFile=stdin;


	if (outputfilename) {
		outputFile = fopen(outputfilename, "w");
		if (outputFile == NULL) {
			printf("Error opening %s\n",outputfilename);
			fclose(inputFile);
			return 1;
		}
	}
	else
		outputFile=stdout;

	while ((character = fgetc(inputFile)) != EOF) {
		if (character==155) {
			fputc(0x0a, outputFile);
		}
		else if (character<128 || sevenbitout){
			if (convertpl) {
				int i=0;
				while (converpl_tab[i]!=NULL)
				{
					if (converpl_tab[i][0]>=96) {
						if (converpl_tab[i][0]-96==(character&0x7f)) {
							fprintf(outputFile,"%s",converpl_tab[i+1]);
							break;
						}
					} else
					if (converpl_tab[i][0]>=64) {
						if (converpl_tab[i][0]-64==(character&0x7f)) {
							fprintf(outputFile,"%s",converpl_tab[i+1]);
							break;
						}
					}
					i+=2;
				}
				if (!converpl_tab[i])
					fputc(character&0x7f, outputFile);
			}
			else
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
