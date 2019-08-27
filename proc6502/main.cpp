#include <iostream>
#include <functional>
#include "proc6502.h"

int main()
{
	double x[3][4] = {
		{1, 2, 3, 5},
		{2, 4, 6, 10},
		{5, 2, 7, 1}
	};

	for (int i = 0; i < 3; ++i)
	{
		double piv = x[i][i];
		for (int j = 0; j < 4; j++)
		{
			x[i][j] /= piv;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << x[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}