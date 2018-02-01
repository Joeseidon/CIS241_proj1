#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef enum{
	ENCODE = 0,
	DECODE,
	INVALID
}op_mode;

void generateCharMap(char *key, char *alpha);


int main(int argc, char *argv[])   
{
	op_mode mode = INVALID;
	FILE *input, *output;
	char *input_file, *output_file;
	char *key;
	
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
			exit(0)
		}
	}
	
	
	//Open input and output files
	input = fopen (input_file,"r" );
	output = fopen (output_file, "w" );
	
	
}

//using the key string and the concepts behind a ceaser cipher and new alphabet
//will be generated.
void generateCharMap(char *key, char **alpha){
	
}