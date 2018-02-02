/*****************************************************
*!Project: CIS241 Project 1
*!
*!Author: Joseph Cutino
*!Description: This program using command line arguments 
*!	to encode or decode text files. The user will
*!	provide an input file, output file, crypto key,
*!	and their desired action (encode (e) or decode (d))
*!	as command line arguments.
******************************************************/

/*Library Includes*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*Program Defines*/
#define CHAR_COUNT 26

/*Global Data*/
typedef enum{
	ENCODE = 0,
	DECODE,
	INVALID
}op_mode;

/*Function Prototypes*/
void generateCharMap(char *key, char *alpha);
void decode(FILE *in, FILE *out, char *lookupTbl);
void encode(FILE *in, FILE *out, char *lookupTbl);

int main(int argc, char *argv[])   
{
	/*Variable Definition*/
	op_mode mode = INVALID;
	FILE *input, *output;
	char *input_file_name, *output_file_name;
	char *key;
	char charMap[26];
	
	/*Input Error Check*/
	if(argc<5){
		//This program requires 5 arguments to run properly
		fprintf(stdout,"This program requires 5 arguments.\n");
		exit(1);
	}else{
		//assign command line args to usable vars
		input_file_name = argv[1];
		output_file_name = argv[3];
		key = argv[2];
		if(argv[4][0] == 'e'){
			//Encryption mode 
			mode = ENCODE;
		}else if (argv[4][0] == 'd'){
			//Decryption mode
			mode = DECODE;
		}else{
			//Invalid operation
			mode = INVALID;
			exit(1);
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
	generateCharMap(key, charMap);
	
	//Perform Action
	if(mode == ENCODE){
		decode(input,output,charMap);
	}else if(mode == DECODE){
		encode(input,output,charMap);
	}	
	return 0;
}

/*****************************************************
*!Input: Input file ID, Output file ID, look up Table
*!
*!Output: NONE
*!
*!Description: Decode the text in the input file and 
*!	print it to the output file.
*****************************************************/
void decode(FILE *in, FILE *out, char *lookupTbl){
	char input;
	int upper = 0;
	fscanf(in, "%c", &input);
	//If not end of file process chars
	while ( ! feof(in) )   {
		upper = 0;
		//Process character
		if(isalpha(input)){
			if(isupper(input)){
				upper=1;
			}
			input = tolower(input);
			//find conversion value
			int i;
			for(i=0;i<strlen(lookupTbl);i++){
				if(lookupTbl[i] == input){
					break;
				}
			}
			input = (char)(0x61+i);
		}
		
		//Print processed character to output file with appropriate case
		if(upper){
			fprintf ( out, "%c", toupper(input) );
		}else{
			fprintf( out, "%c", tolower(input) );
		}
		
		//Read next character
		fscanf ( in, "%c", &input );
	}
	return;
}

/*****************************************************
*!Input: Input file ID, Output file ID, look up Table
*!
*!Output: NONE
*!
*!Description: Encode the text in the input file and 
*!	print it to the output file.
*****************************************************/
void encode(FILE *in, FILE *out, char *lookupTbl){
	char input;
	int upper = 0;
	fscanf(in, "%c", &input);
	//If not end of file process chars
	while ( ! feof(in) )   {
		upper = 0;
		//Process character
		if(isalpha(input)){
			if(isupper(input)){
				upper=1;
			}
			input = tolower(input);
			//find conversion value
			input=lookupTbl[(int)(input-97)];
		}
		
		//Print processed character to output file with appropriate case
		if(upper){
			fprintf ( out, "%c", toupper(input) );
		}else{
			fprintf( out, "%c", tolower(input) );
		}
		
		//Read next character
		fscanf ( in, "%c", &input );
	}
	return;
}

/**************************************************
*!Input: Key and storage area for the look up Table
*!
*!Output: Look up table will be store in alpha
*!
*!Description: Using the key, an encryption
*!	and decryption lookup table is created.
**************************************************/
void generateCharMap(char *key, char *alpha){
	//for char in string add to alpha
	size_t len = strlen(key);
	int i;
	for(i = 0; i<len; i++){
		alpha[i]=tolower(key[i]); // make sure lower case 
	}
	//Add the remaining characters to the array
	char *rtn;
	int missed =0;
	for(i=0; i<CHAR_COUNT; i++){
		//if char not in alpha already place it there 
		char newChar = (char)(0x7A-i);
		rtn = strchr(alpha, newChar); //'a' incremented by one each time
		if(rtn == NULL){
			alpha[i+(len)-missed]=newChar;
		}else{
			missed++;
		}
		//else pass
	}	
	return;
}
