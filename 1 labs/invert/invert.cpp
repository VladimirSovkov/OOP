#include <iostream>
#include <fstream>
#include <string>
//0.8

using namespace std;

int MatrixFilling(double** matrix, const int SIZE_MATRIX, ifstream& inputFile)
{
	double number;

	for (int i = 0; i < SIZE_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_MATRIX; j++)
		{
			if (inputFile.eof() || !(inputFile >> number))
			{
				cout << "file is incorrectly filled" << endl;
				return 1;
			}
			matrix[i][j] = number;
		}
	}

	return 0;
}

double FindingDeterminant(double** matrix, const int SIZE_MATRIX)
{
	double multiplication = 1;
	double summ = 0;

	multiplication = matrix[0][0] * matrix[1][1] * matrix[2][2];
	summ = summ + multiplication;
	
	multiplication = matrix[1][0] * matrix[2][1] * matrix[0][2];
	summ = summ + multiplication;

	multiplication = matrix[2][0] * matrix[0][1] * matrix[1][2];
	summ = summ + multiplication;
	
	multiplication = matrix[0][2] * matrix[1][1] * matrix[2][0];
	summ = summ - multiplication;

	multiplication = matrix[1][2] * matrix[2][1] * matrix[0][0];
	summ = summ - multiplication;

	multiplication = matrix[2][2] * matrix[0][1] * matrix[1][0];
	summ = summ - multiplication;

	return summ;
}

double GetDeterminantMinorMatrix(double** matrix, 
	const int SIZE_MATRIX, 
	int column, 
	int row)
{
	const int SYZE_MINOR_MATRIX = SIZE_MATRIX - 1;
	double minorMatrix[2][2]{};
	int columnMatrix = 0;
	int rowMatrix = 0;

	for (int i = 0; i < SYZE_MINOR_MATRIX; i++)
	{
		if (column == i)
		{
			columnMatrix++;
		}
		for (int j = 0; j < SYZE_MINOR_MATRIX; j++)
		{
			if (row == j)
			{
				rowMatrix++;
			}
			minorMatrix[i][j] = matrix[columnMatrix][rowMatrix];
			rowMatrix++;
		}
		rowMatrix = 0;
		columnMatrix++;
	}

	double difference = 0;

	double multiplication = 1;
	multiplication = minorMatrix[0][0] * multiplication;
	multiplication = minorMatrix[1][1] * multiplication;
	difference = multiplication;

	multiplication = 1;
	multiplication = minorMatrix[0][1] * multiplication;
	multiplication = minorMatrix[1][0] * multiplication;

	difference = difference - multiplication;

	return difference;
}

void MatrixTranspose(double** matrix)
{
	double number = 0;
	number = matrix[0][1];
	matrix[0][1] = matrix[1][0];
	matrix[1][0] = number;

	number = matrix[0][2];
	matrix[0][2] = matrix[2][0];
	matrix[2][0] = number;

	number = matrix[1][2];
	matrix[1][2] = matrix[2][1];
	matrix[2][1] = number;
}

void GetMatrixOfAlgebraicComplements(double** matrix)
{
	matrix[0][1] *= -1;
	matrix[1][0] *= -1;
	matrix[1][2] *= -1;
	matrix[2][1] *= -1;
}

void MatrixMultiplicationByNumber(double** matrix, 
	const int SIZE_MATRIX, 
	const int number)
{
	for (int i = 0; i < SIZE_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_MATRIX; j++)
		{
			matrix[i][j] /= number;
		}
	}
}

void ConclusionMatrix(double** matrix, const int SIZE)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			cout << round(matrix[i][j] * 1000) / 1000 << "\t";//setprecision
		}
		cout << "\n";
	}
}


int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "missing arguments" << endl;
		cout << "invert.exe <matrix file>" << endl;
		return 1;
	}
	else
	{
		if (argc > 2)
		{
			cout << "mismatch with the number of arguments" << endl;
			cout << "invert.exe <matrix file>" << endl;
			return 1;
		}
	}

	string pathInput = argv[1];
	ifstream inputFile(pathInput);
	if (!inputFile.is_open())
	{
		cout << "error opening file" << endl;
		return 1;
	}

	const int SIZE_MATRIX = 3;
	double** matrix = new double* [SIZE_MATRIX];
	for (int i = 0; i < SIZE_MATRIX; i++)
	{
		matrix[i] = new double[SIZE_MATRIX];
	}

	if (MatrixFilling(matrix, SIZE_MATRIX, inputFile) == 1)
	{
		return 1;
	}

	double determinant = FindingDeterminant(matrix, SIZE_MATRIX);

	if (determinant == 0)
	{
		cout << "the inverse matrix does not exist" << endl;
		return 1;
	}

	double** inverseMatrix = new double* [SIZE_MATRIX] {};//создание двумерного динамического массива 
	for (int i = 0; i < SIZE_MATRIX; i++)
	{
		inverseMatrix[i] = new double[SIZE_MATRIX];
	}

	for (int i = 0; i < SIZE_MATRIX; i++)
	{
		//inverseMatrix[i] = new double[SIZE_MATRIX] {};
		for (int i = 0; i < SIZE_MATRIX; i++)
		{
			for (int j = 0; j < SIZE_MATRIX; j++)
			{
				inverseMatrix[i][j] = GetDeterminantMinorMatrix(matrix, SIZE_MATRIX, i, j);
			}
		}
	}

	//транспонирование матрицы
	MatrixTranspose(inverseMatrix);
	GetMatrixOfAlgebraicComplements(inverseMatrix);

	//умножение матрицы на определеитель
	MatrixMultiplicationByNumber(inverseMatrix, SIZE_MATRIX, determinant);
	ConclusionMatrix(inverseMatrix, SIZE_MATRIX);
	
	return 0;
}