#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H


namespace sm 
{

	struct Cell
	{
		int j;
		int data;
		Cell* next = nullptr;
	};

	struct Vec 
	{
		int n;
		Cell* scell = nullptr;
	};

	struct Row
	{
		int i;
		Cell* scell = nullptr;
		Row* next = nullptr;
	};

	struct SparseMatrix
	{
		int m;
		int n;

		Row* srow = nullptr;
	};

	typedef enum err_codes
	{
		EC_GOOD = 0,
		EC_BAD
	}RC;

	static bool getNum(int& num);

	static RC set(SparseMatrix* mat, int i, int j, int data);

	SparseMatrix* input();
	SparseMatrix* by_criterion(SparseMatrix* mat);
	RC output(SparseMatrix* mat);
	void input_par(int &par);

	RC erase(SparseMatrix* mat);

	static void crit_1(int **ln, int len);
	static void get_am(int a, int *b);
	static bool is_in(int a, int *ln, int len);

}


#endif // SPARSEMATRIX_H
