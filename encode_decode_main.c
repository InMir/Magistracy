#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "func_encode_decode.h"

int main(void)
{
	int number;
	char command = '4';
	printf("Enter the number to encode: ");
	scanf("%d", &number);
	printf("Command\n0 - encoding with the first function\n1 - function 1\n2 - function 2\ne - exit\nn - new number to encode\n");
	while(command != 'e'){
		if(command == '0'){
			encode_f0(number);
			printf("Number encode! Decoding...\n");
			printf("You number: %d\n", decode_f0());
		}
		if(command == '1'){
			encode_f1(number);
			printf("Number encode! Decoding...\n");
			printf("You number: %d\n", decode_f1());
		}
		if(command == '2'){
			encode_f2(number);
			printf("Number encode! Decoding...\n");
			printf("You number: %d\n", decode_f2());
		}
		if(command == 'n'){
			printf("Enter the number to encode: ");
			scanf("%d", &number);
		}
		scanf("%c", &command);			
	}
	return 0;
}
