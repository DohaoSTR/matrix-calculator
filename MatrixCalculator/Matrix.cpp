#include <iostream>

#include "NoneSquareMatrixException.cpp"
#include "IndexOutOfRangeException.cpp"

using namespace std;

class Matrix
{
private:
    int _rowsCount;
    int _columnsCount;

    double** _matrix;

public:
    Matrix()
    {
        _rowsCount = _columnsCount = 0;
        _matrix = nullptr;
    }

    Matrix(int rowsCount, int columnsCount)
    {
        _rowsCount = rowsCount;
        _columnsCount = columnsCount;

        _matrix = new double* [rowsCount];
        for (int i(0); i < rowsCount; i++)
        {
            _matrix[i] = new double[columnsCount];
        }
    }

    Matrix(const Matrix& matrix)
    {
        _rowsCount = matrix.GetRowsCount();
        _columnsCount = matrix.GetColumnsCount();

        _matrix = new double* [_rowsCount];
        for (int i(0); i < _rowsCount; i++)
        {
            _matrix[i] = new double[_columnsCount];
        }

        for (int i = 0; i < _rowsCount; i++)
        {
            for (int j = 0; j < _columnsCount; j++)
            {
                _matrix[i][j] = matrix.GetValue(i, j);
            }
        }
    }

    double GetValue(int row, int column) const
    {
        return _matrix[row][column];
    }

    bool SetValue(int row, int column, double value)
    {
        if (row <= _rowsCount && column <= _columnsCount)
        {
            _matrix[row][column] = value;

            return true;
        }
        else
        {
            return false;
        }
    }

    int GetRowsCount() const
    {
        return _rowsCount;
    }

    int GetColumnsCount() const
    {
        return _columnsCount;
    }

