#include <iostream>
using namespace std;
//**************************************************************************************
double** createMatrix(int n);
double** createIdentityMatrix(int n);
double** copyMatrix(double** matrix, int n);
void printMatrix(double** matrix, int n);
void deleteMatrix(double** matrix, int n);
double** LUDecomposition(double** matrix, int n);
//**************************************************************************************
int main() {
	double** matr4 = createMatrix(4);
	//double** matr3i = createIdentityMatrix(3);
	//double** matr5i = createIdentityMatrix(5);
	//double** Copymatr3 = copyMatrix(matr3,3);
	//double** Copymatr5i = copyMatrix(matr5i, 5);
	printMatrix(matr4, 4);
	double** luMatr = LUDecomposition(matr4, 4);
	cout << "************************" << endl;
	printMatrix(luMatr, 4);
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
	deleteMatrix(matr4, 4);
	deleteMatrix(luMatr, 4);
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