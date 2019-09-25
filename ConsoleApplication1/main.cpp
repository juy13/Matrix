#include <iostream>
#include "SparseMatrix.h"



int main()
{
    sm::SparseMatrix* mat = sm::input();
    sm::output(mat);
	sm::SparseMatrix* mat_2 = sm::by_criterion(mat);
	sm::output(mat_2);
    //sm::Vec v = sm::vecProc(mat);
    //sm::vecOutput(v);
    sm::erase(mat);
}

