#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "func_encode_decode.h"

int encode_f0(int number)
{
    FILE *fd;
    int size_cipher = 0;
	int *cipher_number;
	char buf[1];
	
	size_cipher = number + 1;
	cipher_number = (int*)malloc(size_cipher * sizeof(int));
	
	for(int i = 0; i < number; i++){
		cipher_number[i] = 0;
	}
	cipher_number[size_cipher - 1] = 1;
		
	fd = fopen("2.txt", "w");
	if(fd == 0){
		perror("error");
		return EXIT_FAILURE;
	}
	
	for(int i = 0; i < size_cipher; i++){
		sprintf(buf, "%d", cipher_number[i]);
		fwrite(buf, sizeof(char), 1, fd);
	}
	free(cipher_number);
	fclose(fd);
	return 0;
}

int decode_f0()
{
	FILE *fd;
	char buf[1];
	char *str;
	int size_file = 0;
	int *cipher_number;
	int size_cipher = 0, count = 0;
	
	fd = fopen("2.txt", "r");
	if(fd == 0){
		perror("error");
		return EXIT_FAILURE;
	}
			
	while(!feof(fd)){
		fread(buf, sizeof(char), 1, fd);
		size_file++;
	}
	fclose(fd);

	size_cipher = size_file - 1;
	cipher_number = (int*)malloc(size_cipher * sizeof(int));

	fd = fopen("2.txt", "r");
	if(fd == 0){
		perror("error");
		return EXIT_FAILURE;
	}

	while(!feof(fd)){
		fread(buf, sizeof(char), 1, fd);
		str = buf;
		cipher_number[count] = atoi(str);
		count++;
	}
	
	fclose(fd);
/*	
	printf("Code number: ");
	for(int i = 0; i < size_cipher; i++)
		printf("%d", cipher_number[i]);
	printf("\nYou number: %d", size_cipher - 1);
*/
	return size_cipher - 1;
}

int func_bin (int number, char *bin_mas)
{
	int k = 0;	

	while (number > 0){
		bin_mas[k++] = (number % 2) + '0';
		number = number / 2;
	}
	
	bin_mas[k] = '\0';
	char tmp;
	
	for(int i = 0; i < k / 2; i++){
		tmp = bin_mas[i];
		bin_mas[i] = bin_mas[k - 1 - i];
		bin_mas[k - 1 - i] = tmp;
	}
/*	
	printf("Bin number: ");
	for(int i = 0; i < k; i++)
		printf("%c", bin_mas[i]);
	printf("\n");
*/
	return k;//размер массива в двоичном представлении числа
}

int encode_f1(int number)
{
    FILE *fd;
    int size_cipher = 0, size_bin = 0, max_size_bin_int = 32;
	char *bin_number, *cipher_number;

	bin_number = (char*)malloc(max_size_bin_int * sizeof(char));
	size_bin = func_bin(number, bin_number);

/*
	printf("Bin number: ");
	for(int i = 0; i < size_bin; i++)
		printf("%c", bin_number[i]);
*/

	size_cipher = size_bin + 1 + size_bin - 1;	
	cipher_number = (char*)malloc(size_cipher * sizeof(char));
	
	for(int i = 0; i < size_bin; i++){
		cipher_number[i] = '0';
	}
	cipher_number[size_bin] = '1';
	
	for(int i = 1; i < size_bin; i++){
		cipher_number[size_bin + i] = bin_number[i];
	}
	
/*		
	printf("\nChiper number: ");
	for(int i = 0; i < size_cipher; i++)
		printf("%c", cipher_number[i]);	
*/

	fd = fopen("2.txt", "w");
	if(fd == 0){
		perror("error");
		return EXIT_FAILURE;
	}
	fwrite(cipher_number, sizeof(char), size_cipher, fd);	
	free(bin_number);
	free(cipher_number);
	fclose(fd);
	return 0;
}

int func_dec(char *bin_mas, int size_bin_mas)
{
	int number = 0; 
	for(int i = size_bin_mas - 1; i > -1; i--)
		if(bin_mas[i] == '1')
			number += pow(2, size_bin_mas - (i + 1));
	return number;
}