    bool IsSquare() const
    {
        if (_rowsCount == _columnsCount)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool IsRowsEqual(const Matrix& matrix) const
    {
        return GetRowsCount() == matrix.GetRowsCount();
    }

    bool IsColumnsEqual(const Matrix& matrix) const
    {
        return GetColumnsCount() == matrix.GetColumnsCount();
    }

    bool IsEqualDimension(const Matrix& matrix) const
    {
        return IsRowsEqual(matrix) && IsColumnsEqual(matrix);
    }

    Matrix CopyTo(const Matrix& matrix) const
    {
        if (IsEqualDimension(matrix))
        {
            Matrix copyMatrix(matrix.GetRowsCount(), matrix.GetColumnsCount());

            for (int i = 0; i < copyMatrix.GetRowsCount(); i++)
            {
                for (int j = 0; j < copyMatrix.GetColumnsCount(); j++)
                {
                    copyMatrix.SetValue(i, j, matrix.GetValue(i, j));
                }
            }

            return copyMatrix;
        }
        else
        {
            throw new IndexOutOfRangeException("Матрица не равной размерности!");
        }
    }

    Matrix GetTriangle() const
    {
        Matrix triangleMatrix(*this);

        for (int i = 0; i < triangleMatrix.GetRowsCount() - 1; i++)
        {
            for (int j = i + 1; j < triangleMatrix.GetRowsCount(); j++)
            {
                double coefficient = triangleMatrix.GetValue(i, i) == 0 ? 0 : triangleMatrix.GetValue(j, i) / triangleMatrix.GetValue(i, i);

                for (int k = i; k < triangleMatrix.GetRowsCount(); k++)
                {
                    triangleMatrix.SetValue(j, k, triangleMatrix.GetValue(j, k) - triangleMatrix.GetValue(i, k) * coefficient);
                }
            }
        }

        return triangleMatrix;
    }

    double GetDeterminant() const
    {
        if (IsSquare())
        {
            double determinant = 1;

            Matrix triangleMatrix(GetRowsCount(), GetColumnsCount());
            triangleMatrix = GetTriangle();

            for (int i = 0; i < triangleMatrix.GetRowsCount(); i++)
            {
                determinant *= triangleMatrix.GetValue(i, i);
            }

            return determinant;
        }
        else
        {
            throw NoneSquareMatrixException("Матрица не является квадратной!");
        }
    }

    Matrix Addition(const Matrix& matrix) const
    {
        if (IsEqualDimension(matrix))
        {
            Matrix resultOfAdditionMatrix(GetRowsCount(), matrix.GetColumnsCount());

            for (int i = 0; i < resultOfAdditionMatrix.GetRowsCount(); i++)
            {
                for (int j = 0; j < resultOfAdditionMatrix.GetColumnsCount(); j++)
                {
                    resultOfAdditionMatrix.SetValue(i, j, GetValue(i, j) + matrix.GetValue(i, j));
                }
            }

            return resultOfAdditionMatrix;
        }
        else
        {
            throw new IndexOutOfRangeException("Матрицы не одинаковой размерности!");
        }
    }

    Matrix Difference(const Matrix& matrix) const
    {
        if (IsEqualDimension(matrix))
        {
            Matrix resultDifferenceMatrix(GetRowsCount(), matrix.GetColumnsCount());

            for (int i = 0; i < resultDifferenceMatrix.GetRowsCount(); i++)
            {
                for (int j = 0; j < resultDifferenceMatrix.GetColumnsCount(); j++)
                {
                    resultDifferenceMatrix.SetValue(i, j, GetValue(i, j) - matrix.GetValue(i, j));
                }
            }

            return resultDifferenceMatrix;
        }
        else
        {
            throw new IndexOutOfRangeException("Матрицы не одинаковой размерности!");
        }
    }

    Matrix Multiplication(const Matrix& matrix) const
    {
        if (GetColumnsCount() == matrix.GetRowsCount())
        {
            Matrix resultMultiplicationMatrix(GetRowsCount(), matrix.GetColumnsCount());

            for (int i = 0; i < resultMultiplicationMatrix.GetRowsCount(); i++)
            {
                for (int j = 0; j < resultMultiplicationMatrix.GetColumnsCount(); j++)
                {
                    resultMultiplicationMatrix.SetValue(i, j, 0);

                    for (int m = 0; m < GetColumnsCount(); m++)
                    {
                        double resultValue = resultMultiplicationMatrix.GetValue(i, j) + GetValue(i, m) * matrix.GetValue(m, j);
                        resultMultiplicationMatrix.SetValue(i, j, resultValue);
                    }
                }
            }

            return resultMultiplicationMatrix;
        }
        else
        {
            throw new IndexOutOfRangeException("Число столбцов первой матрицы не равно числу строк второй матрицы!");
        }
    }

    Matrix Transpose() const
    {
        Matrix transposeMatrix(GetColumnsCount(), GetRowsCount());

        for (int i = 0; i < GetRowsCount(); i++)
        {
            for (int j = 0; j < GetColumnsCount(); j++)
            {
                transposeMatrix.SetValue(j, i, GetValue(i, j));
            }
        }

        return transposeMatrix;
    }

    Matrix operator=(const Matrix& matrix)
    {
        if (_rowsCount > 0)
        {
            for (int i = 0; i < _columnsCount; i++)
            {
                delete[] _matrix[i];
            }
        }

        if (_columnsCount > 0)
        {
            delete[] _matrix;
        }

        _rowsCount = matrix.GetRowsCount();
        _columnsCount = matrix.GetColumnsCount();

        _matrix = new double* [_rowsCount];
        for (int i(0); i < _rowsCount; i++)
        {
            _matrix[i] = new double[_columnsCount];
        }

        for (int i = 0; i < _rowsCount; i++)
        {
            for (int j = 0; j < _columnsCount; j++)
            {
                _matrix[i][j] = matrix.GetValue(i, j);
            }
        }

        return *this;
    }

    Matrix operator+(const Matrix& matrix) const
    {
        return Addition(matrix);
    }

    Matrix operator-(const Matrix& matrix) const
    {
        return Difference(matrix);
    }

    Matrix operator*(const Matrix& matrix) const
    {
        return Multiplication(matrix);
    }

    ~Matrix()
    {
        if (_rowsCount > 0)
        {
            for (int i = 0; i < _columnsCount; i++)
            {
                delete[] _matrix[i];
            }
        }

        if (_columnsCount > 0)
        {
            delete[] _matrix;
        }
    }
};