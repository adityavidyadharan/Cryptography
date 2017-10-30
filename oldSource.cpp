//////////////////////////////////////////////////////////////////////////////////////////////
/*
	OLD SOURCE CODE
	USE SOURCE.CPP FILE 
*/
//////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "./Headers/fileio.h"
#include "./Headers/matrix.h"
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////
/*
	Variable Names:
	Output means that it is used in encryption part
	Input means it is used in decryption
*/
//////////////////////////////////////////////////////////////////////////////////////////////
//Variables for choose mode:
char answer;
string path;

//Functions:
void enterPhrase(char [], int *); // will store text to encrypt into appropriate array
void convertText(char [], int [], int *);
void createKey(float [][3]);
void checkKeyValid(float *, float[][3], float [][5]);
void genText(int *, float [][3], int [], int []);
void encryption(int *, float[][3], int[], int[], char[]);
void convertASCII(char [], int [], int*);
void displayMessage(int *, char[]);
void decryption(int *, int [], float [][3], float [3][5], float *, float [][3], float [][3], float [][3], float [][3], int [], char[]);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Mode Choosing Function:
void chooseMode(int *, int [], float [][3], float [3][5], float *, float [][3], float [][3], float [][3], float [][3], int [], char[], int *, float [][3], int [], int [], char []);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Encryption variables:
	int outputLetters[3][1]; //set of three lettters to multiply
	char outputPhrase[1000]; //text to encrypt
	int outputPhraseASCII[1000];//text to encrypt in ascii
	int outputCipherText[1000]; //encrypted text
	float outputKey[3][3];
	int outputNumLetter; //how many characters are in the text to encrypt
	float outputDeterminant = 0;
	float outputModifiedKey[3][5];
	///////////////////////////////////////////////////////////////////////////////////////////////////
	//Decryption Variables:
	float inputKey[3][3];
	float inputDeterminant = 0; //determinant
	int inputNumLetter; //number of letters
	int inputCipherTextASCII[1000]; //text read from files - Encrypted letters as numbers
	float inputModifiedKey[3][5]; //modifed 5x3 key for determinant
	float inputInverseKey[3][3]; //inversed key
	float inputMinorKey[3][3]; //minor key
	float inputCofactorKey[3][3]; //
	float inputAdjointKey[3][3]; //transposed key for inverse
	int inputLetters[3][1]; //set of three letters for matrix multiplication
	int inputPhraseASCII[1000]; //decrypted characters - as ASCII
	char inputPhrase[1000]; //decrypted characters as final letters
							///////////////////////////////////////////////////////////////////////////////////////////////////
	chooseMode (&inputNumLetter,  inputCipherTextASCII, inputKey, inputModifiedKey, &inputDeterminant, inputMinorKey, inputCofactorKey, inputAdjointKey, inputInverseKey, inputPhraseASCII, inputPhrase, &outputNumLetter, outputKey, outputPhraseASCII, outputCipherText, outputPhrase);
}
void enterPhrase(char outputPhrase[], int *outputNumLetter) // will store text to encrypt into appropriate array
{

	std::cout << "Enter phrase to encrypt" << endl;
	for (int i = 1; ((outputPhrase[i - 1] = cin.get()) != '\n'); ++i)
	{
		*outputNumLetter = i;
	}
	if (*outputNumLetter % 3 == 2)
	{
		++*outputNumLetter;
		outputPhrase[*outputNumLetter - 1] = ' ';
	}
	if (*outputNumLetter % 3 == 1)
	{
		++*outputNumLetter;
		outputPhrase[*outputNumLetter - 1] = ' ';
		++*outputNumLetter;
		outputPhrase[*outputNumLetter - 1] = ' ';
	}
}
void convertText(char outputPhrase[], int outputPhraseASCII[], int *outputNumLetter) // will convert text to words
{
	for (int count = 0; count < *outputNumLetter; count++)
	{
		outputPhraseASCII[count] = outputPhrase[count];
	}
}
void createKey(float outputKey[][3]) //generates encryption key
{
	for (int row = 0; row < 3; row++)
	{
		for (int column = 0; column < 3; column++)
			outputKey[row][column] = rand() % 100 + 1;
	}
}
void checkKeyValid(float *outputDeterminant, float outputKey[][3], float outputModifiedKey[][5])
{
	while (outputDeterminant == 0)
	{
		createKey(outputKey);
		modifyKey(outputKey, outputModifiedKey);
		determinant(outputModifiedKey, outputDeterminant);
	}
}
void genText(int *letter, float key[][3], int ascii[], int output[])
{
	int reps = *letter / 3; //number of sets of three
	int usedSpace = 0;
	float sum = 0;
	for (int counter = 0; counter < reps; counter++)
	{
		for (int row = 0; row < 3; row++) //creates cipher text for each set of three words
		{
			for (int count = 0; count < 3; count++)
				sum += key[row][count] * ascii[counter * 3 + count];
			output[usedSpace++] = roundf(sum);
			sum = 0;
		}
	}
}
void encryption(int *outputNumLetter, float outputKey[][3], int outputPhraseASCII[], int outputCipherText[], char outputPhrase[])
{
	cin.ignore();
	srand(time(NULL));
	createKey(outputKey);
	enterPhrase(outputPhrase, outputNumLetter);
	convertText(outputPhrase, outputPhraseASCII, outputNumLetter);
	genText(outputNumLetter, outputKey, outputPhraseASCII, outputCipherText);
	writeToFile(&path, outputNumLetter, outputCipherText, outputKey);
	system("PAUSE");
}
void convertASCII(char inputPhrase[], int inputPhraseASCII[], int *inputNumLetter)
{
	for (int count = 0; count < *inputNumLetter; count++)
		inputPhrase[count] = inputPhraseASCII[count];
}
void displayMessage(int *inputNumLetter, char inputPhrase[])
{
	std::cout << "MESSAGE DECRYPTED" << endl;
	std::cout << "Message is: ";
	for (int count = 0; count < *inputNumLetter; count++)
		std::cout << inputPhrase[count];
	std::cout << endl;
}
void decryption(int *inputNumLetter, int inputCipherTextASCII[], float inputKey[][3], float inputModifiedKey[3][5], float *inputDeterminant, float inputMinorKey[][3], float inputCofactorKey[][3], float inputAdjointKey[][3], float inputInverseKey[][3], int inputPhraseASCII[], char inputPhrase[])
{
	readFromFile(&path, inputNumLetter, inputCipherTextASCII, inputKey);
	modifyKey(inputKey, inputModifiedKey);
	determinant(inputModifiedKey, inputDeterminant);
	minorKey(inputMinorKey, inputKey);
	cofactorMatrix(inputCofactorKey, inputMinorKey);
	adjointKey(inputAdjointKey, inputCofactorKey);
	inverseMatrix(inputAdjointKey, inputDeterminant, inputInverseKey);
	genText(inputNumLetter, inputInverseKey, inputCipherTextASCII, inputPhraseASCII);
	convertASCII(inputPhrase, inputPhraseASCII, inputNumLetter);
	displayMessage(inputNumLetter, inputPhrase);
	system("PAUSE");
}
void chooseMode(int *inputNumLetter, int inputCipherTextASCII[], float inputKey[][3], float inputModifiedKey[3][5], float *inputDeterminant, float inputMinorKey[][3], float inputCofactorKey[][3], float inputAdjointKey[][3], float inputInverseKey[][3], int inputPhraseASCII[], char inputPhrase[], int *outputNumLetter, float outputKey[][3], int outputPhraseASCII[], int outputCipherText[], char outputPhrase[])
{
	bool run = true;
	while (run)
	{
		cout << "Encryption(e) or Decryption(d) mode?" << endl;
		cin >> answer;
		cin.ignore();
		switch (answer)
		{
		case 'e':
			cout << "Enter path for decryption file" << endl;
			cin >> path;
			encryption(outputNumLetter, outputKey, outputPhraseASCII, outputCipherText, outputPhrase);
			run = false;
			break;
		case 'd':
			cout << "Enter path for encryption file" << endl;
			cin >> path;
			decryption(inputNumLetter, inputCipherTextASCII, inputKey, inputModifiedKey, inputDeterminant, inputMinorKey, inputCofactorKey, inputAdjointKey, inputInverseKey, inputPhraseASCII, inputPhrase);
			run = false;
			break;
		default:
			cout << "Enter valid input ('e' or 'd)" << endl;
		}
	}
}
