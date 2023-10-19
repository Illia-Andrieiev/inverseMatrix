#include <iostream>
#include"Shtrassen.cpp"
using namespace std;
//**************************************************************************************
double* createArrWithOne(int n);
void swap(double* arr, int position1, int position2, int n);
double** createEmptyMatrix(int n);
double** createMatrixFromConsole(int n);
double** createIdentityMatrix(int n);
void writeArrInMatrixColumn(double** matrix, double* arr, int n, int columnNomer);
double** copyMatrix(double** matrix, int n);
void printMatrix(double** matrix, int n);
void deleteMatrix(double** matrix, int n);
double summArrsForLUSolve(double* arr1, double* arr2, int startIndex, int endIndex);
double** LUDecomposition(double** matrix, int n);
double* LUSolve(double** LUmatrix, double* res, int n);
double** inverseMatrix(double** matrix, int n);
//**************************************************************************************
int main() {
	double** matr3 = createMatrixFromConsole(3);
	double** inverse = inverseMatrix(matr3, 3);
	cout << "************************" << endl;
	printMatrix(matr3, 3);
	
	cout << "************************" << endl;
	printMatrix(inverse, 3);
	cout << "************************" << endl;
	double** res = createIdentityMatrix(3);
	printMatrix(res, 3);
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
	deleteMatrix(inverse, 3);
	return 0;
}
// Створює квадратну матрицю розмірності n з консолі
double** createMatrixFromConsole(int n) {
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
// Проводить LU-розклад матриці. Не змінює задану, працюючи у копії
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
	// Пряма підстановка
	for (int i = 1; i < n; i++) {
		y[i] = res[i] - summArrsForLUSolve(LUmatrix[i], y, 0, i - 2) - y[i - 1] * LUmatrix[i][i - 1];
	}
	// Оберенена підстановка
	for (int i = n - 1; i > -1; i--) {
		x[i] = (y[i] - summArrsForLUSolve(LUmatrix[i], x, i + 1, n - 1)) / LUmatrix[i][i];
	}
	delete[] y;
	return x;
}
// Знаходить обернену матрицю вирішуючи n систем лінійних рвнянь типу Ах = I(n) за допомогою LU-розкладу
double** inverseMatrix(double** matrix, int n) {
	double** inverse = createEmptyMatrix(n);
	double* Ii = createArrWithOne(n); // Поточний рядок одиничної матриці розмірності n
	double** LUMatrix = LUDecomposition(matrix, n);
	for (int i = 0; i < n; i++) {
		double* Xi = LUSolve(LUMatrix, Ii, n); // Розв'язок і-ї системи рівнянь
		writeArrInMatrixColumn(inverse, Xi, n, i); // Запис розв'язку у і-тий стовпчик результату
		swap(Ii, i, i + 1, n); // Пересуваємо одиницю на один індекс вправо
		delete[] Xi;
	}
	// Звільнення пам'яті
	delete[] Ii;
	deleteMatrix(LUMatrix, n);
	return inverse;
}
// Створює масив розмірнсті n з 1 на 0-й позиції та 0 на всіх інших
double* createArrWithOne(int n) {
	double* res = new double[n];
	res[0] = 1;
	for (int i = 1; i < n; i++)
		res[i] = 0;
	return res;
}
// Міняє місцями елементи у масиві на вказаних позиціях 
void swap(double* arr, int position1, int position2, int n) {
	if (position1 >= n || position2 >= n)
		return;
	double temp = arr[position1];
	arr[position1] = arr[position2];
	arr[position2] = temp;
}
// Створює порожню квадратну матрицю
double** createEmptyMatrix(int n) {
	double** newMatrix = new double* [n];
	for (int i = 0; i < n; i++)
		newMatrix[i] = new double[n];
	return newMatrix;
}
// Записує масив у вказаний стовпчик матриці
void writeArrInMatrixColumn(double** matrix, double* arr, int n, int columnNomer) {
	for (int i = 0; i < n; i++)
		matrix[i][columnNomer] = arr[i];
}