int decode_f1()
{
	FILE *fd;
	char buf[1];
	char *cipher_number;
	int size_file = 0;
	int size_cipher = 0;
	int count = 0, count_1 = 0;
	
	fd = fopen("2.txt", "r");
	if(fd == 0){
		perror("error");
		return EXIT_FAILURE;
	}
			
	while(!feof(fd)){
		fread(buf, sizeof(char), 1, fd);
		size_file++;
	}
	fclose(fd);

	size_cipher = size_file - 1;
	cipher_number = (char*)malloc(size_cipher * sizeof(char));

	fd = fopen("2.txt", "r");
	if(fd == 0){
		perror("error");
		return EXIT_FAILURE;
	}

	while(!feof(fd))
		fread(cipher_number, sizeof(char), size_cipher, fd);
	fclose(fd);
	
/*	
	printf("Code number: ");
	for(int i = 0; i < size_cipher; i++)
		printf("%c", cipher_number[i]);
*/
	
	while(cipher_number[count] == '0')
		count++;
	
	int size_bin_mas = size_cipher - count;
	char bin_mas[size_bin_mas];
		
	for(int i = count; i < size_cipher; i++){
		bin_mas[count_1] = cipher_number[i];
		count_1++;
	}

/*		
	printf("\nBin you number: ");
	for(int i = 0; i < size_bin_mas; i++)
		printf("%c", bin_mas[i]);
*/	
	int ret = func_dec(bin_mas, size_bin_mas);
	return ret;
}

int encode_f2(int number)
{
    FILE *fd;
    int size_cipher = 0, size_file = 0, size_bin = 0, max_size_bin_int = 32, count = 0;
	char *bin_number, *bint_number, *cipher_number;
	char buf[1];

	bin_number = (char*)malloc(max_size_bin_int * sizeof(char));
	bint_number = (char*)malloc(max_size_bin_int * sizeof(char));
	size_bin = func_bin(number, bin_number);

	for(int i = 1; i < size_bin; i++){
		bint_number[count] = bin_number[i];
		count++;
	}
	
	encode_f1(size_bin);
	
	fd = fopen("2.txt", "r");
	if(fd == 0){
		perror("error");
		return EXIT_FAILURE;
	}
	
	while(!feof(fd)){
		fread(buf, sizeof(char), 1, fd);
		size_file++;
	}
	fclose(fd);

	size_cipher = size_file - 1;
	cipher_number = (char*)malloc(size_cipher * sizeof(char));

	fd = fopen("2.txt", "r");
	if(fd == 0){
		perror("error");
		return EXIT_FAILURE;
	}
	fread(cipher_number, sizeof(char), size_cipher, fd);
	fclose(fd);
	
	fd = fopen("2.txt", "w");
	if(fd == 0){
		perror("error");
		return EXIT_FAILURE;
	}
	fwrite(cipher_number, sizeof(char), size_cipher, fd);
	fwrite(bint_number, sizeof(char), size_bin - 1, fd);		
	free(bin_number);
	free(bint_number);
	free(cipher_number);
	fclose(fd);
	return 0;
}

int decode_f2()
{
	FILE *fd;
	char buf[1];
	char *cipher_number;
	int size_file = 0;
	int size_cipher = 0;
	int count = 0, count_1 = 1;
	
	fd = fopen("2.txt", "r");
	if(fd == 0){
		perror("error");
		return EXIT_FAILURE;
	}
			
	while(!feof(fd)){
		fread(buf, sizeof(char), 1, fd);
		size_file++;
	}
	fclose(fd);

	size_cipher = size_file - 1;
	cipher_number = (char*)malloc(size_cipher * sizeof(char));

	fd = fopen("2.txt", "r");
	if(fd == 0){
		perror("error");
		return EXIT_FAILURE;
	}

	fread(cipher_number, sizeof(char), size_cipher, fd);
	fclose(fd);
	
/*	
	printf("Code number: ");
	for(int i = 0; i < size_cipher; i++)
		printf("%c", cipher_number[i]);
*/
	
	while(cipher_number[count] == '0')
		count++;
	
	int size_bin_mas = size_cipher - count - count;
	char bin_mas[size_bin_mas];
		
	for(int i = count + count; i < size_cipher; i++){
		bin_mas[count_1] = cipher_number[i];
		count_1++;
	}
	bin_mas[0] = '1';
/*		
	printf("\nBin you number: ");
	for(int i = 0; i < size_bin_mas; i++)
		printf("%c", bin_mas[i]);
*/	
	int ret = func_dec(bin_mas, size_bin_mas + 1);
	return ret;
}
