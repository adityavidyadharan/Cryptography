//Arien:
#pragma once
#include <iostream>
using namespace std;
void arrCopy(float original[][3], float copy[][3])
{
	for (int r = 0; r < 3; r++)
		for (int c = 0; c < 3; c++)
			copy[r][c] = original[r][c];
}
void calcDeterminant(float source[3][3], float *output)
{
	float modifyKey[3][5];
	//create modifiedoriginalTemp for determinant
		//copy original elements oforiginalTemp
		for (int row = 0; row < 3; row++)
		{
			for (int column = 0; column < 3; column++)
				modifyKey[row][column] = source[row][column];
		}
		//create duplicate first two columns on end
		for (int row = 0; row < 3; row++)
		{
			for (int column = 3; column < 5; column++)
				modifyKey[row][column] = source[row][column - 3];
		}
	//start finding determinant
		int product = 1;
		for (int counter = 0; counter < 3; counter++)
		{
			for (int row = 0; row < 3; row++)
			{
				product *= modifyKey[row][row + counter];
			}
			*output += product;
			product = 1;
		}
		for (int counter = 2; counter < 5; counter++)
		{
			for (int row = 0; row < 3; row++)
			{
				product *= modifyKey[row][counter - row];
			}
			*output -= product;
			product = 1;
		}
}
void minorKey(float key[][3])
{
	float originalTemp[3][3]; //temporary array to hold original key
	arrCopy(key, originalTemp);
	key[0][0] = originalTemp[1][1] * originalTemp[2][2] - originalTemp[2][1] * originalTemp[1][2];
	key[0][1] = originalTemp[1][0] * originalTemp[2][2] - originalTemp[2][0] * originalTemp[1][2];
	key[0][2] = originalTemp[1][0] * originalTemp[2][1] - originalTemp[2][0] * originalTemp[1][1];
	key[1][0] = originalTemp[0][1] * originalTemp[2][2] - originalTemp[2][1] * originalTemp[0][2];
	key[1][1] = originalTemp[0][0] * originalTemp[2][2] - originalTemp[2][0] * originalTemp[0][2];
	key[1][2] = originalTemp[0][0] * originalTemp[2][1] - originalTemp[2][0] * originalTemp[0][1];
	key[2][0] = originalTemp[0][1] * originalTemp[1][2] - originalTemp[1][1] * originalTemp[0][2];
	key[2][1] = originalTemp[0][0] * originalTemp[1][2] - originalTemp[1][0] * originalTemp[0][2];
	key[2][2] = originalTemp[0][0] * originalTemp[1][1] - originalTemp[1][0] * originalTemp[0][1];
}
void cofactorMatrix(float key[][3])
{
	float originalTemp[3][3];
	arrCopy(key, originalTemp);
	for (int count = 0, row = 0; row < 3; row++)
		for (int column = 0; column < 3; column++, count++)
				if (count % 2 == 1)
					key[row][column] = originalTemp[row][column] * -1;
				else
					key[row][column] = originalTemp[row][column];
}
void adjointKey(float key[][3])
{
	float originalTemp[3][3];
	arrCopy(key, originalTemp);
	for (int row = 0; row < 3; row++)
		for (int column = 0; column < 3; column++)
			key[column][row] = originalTemp[row][column]; 
}
void inverseMatrix(float key[][3], float determinant)
{
	float originalTemp[3][3];
	arrCopy(key, originalTemp);
	for (int row = 0; row < 3; row++)
		for (int column = 0; column < 3; column++)
			key[row][column] = originalTemp[row][column] / determinant;
}