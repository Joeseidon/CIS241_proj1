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

/*DEBUGGING FUNCTIONS*/
void printCharMap(char *map);
void printFile(FILE *in);

int main(int argc, char *argv[])   
{
	op_mode mode = INVALID;
	FILE *input, *output;
	char *input_file_name, *output_file_name;
	char *key;
	char charMap[26];
#ifndef DEBUG
	//If more than one command line argument is present, quit
	if(argc<5){
		fprintf(stdout,"This program requires 5 arguments.");
		exit(0);
	}else{
		//assign command line args to usable vars
		input_file_name = argv[1];
		output_file_name = argv[3];
		key = argv[2];
		if(argv[4][0] == 'e'){
			//encryption mode 
			mode = ENCODE;
		}else if (argv[4][0] == 'd'){
			//decryption mode
			mode = DECODE;
		}else{
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
#else
	FILE *encrypted;
	FILE *decrypted;
	generateCharMap("RaNdKey", charMap);
	printCharMap(charMap);

	input = fopen ("input.txt","r" );
	output = fopen ("encrypted.txt", "w" );
	
	encode(input,output,charMap);
	
	fclose(output);
	fclose(input);
	
	input = fopen ("input.txt","r" );
	printf("\n\n/***********************ORIGINAL***********************/\n");
	printFile(input);
	fclose(input);
	
	encrypted = fopen("encrypted.txt","r");
	printf("\n\n/***********************ENCRYPTED***********************/\n");
	printFile(encrypted);
	fclose(encrypted);
	encrypted = fopen("encrypted.txt","r");
	decrypted = fopen("decrypted.txt","w");
	decode(encrypted,decrypted,charMap);
	fclose(encrypted);
	fclose(decrypted);
	decrypted = fopen("decrypted.txt","r");
	printf("\n\n/***********************DECRYPTED***********************/\n");
	printFile(decrypted);
	fclose(decrypted);
	printf("\n\n\n");
#endif
	
	return 0;
}
void printFile(FILE *in){
	char input;
	fscanf(in, "%c", &input);
	//If not end of file process chars
	while ( ! feof(in) )   {
		printf("%c",input);
		//Read next character
		fscanf ( in, "%c", &input );
	}
}
void printCharMap(char *map){
	int i;
	for(i=0; i< CHAR_COUNT; i++){
		printf("%c | ",(char)(0x61+i));
	}
	printf("\n");
	for(i=0; i<CHAR_COUNT; i++){
		printf("%c | ",map[i]);
	}
	printf("\n");
}
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