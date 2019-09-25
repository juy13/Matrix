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

	bool getNum(int& num);

	void set(SparseMatrix* mat, int i, int j, int data);

	SparseMatrix* input();
	SparseMatrix* by_criterion(SparseMatrix* mat);
	void output(SparseMatrix* mat);
	void input_par(int &par);

	void erase(SparseMatrix* mat);

	void crit_1(int **ln, int len);
	void get_am(int a, int *b);
	bool is_in(int a, int *ln, int len);

}


#endif // SPARSEMATRIX_H
