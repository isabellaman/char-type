/*
 * Reads from an input file, counts number of alphabetic, digit,
 * punctuation, and whitespace characters in each line.
 * Prints an array of elements under each respective category in output file. 
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>
#include<string.h>

#define MAX_STRING_LENGTH 100

void extract_chars(char* s, char* a, char* d, char* p, char* w);

int main(int argc, char* argv[]){
	FILE* in;                        
   	FILE* out;                     
   	char* line;             

	char* a; 	//alphabetic
	char* d;        //digit	
	char* p; 	//punctuation
	char* w; 	//whitespace characters

   	if( argc != 3 ){
      		printf("Usage: %s input-file output-file\n", argv[0]);
      		exit(EXIT_FAILURE);
   	}
   	if( (in=fopen(argv[1], "r"))== NULL ){	
      		printf("Unable to read from file %s\n", argv[1]);
      		exit(EXIT_FAILURE);
   	}
	if( (out=fopen(argv[2], "w"))== NULL ){
      		printf("Unable to write to file %s\n", argv[2]);
      		exit(EXIT_FAILURE);
   	}

   	line = calloc(MAX_STRING_LENGTH+1, sizeof(char));

        a = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
        d = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
        p = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
        w = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
	assert(a != NULL && d != NULL && p != NULL && w != NULL);
        assert(line != NULL);

	int curLine = 1;
   	while ( fgets(line, MAX_STRING_LENGTH, in) != NULL ){
		extract_chars(line, a, d, p, w);
		fprintf(out, "line %d contains: \n", curLine);
		fprintf(out, "%lu alphabetic characters: %s\n", strlen(a), a);
                fprintf(out, "%lu numeric characters: %s\n", strlen(d), d);
                fprintf(out, "%lu punctuation characters: %s\n", strlen(p), p);
                fprintf(out, "%lu whitespace characters: %s\n\n", strlen(w), w);
		curLine++;
   	} 
  	free(line);
	free(a);
	free(d);
	free(p);
	free(w);

	line = NULL;
	a = NULL;
	d = NULL;
	p = NULL;
	w = NULL;
	
   	fclose(in);
   	fclose(out);

   	return EXIT_SUCCESS;
}


 //char* s is the input string
void extract_chars(char* s, char* a, char* d, char* p, char* w) {
	int i = 0, dCount = 0;
	int aCount = 0;
	int pCount = 0;
	int wCount = 0;

	while(s[i] != '\0' && i < MAX_STRING_LENGTH) {
		if (isdigit((int)s[i])) {
			d[dCount] = s[i];
			dCount++;
		}
		else if (isalpha(s[i])) {
			a[aCount] = s[i];
                        aCount++;
		}
		else if (ispunct(s[i])) {
			p[pCount] = s[i];
                        pCount++;
		}
		else if (isspace(s[i])) {
			w[wCount] = s[i];
                        wCount++;
		}
		i++;
	}
	d[dCount] = '\0';
	a[aCount] = '\0';
	p[pCount] = '\0';
     	w[wCount] = '\0';
}

void extract_alpha_num(char* s, char* a){
	//char* a is string alphanumeric characters
	//char* s is current string
   	int i = 0, j = 0;

	//while current char != new line character
	//and string length < 100
   	while(s[i] != '\0' && i < MAX_STRING_LENGTH) {

		//convert char to int
		//if int is alphanumeric
      		if( isalnum( (int) s[i]) ) {
			a[j] = s[i];
			j++;
		}
		i++;
   	}
	//add new line to array containing alphanumeric character
   	a[j] = '\0';
}
