/****************************************************************************************
*                                                                                       *
*                        ИНФОРМАТИКА И ВЫЧИСЛИТЕЛЬНАЯ ТЕХНИКА                           *
*                                                                                       *
*****************************************************************************************
*    Prodgect type: ConsoleApplication                                                  *
*    Progect name:  2С_Laba2                                                            *
*    File name:     2С_Laba2.сpp                                                        *
*    Language:      Cpp, MSVS 2017                                                      *
*    Programmes:    М3О-107Б-18                                                         *
*                   Гордеев Никита                                                      *
*                   Онгарбаев Бауржан                                                   *
*    Modified by:   13.02.2019                                                          *
*    Created:       14.02.2019                                                          *
*    Comment:       Лабораторная работа №6                                              *
****************************************************************************************/
#include "pch.h"
#include <conio.h>
#include <iostream>
#include <fstream>
using namespace std;
const char *FNAME_1 = "Text0.txt";	const char *FNAME_2 = "Text10.txt";	//файл несуществует
//const char *FNAME_1 = "Text2.txt";	const char *FNAME_2 = "Text9.txt";	//файл пуст
//const char *FNAME_1 = "Text3.txt";	const char *FNAME_2 = "Text8.txt";	//в файле не число
//const char *FNAME_1 = "Text4.txt";	const char *FNAME_2 = "Text7.txt";	//n < 0
//const char *FNAME_1 = "Text8.txt";	const char *FNAME_2 = "Text6.txt";	//n не число
//const char *FNAME_1 = "Text5.txt";	const char *FNAME_2 = "Text11.txt";	//матрица не квадратная
//const char *FNAME_1 = "Text12.txt";	const char *FNAME_2 = "Text13.txt";	//в одной из строк элементов на 1 больше а в другой меньще
//const char *FNAME_1 = "Text6.txt";	const char *FNAME_2 = "Text4.txt";	//одна из строк заполнена не полностью или переполнина
//const char *FNAME_1 = "Text7.txt";	const char *FNAME_2 = "Text3.txt";	//нет надпобочьной диогонали
//const char *FNAME_1 = "Text9.txt";	const char *FNAME_2 = "Text2.txt";	//n = 0
//const char *FNAME_1 = "Text10.txt";	const char *FNAME_2 = "Text0.txt";	//все элементы чётные
//const char *FNAME_1 = "Text11.txt";	const char *FNAME_2 = "Text5.txt";	//единственный нечотный элемент и он отрицательный во второй строке 
//const char *FNAME_1 = "Text13.txt";	const char *FNAME_2 = "Text12.txt";	//n > NMAX
//const char *FNAME_1 = "Text14.txt";	const char *FNAME_2 = "Text15.txt";	//maxsum=0
//const char *FNAME_1 = "Text15.txt";	const char *FNAME_2 = "Text14.txt";	//maxsum<0

//const char *FNAME_1 = "Text.txt";	const char *FNAME_2 = "Text1.txt";
const int NMAX = 10;										//максимальный размер матрицы

bool ReadMatr(const char* fin, int pMatr[][NMAX], int &n);	//чтение матрицы
void PrintMatr(int pMatr[][NMAX], int n);					//вывод матрицы
int Pruv(const char* fin, int pMatr[][NMAX], int &n);		//задание 1
double MaxSym(const char* fin, int pMatr[][NMAX], int &n);	//задание 2
void Our(int ReadMatr, const char *FNAME);					//ошибки
void Zadaha(const char *FNAME);								//пезедача данных в ф-ии

//реализация программы через динамический массив
bool ReadMatr2(const char* fin, int **ppMatr, int &n);		//чтение матрицы
void PrintMatr2(int **ppMatr, int &n);						//вывод матрицы
int Pruv2(const char* fin, int **ppMatr, int &n);			//задание 1
double MaxSym2(const char* fin, int **ppMatr, int &n);		//задание 2
bool Zadaha2(const char *FNAME);							//пезедача данных в ф-ии

int main() {
	Zadaha2(FNAME_1);
	Zadaha2(FNAME_2);
	Zadaha(FNAME_1);
	Zadaha(FNAME_2);
	return 0;
}

