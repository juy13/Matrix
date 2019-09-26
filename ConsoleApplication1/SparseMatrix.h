#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H


namespace sm 
{
	/* Клетка матрицы, внутри список */
	struct Cell
	{
		int j;
		int data;
		Cell* next = nullptr;
	};

	/* Строка матрицы, внутри список строк и список клеток */
	struct Row
	{
		int i;
		Cell* scell = nullptr;
		Row* next = nullptr;
	};

	/* Структура матрицы */
	struct SparseMatrix
	{
		int m;
		int n;

		Row* srow = nullptr;
	};

	/* Набор кодов возврата */
	typedef enum err_codes
	{
		EC_GOOD = 0,
		EC_BAD
	}RC;


	/* Рабочие функции, которые во внешней части программы */
	SparseMatrix* input();
	SparseMatrix * by_criterion(SparseMatrix* mat, int tp);
	RC output(SparseMatrix* mat);
	RC erase(SparseMatrix* mat);

	/* Функции, которые работают во внутреннем модуле программы */
	static bool getNum(int& num);
	static RC set(SparseMatrix* mat, int i, int j, int data);
	static void input_par(int &par);
	static void crit_1(int **ln, int len);
	static void get_am(int a, int *b);
	static bool is_in(int a, int *ln, int len);
	static void crit_2(int **ln, int len);

}


#endif // SPARSEMATRIX_H
