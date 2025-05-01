#include<iostream>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<cstdlib>
#include<string>
#include<stdbool.h>

using namespace std;


#define ONEKB 1024
#define TENKB 10240

// This function Generate File and Create fixed file size of 10MB with Random char  Data
// Function accept file name 

bool GenChar(char* Fptr)
{
	FILE* stream = NULL;
	char  buffer[ONEKB] = {'\0'};
	char List[ONEKB] = {'\0'};

	errno_t err = 0;
	int numwritten = 0, iCnt = 0;
	char var = '\0';

	err = fopen_s(&stream, Fptr, "w");
	if (err != 0){
		strerror_s(buffer, ONEKB, err);
		printf("The file %s was not opened with error %s\n", Fptr,buffer);
		return false;
	}
	

	for (iCnt = 0; iCnt < ONEKB; iCnt++){
		var = 'A' + rand() % 26;
		List[iCnt] = var;
	}

	for (iCnt = 0; iCnt < 10000; iCnt++){

		numwritten = fwrite(List, sizeof(char), ONEKB, stream);
		if (numwritten < (sizeof(char)* ONEKB)){
			strerror_s(buffer, ONEKB, numwritten);
			printf("the random data in file is not writeen in file name %s with error is   %s\n",Fptr, buffer);
			fclose(stream);
			return false;
		}
	}

	fclose(stream);
	return true;
}

// This function Generate File and Create fixed file size of 10MB with Random int  Data
// function accept file name 

bool GenInt(char* Fptr)
{
	FILE* stream = NULL;
	char  buffer[ONEKB] = {'\0'};
	errno_t err = 0;
	int numwritten = 0, iCnt = 0;

	err = fopen_s(&stream, Fptr, "w");
	if (err != 0){
		strerror_s(buffer, ONEKB, err);
		printf("The file %s was not opened with an error %s\n", Fptr, buffer);
		return false;
	}


	for (iCnt = 0; iCnt < TENKB * 1000; iCnt++)
	{
		char str[4] = { '\0' };
		sprintf_s(str, "%d", (rand() % 100 + 1));
		numwritten = fwrite(str, sizeof(char), 1, stream);

		if (numwritten < (sizeof(char) * 1)){
			strerror_s(buffer, ONEKB, numwritten);
			printf("the random data in file is not writeen in file name %s with error is   %s\n", Fptr, buffer);
			fclose(stream);
			return false;
		}
	}

	fclose(stream);
	return true;
}


int main()
{

	char Fname[ONEKB] = {'\0'};
	bool bRet;

	printf("Enter file name : ");
	scanf_s("%s", Fname, ONEKB);
	
	/*
	bRet = GenChar(Fname);
	if (bRet == true)
	{
		printf("Sucessfully generate char file with random data\n");
	}
	else
	{
		printf("File not sucessfully generate char file with random data\n");
	}

	*/

	bRet = GenInt(Fname);
	if (bRet == true){
		printf("Sucessfully generate int file with random data\n");
	}
	else{
		printf("File not sucessfully generate int file with random data\n");
	}

	return 0;
}