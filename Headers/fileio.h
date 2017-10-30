//Sahil:

#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

void writeToFile(string fileLocation, int numlet, int text[], float key[][3])
{
	int load = 1;
	ofstream transfer;
	transfer.open(fileLocation); //creates object to write to file using path prompted in start
	if (!transfer.is_open())
	{
		cout << "Error. Invalid file" << endl;
		exit(1);
	}
	//transfer number of letters
	transfer << numlet << endl;
	//transfer ciphertext
	for (int count = 0; count < numlet; count++)
		transfer << text[count] << endl; //writes encrypted text in array passed to function
	//transfer key
	for (int count = 0, row = 0; row < 3; row++, count++)
		for (int column = 0; column < 3; column++, count++)
			transfer << key[row][column] << endl; //writes key that was created in array
	cout << '\n' << "Encrypted" << endl;
	transfer.close();
}
void readFromFile(string fileLocation, int *numlet, int text[], float key[][3])
{
	ifstream read;
	string reading;
	int temporary;
	string string;
	read.open(fileLocation);
	if (!read.is_open())
	{
		cout << "Error. Invalid file" << endl;
		exit(1);
	}
	//read number of letters
	{
		read >> *numlet;
	}
	//read cipher text
	for (int count = 0; count < *numlet; count++)
		read >> text[count];
	//read key
	for (int count = 0, row = 0; row < 3; row++, count++)
		for (int column = 0; column < 3 && read >> temporary; column++, count++)
			key[row][column] = temporary;
	cout << "-----------------------------" << endl;
	read.close();
}