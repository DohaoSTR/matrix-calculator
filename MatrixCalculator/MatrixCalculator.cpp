#include <iostream>
#include <list>
#include <sstream>
#include "Matrix.cpp"

using namespace std;

void GetRandomMatrix(Matrix& matrix, int rowsCount, int columnsCount, int randomStart, int randomEnd)
{
    for (int i = 0; i < rowsCount; i++)
    {
        for (int j = 0; j < columnsCount; j++)
        {
            double randomValue = randomStart + rand() % (randomEnd - randomStart);

            matrix.SetValue(i, j, randomValue);
        }
    }
}

void PrintMatrix(Matrix& matrix, int rowsCount, int columnsCount, string message)
{
    cout << message << endl;

    for (int i = 0; i < rowsCount; i++)
    {
        for (int j = 0; j < columnsCount; j++)
        {
            cout << matrix.GetValue(i, j) << " ";
        }

        cout << endl;
    }
}

void PrintOptions()
{
    cout << "0.Выйти из программы." << endl;
    cout << "1.Создать матрицу." << endl;
    cout << "2.Вывод матрицы." << endl;
    cout << "3.Вывод всех матриц." << endl;
    cout << "4.Триангуляция матрицы." << endl;
    cout << "5.Поиск определителя матрицы." << endl;
    cout << "6.Сложение матриц." << endl;
    cout << "7.Вычитание матриц." << endl;
    cout << "8.Умножение матриц." << endl;
    cout << "9.Транспонирование матрицы." << endl;
}

Matrix CreateMatrix(Matrix& matrix, int rowsCount, int columnsCount)
{
    bool isEnterRange = true;
    int a, b;
    while (isEnterRange)
    {
        cout << "\nВведите диапазон генерации случайных чисел:\nОт - ";
        cin >> a;

        cout << "До - ";
        cin >> b;

        if (a == b)
        {
            cout << "\nЗначение начала диапазона не должно быть ровно значению его конца!\n";
        }
        else if (a > b)
        {
            cout << "\nЗначение начала диапазона должно быть меньше значения его конца!\n";
        }
        else
        {
            isEnterRange = false;
        }
    }

    GetRandomMatrix(matrix, rowsCount, columnsCount, a, b);

    return matrix;
}

int* GetIndexOfMatrixs()
{
    int indexFirstMatrix, indexSecondMatrix;

    cout << "Введите номер первой матрицы - ";
    cin >> indexFirstMatrix;

    cout << "Введите номер второй матрицы - ";
    cin >> indexSecondMatrix;

    int* indexes = new int[2];
    indexes[0] = indexFirstMatrix;
    indexes[1] = indexSecondMatrix;

    return indexes;
}

pair<Matrix, Matrix> FindMatrixs(list<Matrix> matrixs, int indexFirstMatrix, int indexSecondMatrix)
{
    Matrix firstMatrix;
    Matrix secondMatrix;

    int index = 0;
    for (Matrix matrix : matrixs)
    {
        if (index == indexFirstMatrix)
        {
            firstMatrix = matrix;
        }

        if (index == indexSecondMatrix)
        {
            secondMatrix = matrix;
        }

        index++;
    }

    pair<Matrix, Matrix> findedMatrix;
    findedMatrix.first = firstMatrix;
    findedMatrix.second = secondMatrix;

    return findedMatrix;
}

