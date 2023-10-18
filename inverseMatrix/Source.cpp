#include <iostream>
using namespace std;
//**************************************************************************************
double** createMatrix(int n);
double** createIdentityMatrix(int n);
double** copyMatrix(double** matrix, int n);
void printMatrix(double** matrix, int n);
void deleteMatrix(double** matrix, int n);
double summArrsForLUSolve(double* arr1, double* arr2, int startIndex, int endIndex);
double** LUDecomposition(double** matrix, int n);
double* LUSolve(double** LUmatrix, double* res, int n);
//**************************************************************************************
int main() {
	double** matr3 = createMatrix(3);
	double b[] = { -2,7,8 };
	double** luMatr = LUDecomposition(matr3, 3);
	double* res = LUSolve(luMatr, b, 3);
	//double** matr3i = createIdentityMatrix(3);
	//double** matr5i = createIdentityMatrix(5);
	//double** Copymatr3 = copyMatrix(matr3,3);
	//double** Copymatr5i = copyMatrix(matr5i, 5);
	//printMatrix(matr3, 3);

	cout << "************************" << endl;
	for (int i = 0; i < 3; i++)
		cout << res[i] << "\t";
	cout << "************************" << endl;

	//printMatrix(luMatr, 3);
	//printMatrix(matr3i, 3);
	//cout << "************************" << endl;
	//printMatrix(matr5i, 5);
	//cout << "************************" << endl;
	//printMatrix(Copymatr3, 3);
	//cout << "************************" << endl;
	//printMatrix(Copymatr5i, 5);
	//deleteMatrix(matr3i, 3);
	//deleteMatrix(Copymatr3, 3);
	//deleteMatrix(matr5i, 5);
	//deleteMatrix(Copymatr5i, 5);
	deleteMatrix(matr3, 3);
	deleteMatrix(luMatr, 3);
	delete[] res;
	return 0;
}
// Створює квадратну матрицю розмірності n
double** createMatrix(int n) {
	double** matrix = new double* [n];
	for (int i = 0; i < n; i++) {
		double* str = new double[n];
		matrix[i] = str;
		for (int j = 0; j < n; j++) {
			cout << "enter elemnt at " << i << " " << j << " index: ";
			cin >> matrix[i][j];
			cout << endl;
		}
	}
	return matrix;
}
// Виводить у консоль квадратну матрицю
void printMatrix(double** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}
// Створює одиничну матрицю порядку n
double** createIdentityMatrix(int n) {
	double** matrix = new double* [n];
	for (int i = 0; i < n; i++) {
		double* str = new double[n];
		matrix[i] = str;
		for (int j = 0; j < n; j++) {
			if (j == i)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;
		}
	}
	return matrix;
}
// Копіює матрицю
double** copyMatrix(double** matrix, int n) {
	double** new_matrix = new double* [n];
	for (int i = 0; i < n; i++) {
		double* str = new double[n];
		new_matrix[i] = str;
		for (int j = 0; j < n; j++) {
			if (j == i)
				new_matrix[i][j] = matrix[i][j];
			else
				new_matrix[i][j] = matrix[i][j];
		}
	}
	return new_matrix;
}
// Видаляє матрицю
void deleteMatrix(double** matrix, int n) {
	for (int i = 0; i < n; i++) {
		delete matrix[i];
	}
	delete matrix;
}
// Проводить LU-розклад матриці
double** LUDecomposition(double** matrix, int n) {
	double** res = copyMatrix(matrix, n);
	for (int i = 0; i < n; i++) {
		res[i][i] = res[i][i];
		for (int j = i + 1; j < n; j++) {
			res[j][i] = res[j][i] / res[i][i];
			res[i][j] = res[i][j];
		}
		for (int j = i + 1; j < n; j++) {
			for (int k = i + 1; k < n; k++) {
				res[j][k] = res[j][k] - res[j][i] * res[i][k];
			}
		}
	}
	return res;
}
// Суммує добутки відповідних елементів массивів для LUSolve. Включно StartIndex та endIndex
double summArrsForLUSolve(double* arr1, double* arr2, int startIndex, int endIndex) {
	double res = 0;
	for (int i = startIndex; i <= endIndex; i++)
		res += arr1[i] * arr2[i];
	return res;
}
// Вирішує систему лінійних рівнянь. LUmatrix зберігає матриці L і U 
double* LUSolve(double** LUmatrix, double* res, int n) {
	double* x = new double[n];
	double* y = new double[n];
	y[0] = res[0];
	for (int i = 1; i < n; i++) {
		y[i] = res[i] - summArrsForLUSolve(LUmatrix[i], y, 0, i - 2) - y[i - 1] * LUmatrix[i][i - 1];
	}
	cout << "************************" << endl;
	for (int i = 0; i < n; i++)
		cout << y[i] << "\t";
	for (int i = n - 1; i > -1; i--) {
		x[i] = (y[i] - summArrsForLUSolve(LUmatrix[i], x, i + 1, n - 1)) / LUmatrix[i][i];
	}
	delete[] y;
	return x;
}