//пезедача данных в ф-ии
void Zadaha(const char *FNAME) {
	setlocale(LC_ALL, "Russian");				//подключаю русский язык
	int	Matr[NMAX][NMAX] = { 0 };				//матрица
	int	n;										//размер матрицы
	if (ReadMatr(FNAME, Matr, n))				//если ввод выполнен коректно
	{
		PrintMatr(Matr, n);						//вывод матрицы
		if (Pruv(FNAME, Matr, n) >= 0)			//задача 1
			cout << "\nПроизведение положительных элементов матрицы, которые расположены над\nпобочной диагональю = " 
			<< Pruv(FNAME, Matr, n) << "\n\n";
		if (MaxSym(FNAME, Matr, n) / 1 != 0)	//задача 2
			cout << "Максимум среди сумм по строкам нечётных элементов матрицы = "
			<< MaxSym(FNAME, Matr, n) << "\n\n\n";
		if (MaxSym(FNAME, Matr, n) == 0) cout << "Максимум среди сумм по строкам нечётных элементов матрицы = "
			<< MaxSym(FNAME, Matr, n) << "\n\n\n";
	}
	_getch();									//пауза
	system("cls");								//очистка экрана
	_getch();									//пауза

}

//чтение файла и нумерация ошибок
bool ReadMatr(const char* fin, int Matr[][NMAX], int &n)
{
	int i = 0;													//индекс строки матрицы
	int j = 0;													//индекс столбца матрицы
	int k = 0;													//щёчик числа элементов	
	ifstream fin2(fin);											//файловая переменная
	ifstream fin1(fin);											//файловая переменная
	if (!fin) { Our(1, fin); return false; }					//файл не найден
	fin1 >> n;													//заполнение n
	fin2 >> n;													//заполнение n
	if (fin2.eof()) { Our(2, fin); return false; }				//файл пуст
	if (fin2.fail()) { Our(4, fin); return false; }				//n не число
	if (n <= 0) { Our(3, fin); return false; }					//нет матрицы или n отрицателен

	//проверка на сдвиг элементов матрицы
	char a[1];													//вспомогательный масив
	fin1.read(a, 1);											//пропускаю первые 2 символа в файле отведенные на размер матрицы 
	//поиск количества символов в 1 строке
	while (!fin1.eof()) {
		fin1.read(a, 1);										//переход к следующему символу
		if (a[0] == ' ') k++;									//нашли символ
		if (a[0] == '\n') { j++; k++; break; }					//кончилась строка
	}
	//поиск и сравнения количиства символов в строках с 1 строкой
	while (!fin1.eof()) {
		while (!fin1.eof()) {
			fin1.read(a, 1);									//переход к следующему символу
			if (a[0] == ' ')i++;								//нашли символ
			if (a[0] == '\n') {i++; j++; break; }				//кончилась строка
		}
		if(fin1.eof()) { i++; j++; break; }						//компинсация неточности
		if (i != k) { Our(5, fin); return false; }				//если был символьный сдвиг матрицы выдать ошибку
		i = 0;
	}
	//заполнение матрицы
	i = 0; j = 0; k = 0;
	while (!fin2.eof())											//заполнение столбцов матрицы
	{
		while ((!fin2.eof()) && (i < n) )						//заполнение строк матрицы
		{
			if (fin2.fail()) { Our(4, fin); return false; }		//в файле не число
			fin2 >> Matr[j][i];									//чтение элемента матрицы
			i++;												//переход к следующей строки матрицы
			k++;												//щитаем колличество элементов в матрице
		}		
		j++;													//переход к следующему столбцу матрицы
		i = 0;													//переход в начало строки
	}
	if (j != n) { Our(5, fin); return false; }					//матрица не квадратная
	if (n > NMAX) { Our(6, fin); return false; }				//размерность матрицы больше максимальной
}

//печать матрицы на экран
void PrintMatr(int Matr[][NMAX], int n) {
	int	i, j;
	j = 0; i = 0;
	while (j < n)
	{
		while (i < n)
		{
			cout << Matr[j][i] << "\t";
			i++;
		}
		cout << "\n";
		i = 0;
		j++;
	}
}