int main()
{
    cout.setf(ios::fixed);
    cout.precision(0);
    setlocale(LC_ALL, "Russian");

    list<Matrix> createdMatrix = list<Matrix>();

    while (true)
    {
        try
        {
            PrintOptions();

            cout << "\nВведите номер операции: ";
            int numberOfOperation;
            cin >> numberOfOperation;

            cout << "\n";

            switch (numberOfOperation)
            {
            case 0:
            {
                return 0;
            }
            case 1:
            {
                int rowsCount, columnsCount;

                cout << "Введите количество строк матрицы - ";
                cin >> rowsCount;

                cout << "Введите количество столбцов матрицы - ";
                cin >> columnsCount;

                Matrix matrix(rowsCount, columnsCount);

                CreateMatrix(matrix, rowsCount, columnsCount);

                createdMatrix.push_back(matrix);
                break;
            }
            case 2:
            {
                int indexMatrix;

                cout << "Введите номер матрицы - ";
                cin >> indexMatrix;

                int index = 0;
                for (Matrix matrix : createdMatrix)
                {
                    if (index == indexMatrix)
                    {
                        PrintMatrix(matrix, matrix.GetRowsCount(), matrix.GetColumnsCount(), "Матрица №" + to_string(index) + ":");
                    }

                    index++;
                }

                break;
            }
            case 3:
            {
                int index = 0;
                for (Matrix matrix : createdMatrix)
                {
                    PrintMatrix(matrix, matrix.GetRowsCount(), matrix.GetColumnsCount(), "Матрица №" + to_string(index) + ":");
                    cout << "\n";
                    index++;
                }

                break;
            }
            case 4:
            {
                int indexMatrix;

                cout << "Введите номер матрицы - ";
                cin >> indexMatrix;

                int index = 0;
                for (Matrix matrix : createdMatrix)
                {
                    if (index == indexMatrix)
                    {
                        Matrix triangleMatrix(matrix.GetRowsCount(), matrix.GetRowsCount());
                        triangleMatrix = matrix.GetTriangle();

                        PrintMatrix(triangleMatrix, matrix.GetRowsCount(), matrix.GetColumnsCount(), "Треугольная матрица:");
                    }

                    index++;
                }

                break;
            }
            case 5:
            {
                int indexMatrix;

                cout << "Введите номер матрицы - ";
                cin >> indexMatrix;

                int index = 0;
                for (Matrix matrix : createdMatrix)
                {
                    if (index == indexMatrix)
                    {
                        double determinant = matrix.GetDeterminant();
                        cout << "Определитель матрицы №" << indexMatrix + 1 << ": " << determinant;
                    }

                    index++;
                }

                break;
            }
            case 6:
            {
                int* indexes = GetIndexOfMatrixs();

                pair<Matrix, Matrix> matrixs = FindMatrixs(createdMatrix, indexes[0], indexes[1]);

                Matrix additionMatrixByMethod = matrixs.first.Addition(matrixs.second);
                Matrix additionMatrixByOverload = matrixs.first + matrixs.second;

                PrintMatrix(additionMatrixByMethod, additionMatrixByMethod.GetRowsCount(), additionMatrixByMethod.GetColumnsCount(),
                    "Результат сложения матриц №" + to_string(indexes[0]) + " и №" + to_string(indexes[1]) + " (с помощью метода):");

                cout << "\n";

                PrintMatrix(additionMatrixByOverload, additionMatrixByOverload.GetRowsCount(), additionMatrixByOverload.GetColumnsCount(),
                    "Результат сложения матриц №" + to_string(indexes[0]) + " и №" + to_string(indexes[1]) + " (с помощью перегрузки оператора):");

                break;
            }
            case 7:
            {
                int* indexes = GetIndexOfMatrixs();

                pair<Matrix, Matrix> matrixs = FindMatrixs(createdMatrix, indexes[0], indexes[1]);

                Matrix differenceMatrixByMethod = matrixs.first.Difference(matrixs.second);
                Matrix differenceMatrixByOverload = matrixs.first - matrixs.second;

                PrintMatrix(differenceMatrixByMethod, differenceMatrixByMethod.GetRowsCount(), differenceMatrixByMethod.GetColumnsCount(),
                    "Результат вычитания двух матриц №" + to_string(indexes[0]) + " и №" + to_string(indexes[1]) + " (с помощью метода):");

                cout << "\n";

                PrintMatrix(differenceMatrixByOverload, differenceMatrixByOverload.GetRowsCount(), differenceMatrixByOverload.GetColumnsCount(),
                    "Результат вычитания двух матриц №" + to_string(indexes[0]) + " и №" + to_string(indexes[1]) + " (с помощью перегрузки оператора):");

                break;
            }
            case 8:
            {
                int* indexes = GetIndexOfMatrixs();

                pair<Matrix, Matrix> matrixs = FindMatrixs(createdMatrix, indexes[0], indexes[1]);

                Matrix multiplicationMatrixByMethod = matrixs.first.Multiplication(matrixs.second);
                Matrix multiplicationMatrixByOverload = matrixs.first * matrixs.second;

                PrintMatrix(multiplicationMatrixByMethod, multiplicationMatrixByMethod.GetRowsCount(), multiplicationMatrixByMethod.GetColumnsCount(),
                    "Результат умножения матриц №" + to_string(indexes[0]) + " и №" + to_string(indexes[1]) + " (с помощью метода):");

                cout << "\n";

                PrintMatrix(multiplicationMatrixByOverload, multiplicationMatrixByOverload.GetRowsCount(), multiplicationMatrixByOverload.GetColumnsCount(),
                    "Результат умножения матриц №" + to_string(indexes[0]) + " и №" + to_string(indexes[1]) + " (с помощью перегрузки оператора):");

                break;
            }
            case 9:
            {
                int indexMatrix;

                cout << "Введите номер матрицы - ";
                cin >> indexMatrix;

                int index = 0;
                for (Matrix matrix : createdMatrix)
                {
                    if (index == indexMatrix)
                    {
                        Matrix transposeMatrix = matrix.Transpose();

                        PrintMatrix(transposeMatrix, matrix.GetRowsCount(), matrix.GetColumnsCount(), "Транспонированная матрица:");
                    }

                    index++;
                }

                break;
            }
            default:
            {
                cout << "Неверно введён номер операции!" << endl;
                break;
            }
            }

            cout << "\nОперация выполнена!\n\n";
        }
        catch (exception& error)
        {
            cout << error.what() << endl;
        }
    }
}
