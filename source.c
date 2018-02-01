#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define CHAR_COUNT 26

typedef enum{
	ENCODE = 0,
	DECODE,
	INVALID
}op_mode;

void generateCharMap(char *key, char *alpha);
void decode(FILE *in, FILE *out, char *lookupTbl);
void encode(FILE *in, FILE *out, char *lookupTbl);

int main(int argc, char *argv[])   
{
	op_mode mode = INVALID;
	FILE *input, *output;
	char *input_file_name, *output_file_name;
	char *key;
	char charMap[26];
	
	//If more than one command line argument is present, quit
	if(argc<5){
		fprintf(stdout,"This program requires 5 arguments.");
		exit(0);
	}else{
		//assign command line args to usable vars
		input_file = argv[1];
		output_file = argv[3];
		key = argv[2];
		if(argv[4] == 'e'){
			//encryption mode 
			mode = ENCODE;
		}else if (argv[4] == 'd'){
			//decryption mode
			mode = DECODE;
		}else{
			mode = INVALID;
			exit(1)
		}
	}
	
	
	//Open input and output files
	input = fopen (input_file_name,"r" );
	output = fopen (output_file_name, "w" );
	
	if (input == NULL || output == NULL){
		printf("Files could not be opened\n");
		exit(1);
	}
	
	//Generate character mapping with key
	generateCharMap(&key, charMap);
	
}
void decode(FILE *in, FILE *out, char *lookupTbl){
	char input;
	uint8_t upper = 0, lower = 0;
	fscanf(in, "%c", &input);
	//If not end of file process chars
	while ( ! feof(in) )   {
		upper = 0;
		lower = 0;
		//Process character
		if(isalpha(ch)){
			if(islower(ch)){
				lower=1;
				//find conversion value
			}else if(isupper(ch)){
				upper=1;
				//find conversion value
			}
		}
		
		//Print processed character to output file with appropriate case
		if(upper){
			fprintf ( out, "%c", toupper(input) );
		}else{
			fprintf( out, "%c", tolower(input) );
		}
		
		//Read next character
		fscanf ( in, "%c", &ch );
	}
	return;
}
void encode(FILE *in, FILE *out, char *lookupTbl){
	char input;
	uint8_t upper = 0, lower = 0;
	fscanf(in, "%c", &input);
	//If not end of file process chars
	while ( ! feof(in) )   {
		upper = 0;
		lower = 0;
		//Process character
		if(isalpha(ch)){
			if(islower(ch)){
				lower=1;
				//find conversion value
			}else if(isupper(ch)){
				upper=1;
				//find conversion value
			}
		}
		
		//Print processed character to output file with appropriate case
		if(upper){
			fprintf ( out, "%c", toupper(input) );
		}else{
			fprintf( out, "%c", tolower(input) );
		}
		
		//Read next character
		fscanf ( in, "%c", &ch );
	}
	return;
}
//using the key string and the concepts behind a ceaser cipher and new alphabet
//will be generated.
void generateCharMap(char *key, char *alpha){
	//for char in string add to alpha
	//then starting with int value for 'a' if not int key? add to array
	size_t len = strlen(key);
	int i;
	for(i = 0; i<len; i++){
		alpha[i]=tolower(key[i]); // make sure lower case 
	}
	//strncpy(alpha,src,len);
	int i;
	char *rtn;
	for(i=0; i<CHAR_COUNT; i++){
		//if char not in alpha already place it there 
		rtn = strchr(alpha, 0x61+i); //'a' incremented by one each time
		if(rtn == NULL){
			alpha[i+(len-1)]=(0x61+i);
		}
		//else pass
	}
	
	return 0;
}