//Произведение положительных элементов матрицы, которые расположены над побочной диагональю
int Pruv (const char* fin, int Matr[][NMAX], int &n) {
	int		pruv = 1;									//искомое произведение
	bool f = false;										//флаг существования диогонали поверх побочьной
	int i = n - 1;										//индекс строки первого элемента стоящего над побочьной диогональю
	int j = 0;											//индекс столбца первого элемента стоящего над побочьной диогональю
	for (j = 0; j < n - 1; j++)							//идём над побочьной диогональю
	{
		for (i = n - 2 - j; i >= 0; i--)				//идём над побочьной диогональю
		{
			if (Matr[j][i]>0)
			{
				f = true;								//нужная диогональ существует
				pruv = pruv * Matr[j][i];				//перемножаем элементы
			}
		}
	}
	if (f == false) {
		Our(0, fin);
		return -1;
	}
	else {
		//cout << "\n\n\nПроизведение положительных элементов матрицы, которые расположены над\nпобочной диагональю = " << pruv << "\n\n";
		return pruv;
	}
}

//Максимум среди сумм по строкам нечётных элементов матрицы
double MaxSym(const char* fin, int Matr[][NMAX], int &n) {
	int		Sym = 0;									//сумма нечётных элементов текущей строки
	double		MaxSym = 0;									//искомая сумма
	int		i, j;										//индексные переменные
	bool f = false;										//флаг существования нечётных элементов матрицы
	bool k = false;										//вспомогательный флаг для обозначения факта суммы
	//поиск первой суммы нечётных элементов 
	j = 0;
	while ((j < n) && (f == false))
	{
		for (i = 0; i < n; i++)
		{
			if (abs (Matr[j][i]) % 2 == 1)
			{
				MaxSym = MaxSym + Matr[j][i];
				f = true;								//нужная элемент существует
			}
		}
		j++;
		i = 0;
	}
	while (j < n)										//поиск искомой суммы
	{
		k = false;
		while (i < n)									//сумма нечётных элементов текущей строки
		{
			if (abs(Matr[j][i]) % 2 == 1)
			{
				k = true;
				Sym = Sym + Matr[j][i];
			}
			i++;
		}
		if ((k!=0)&&(MaxSym < Sym)) { MaxSym = Sym; }	//если она больше предыдущего максимума, запоминаем
		Sym =0;
		i = 0;
		j++;
	}
	if (f == false) {										//если сложений непроисходило сообщить об ошибке
		Our(7, fin);
		return 0.5;
	}
	else {
		//cout << "Максимум среди сумм по строкам нечётных элементов матрицы = " << MaxSym << "\n\n\n";
		return  MaxSym;
	}
}

//щшибки
void Our(int N_oh, const char *FNAME) {
	switch (N_oh)
	{
	case 0: {cout << "\n\n\nОШИБКА! В файле " << FNAME << " у матрицы нет положительных элементов над побочьной диогональю\n\n\n"; break; }
	case 1: {cout << "\n\n\nОШИБКА! Файл " << FNAME << " не найден\n\n\n"; break; }
	case 2: {cout << "\n\n\nОШИБКА! Файл " << FNAME << " пуст\n"; break; }
	case 3: {cout << "\n\n\nОШИБКА! Некоректрый ввод n " << FNAME << "\n\n\n" << endl; break; }
	case 4: {cout << "\n\n\nОШИБКА! Не удалось прочитать файл\n\n\n"; break; }
	case 5: {cout << "\n\n\nОШИБКА! Матрица не квадратная\n\n\n"; break; }
	case 6: {cout << "\n\n\nОШИБКА! размерность матрицы больше максимальной\n\n\n"; break; }
	case 7: {cout << "\n\n\nОШИБКА! В файле " << FNAME << " у матрицы нет нечётных элементов\n\n\n"; break; }
	default:
		cout << "Неизвестный код ошибки" << N_oh << endl;
	}
}

