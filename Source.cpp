#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Headers\fileio.h"
#include "Headers\matrix.h"
#include <string>
using namespace std;

void enterPhrase(int[], int *);
void createKey(float[][3]);
void ensureValid(float[][3], float *);
void matrixMultiplication(float[][3], int[], int[], int);
void displayMessage(int, int[]);
int main()
{
	srand(time(0));
	bool run = true;
	cout << "*****************************************************************************************************************************************************************************************************" << endl;
	cout << "                                                                                                >EncrypToText<" << endl;
	cout << "*****************************************************************************************************************************************************************************************************" << endl;
	cout << "                                                                                         >Written by: Aditya Vidyadharan<" << endl;
	cout << "*****************************************************************************************************************************************************************************************************" << endl;
	cout << "Use this program to encrypt a message. You will need to choose the mode (encryption or decryption), path of the encrypted message file, and then choose to run the program again or exit" << endl;
	while (run)
	{
		int phraseASCII[1000]; //phrase will be stored into array as ASCII characters
		int numLetter; //number of letters
		int cipherText[1000]; //encrypted text
		float key[3][3]; //encryption key
		float determinant = 0;
		char answer;
		string path;
		////////////////////////////////////////////////////////////////////////////////////////////////
		cout << "Encryption(e) or Decryption(d) mode?" << endl;
		cin >> answer;
		switch (answer)
		{
		case 'e':
			cout << "Enter path for decryption file" << endl;
			cin >> path;
			cin.ignore();
			enterPhrase(phraseASCII, &numLetter);
			ensureValid(key, &determinant);
			matrixMultiplication(key, phraseASCII, cipherText, numLetter);
			writeToFile(path, numLetter, cipherText, key);
			cout << "Run again? y/n" << endl;
			cin >> answer;
			if (answer == 'y')
				run = true;
			else
				run = false;
			break;
		case 'd':
			cout << "Enter path for encryption file" << endl;
			cin >> path;
			readFromFile(path, &numLetter, cipherText, key);
			calcDeterminant(key, &determinant);
			minorKey(key);
			cofactorMatrix(key);
			adjointKey(key);
			inverseMatrix(key, determinant);
			matrixMultiplication(key, cipherText, phraseASCII, numLetter);
			displayMessage(numLetter, phraseASCII);
			cout << "Run again? y/n" << endl;
			cin >> answer;
			if (answer == 'y')
				run = true;
			else
				run = false;
			break;
		default:
			cout << "Enter valid input ('e' or 'd)" << endl;
		}
	}
}
void enterPhrase(int output[], int *outLet)
{
	cout << "Enter phrase to encrypt" << endl;
	char temp;
	for (*outLet = 1; ((temp = cin.get()) != '\n'); *outLet+=1)
		output[*outLet - 1] = temp;
	*outLet -= 1;
	if (*outLet % 3 == 2)
		output[++*outLet - 1] = ' ';
	if (*outLet % 3 == 1)
		for (int count = 0; count < 2; count++)
			output[++*outLet - 1] = ' ';

}
void createKey(float output[][3])
{
	for (int row = 0; row < 3; row++)
		for (int column = 0; column < 3; column++)
			output[row][column] = rand() % 100 + 1;
}
void ensureValid(float key[][3], float *det)
{
	while (*det == 0)
	{
		createKey(key);
		calcDeterminant(key, det);
	}
}
void matrixMultiplication(float key[][3], int source[], int output[], int numLet)
{
	int reps = numLet / 3; //number of sets of three
	int usedSpace = 0;
	float sum = 0;
	for (int counter = 0; counter < reps; counter++)
		for (int row = 0; row < 3; row++) //creates cipher text for each set of three words
		{
			for (int column = 0; column < 3; column++)
				sum += key[row][column] * source[counter * 3 + column];
			output[usedSpace++] = roundf(sum);
			sum = 0;
		}	
}
void displayMessage(int numLet, int outputPhrase[])
{
	cout << "MESSAGE DECRYPTED" << endl;
	cout << "Message is: ";
	char temp;
	for (int count = 0; count < numLet && (temp = outputPhrase[count]); count++)
		cout << temp;
	cout << endl;
}