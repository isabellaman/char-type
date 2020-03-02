/*
 * Isabella Man
 * 1602153
 * CSE 15
 * 10/17/19
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

// function prototype
void extract_chars(char* s, char* a, char* d, char* p, char* w);

// function main which takes command line arguments 
int main(int argc, char* argv[]){
	FILE* in;        // handle for input file                  
   	FILE* out;       // handle for output file                 
   	char* line;      // string holding input line              

	char* a; 	//alphabetic
	char* d;        //digit	
	char* p; 	//punctuation
	char* w; 	//whitespace characters

   	if( argc != 3 ){
      		printf("Usage: %s input-file output-file\n", argv[0]);
      		exit(EXIT_FAILURE);
   	}
   	if( (in=fopen(argv[1], "r"))== NULL ){		// open input file for reading
      		printf("Unable to read from file %s\n", argv[1]);
      		exit(EXIT_FAILURE);
   	}
	if( (out=fopen(argv[2], "w"))== NULL ){		//open output file for writing
      		printf("Unable to write to file %s\n", argv[2]);
      		exit(EXIT_FAILURE);
   	}

   	// allocate strings line on the heap 
   	line = calloc(MAX_STRING_LENGTH+1, sizeof(char));

	// allocate a, d, p, w on the heap
        a = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
        d = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
        p = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
        w = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
	assert(a != NULL && d != NULL && p != NULL && w != NULL);
        assert(line != NULL);

   	/* read each line in input file, extract alpha-numeric characters 
	 * syntax of fgets(pointer, num chars, pointer to file)
	 * 1 = pointer to array where string read is copied
	 * 2 = number of characters to be copied into string
	 * 3 = pointer to file object
	 * func returns a string
	 */

	int curLine = 1;
   	while ( fgets(line, MAX_STRING_LENGTH, in) != NULL ){
      		//extract_alpha_num(line, alpha_num);
      		//fprintf(out, "%s\n", alpha_num);
		
		extract_chars(line, a, d, p, w);
		fprintf(out, "line %d contains: \n", curLine);
		fprintf(out, "%lu alphabetic characters: %s\n", strlen(a), a);
                fprintf(out, "%lu numeric characters: %s\n", strlen(d), d);
                fprintf(out, "%lu punctuation characters: %s\n", strlen(p), p);
                fprintf(out, "%lu whitespace characters: %s\n\n", strlen(w), w);
		curLine++;
   	}

	// free heap memory 
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

   	// close input and output files 
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
        
	//fprintf(out, "%d numeric characters: %s\n", dCount, d);
	
	//printf("There are %d digits\n", dCount);
}

// function definition 
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
		//have to increment i outside of if
		//if condition is never met, never increments i
		i++;
   	}
	//add new line to array containing alphanumeric character
   	a[j] = '\0';
}