/****************************************************************************************
*                                                                                       *
*                        РЕАЛИЗАЦИЯ ЧЕРЕЗ ДИНАМИЧЕСКИЙ МАССИВ                           *
*                                                                                       *
****************************************************************************************/


bool Zadaha2(const char *FNAME) {
	setlocale(LC_ALL, "Russian");					//подключаю русский язык
	bool f=false;									//флаг заполнения массива
	int	n;											//размер матрицы
	{												//чтение n из файла
	ifstream fin(FNAME);							//файловая переменная
	if (!fin) { Our(1, FNAME); }					//файл не найден
	fin >> n;
	if (fin.eof()) { Our(2, FNAME); _getch(); system("cls"); _getch(); return false; }	//файл пуст
	if (fin.fail()) { Our(4, FNAME); _getch(); system("cls"); _getch(); return false; }//n не число
	if (n <= 0) { Our(3, FNAME); _getch(); system("cls"); _getch(); return false; }	//нет матрицы или n отрицателен
	}
	int **ppMatr;									//двойной указатель на массив целых
	ppMatr = new int *[n];							//указатель на массив диких указателей 
	for (int i = 0; i < n; i++)
	{
		//выделение памяти под каждый элемент строки конкретной длины
		ppMatr[i] = new int[n];						//указатель на массив чисел
	}
	if (ReadMatr2(FNAME, ppMatr, n))				//если ввод выполнен коректно
	{
		PrintMatr2(ppMatr, n);						//вывод матрицы
		if (Pruv2(FNAME, ppMatr, n) >= 0)			//задача 1
			cout << "\nПроизведение положительных элементов матрицы, которые расположены над\nпобочной диагональю = "
			<< Pruv2(FNAME, ppMatr, n) << "\n\n";
		if (MaxSym2(FNAME, ppMatr, n) / 1.0 != 0)	//задача 2
			cout << "Максимум среди сумм по строкам нечётных элементов матрицы = " 
			<< MaxSym2(FNAME, ppMatr, n) << "\n\n\n";
		if (MaxSym2(FNAME, ppMatr, n) == 0) cout << "Максимум среди сумм по строкам нечётных элементов матрицы = "
			<< MaxSym2(FNAME, ppMatr, n) << "\n\n\n";
		f = true;									//массив инецеализирован
	}
	_getch();										//пауза
	system("cls");									//очистка экрана
	_getch();
	if (f) {										//если масив был заполнен удаляем его
		//освобождение памяти в обратном порядке
		for (int i = 0; i < n; i++)
		{
			delete[]  ppMatr[i];						//удаляем строки  (массивы)
		}
		delete[]  ppMatr;								//удаляем массив указателей на строки
	}
}

bool ReadMatr2(const char* fin, int **ppMatr, int &n)
{
	int i = 0;													//индекс строки матрицы
	int j = 0;													//индекс столбца матрицы
	int k = 0;													//щёчик числа элементов	
	ifstream fin2(fin);											//1 файловая переменная
	ifstream fin1(fin);											//2 файловая переменная
	if (!fin) { Our(1, fin); return false; }					//файл не найден
	fin2 >> n;													//заполнение n
	fin1 >> n;													//заполнение n
	if (fin2.eof()) { Our(2, fin); return false; }				//файл пуст
	if (fin2.fail()) { Our(4, fin); return false; }				//n не число
	if (n <= 0) { Our(3, fin); return false; }					//нет матрицы или n отрицателен

	char a[1];													//вспомогательный масив
	fin1.read(a, 1);											//пропускаю первые 2 символа в файле отведенные на размер матрицы 
	//поиск количества символов в 1 строке
	while (!fin1.eof()) {
		fin1.read(a, 1);										//переход к следующему символу
		if (a[0] == ' ') k++;									//нашли символ
		if (a[0] == '\n') { j++; k++; break; }					//кончилась строка
	}
	//поиск и сравнения количиства символов в строках с 1 строкой
	while (!fin1.eof()) {
		while (!fin1.eof()) {
			fin1.read(a, 1);									//переход к следующему символу
			if (a[0] == ' ')i++;								//нашли символ
			if (a[0] == '\n') { i++; j++; break; }				//кончилась строка
		}
		if (fin1.eof()) { i++; j++; break; }					//компинсация неточности
		if (i != k) { Our(5, fin); return false; }				//если был символьный сдвиг матрицы выдать ошибку
		i = 0;
	}

	i = 0; j = 0; k = 0;
	while (!fin2.eof())											//заполнение столбцов матрицы
	{
		while ((!fin2.eof()) && (i < n))						//заполнение строк матрицы
		{
			if (fin2.fail()) { Our(4, fin); return false; }		//в файле не число
			fin2 >> *(*(ppMatr+i)+j);							//чтение элемента матрицы
			i++;												//переход к следующей строки матрицы
			k++;												//щитаем колличество элементов в матрице
		}
		j++;													//переход к следующему столбцу матрицы
		i = 0;													//переход в начало строки
	}
	if (j != n) { Our(5, fin); return false; }					//матрица не квадратная
}
void PrintMatr2(int **ppMatr, int &n) {
	int	i, j;
	j = 0; i = 0;
	while (j < n)
	{
		while (i < n)
		{
			cout << *(*(ppMatr + i) + j) << "\t";
			i++;
		}
		cout << "\n\n";
		i = 0;
		j++;
	}
}

