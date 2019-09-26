#include <iostream>
#include "SparseMatrix.h"



int main()
{
	sm::RC rc = sm::EC_BAD;
    sm::SparseMatrix* mat = sm::input();
	std::cout << "Our matrix: " << std::endl;
    rc = sm::output(mat);
	if (rc != sm::EC_GOOD)
	{
		std::cout << "Error in matrix" << std::endl;
	}
	sm::SparseMatrix* mat_2 = sm::by_criterion(mat);
	std::cout << "New matrix: " << std::endl;
	rc = sm::output(mat_2);
	if (rc != sm::EC_GOOD)
	{
		std::cout << "Error in matrix" << std::endl;
	}
    rc = sm::erase(mat);
	if (rc != sm::EC_GOOD)
	{
		std::cout << "Error in matrix" << std::endl;
	}
}

