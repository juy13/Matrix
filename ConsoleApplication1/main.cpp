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
	sm::SparseMatrix* mat_2 = sm::by_criterion(mat, 1);
	std::cout << "New matrix: " << std::endl;
	rc = sm::output(mat_2);
	if (rc != sm::EC_GOOD)
	{
		std::cout << "Error in matrix" << std::endl;
	}
	sm::SparseMatrix* mat_3 = sm::by_criterion(mat, 2);
	std::cout << "New matrix: " << std::endl;
	rc = sm::output(mat_3);
	if (rc != sm::EC_GOOD)
	{
		std::cout << "Error in matrix" << std::endl;
	}
    rc = sm::erase(mat);
	if (rc != sm::EC_GOOD)
	{
		std::cout << "Error in matrix 1" << std::endl;
	}
	rc = sm::erase(mat_2);
	if (rc != sm::EC_GOOD)
	{
		std::cout << "Error in matrix 2" << std::endl;
	}
	rc = sm::erase(mat_3);
	if (rc != sm::EC_GOOD)
	{
		std::cout << "Error in matrix 3" << std::endl;
	}
}