//Произведение положительных элементов матрицы, которые расположены над побочной диагональю
int Pruv2(const char* fin, int **ppMatr, int &n) {
	int		pruv = 1;									//искомое произведение
	bool f = false;										//флаг существования диогонали поверх побочьной
	int i = n - 1;										//индекс строки первого элемента стоящего над побочьной диогональю
	int j = 0;											//индекс столбца первого элемента стоящего над побочьной диогональю
	for (j = 0; j < n - 1; j++)							//идём над побочьной диогональю
	{
		for (i = n - 2 - j; i >= 0; i--)				//идём над побочьной диогональю
		{
			if (*(*(ppMatr + i) + j) > 0)
			{
				f = true;								//нужная диогональ существует
				pruv = pruv * *(*(ppMatr + i) + j);		//перемножаем элементы
			}
		}
	}
	if (f == false) {
		Our(0, fin);
		return -1;
	}
	else
		return pruv;
		//cout << "\n\n\nПроизведение положительных элементов матрицы, которые расположены над\nпобочной диагональю = " << pruv << "\n\n";
}

//Максимум среди сумм по строкам нечётных элементов матрицы
double MaxSym2(const char* fin, int **ppMatr, int &n) {
	int		Sym = 0;									//сумма нечётных элементов текущей строки
	int		MaxSym = 0;									//искомая сумма
	int		i, j;										//индексные переменные
	bool f = false;										//флаг существования нечётных элементов матрицы
	bool k = false;										//вспомогательный флаг для обозначения факта суммы
	//поиск первой суммы нечётных элементов 
	j = 0;
	while ((j < n) && (f == false))
	{
		for (i = 0; i < n; i++)
		{
			if (abs(*(*(ppMatr + i) + j)) % 2 == 1)
			{
				MaxSym = MaxSym + *(*(ppMatr + i) + j);
				f = true;								//нужная элемент существует
			}
		}
		j++;
		i = 0;
	}
	while (j < n)										//поиск искомой суммы
	{
		k = false;
		while (i < n)									//сумма нечётных элементов текущей строки
		{
			if (abs(*(*(ppMatr + i) + j)) % 2 == 1)
			{
				k = true;
				Sym = Sym + *(*(ppMatr + i) + j);
			}	i++;
		}
		if ((k != 0) && (MaxSym < Sym)) { MaxSym = Sym; }	//если она больше предыдущего максимума, запоминаем
		Sym = 0;
		i = 0;
		j++;
	}
	if (f == false) {										//если сложений непроисходило сообщить об ошибке
		Our(7, fin);
		return 0.5;
	}
	else {
		//cout << "Максимум среди сумм по строкам нечётных элементов матрицы = " << MaxSym << "\n\n\n";
		return  MaxSym;
	}
}