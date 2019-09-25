#include <iostream>
#include <conio.h>
#include <sstream>
#include "SparseMatrix.h"

#define ESC 27

namespace sm {

	bool getNum(int& num)
	{
		int n;
		std::cin >> n;

		bool g = std::cin.good();

		if (g)
			num = n;

		return g;
	}

	void input_par(int &par)
	{
		int a;
		while (true)
		{
			bool fl = getNum(a);
			if (fl == false)
			{
				std::cout << "Error, try again: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			if (fl == true)
			{
				if (a < 0)
				{
					std::cout << "Error, try again: ";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				par = a;
				break;
			}
		}
	}

	void set(SparseMatrix* mat, int i, int j, int data)
	{
		if (!mat || i < 0 || i >= mat->m || j < 0 || j >= mat->n)
			return;


		// find row

		Row* crow = mat->srow;

		if (!crow) {

			mat->srow = new Row;
			mat->srow->i = i;
			mat->srow->next = nullptr;
			mat->srow->scell = new Cell;
			mat->srow->scell->next = nullptr;
			mat->srow->scell->j = j;
			mat->srow->scell->data = data;

		}
		else {
			if (i < crow->i) { // found in begin

				mat->srow = new Row;
				mat->srow->i = i;
				mat->srow->next = crow;
				mat->srow->scell = new Cell;
				mat->srow->scell->next = nullptr;
				mat->srow->scell->j = j;
				mat->srow->scell->data = data;

			}
			else { // mid/end

				while (i >= crow->i) {
					if (i == crow->i) {

						// found

						Cell* ccell = crow->scell;

						if (j < ccell->j) { // cell begin
							crow->scell = new Cell;
							crow->scell->next = ccell;
							crow->scell->j = j;
							crow->scell->data = data;
							break;
						}
						else { // cell mid/end

							while (j >= ccell->j) {

								if (j == ccell->j) {
									ccell->data = data;
									break;
								}
								else if (ccell->next) {

									if (j < ccell->next->j) {
										Cell* oldnext = ccell->next;
										ccell->next = new Cell;
										ccell->next->next = oldnext;
										ccell->next->j = j;
										ccell->next->data = data;
										break;
									}
									else {
										ccell = ccell->next;
										continue;
									}

								}
								else { // last cell
									ccell->next = new Cell;
									ccell->next->next = nullptr;
									ccell->next->j = j;
									ccell->next->data = data;
									break;
								}

							}

						}

					}
					else if (crow->next) {
						if (i < crow->next->i) {
							Row* oldnext = crow->next;
							crow->next = new Row;
							crow->next->next = oldnext;
							crow->next->i = i;
							crow->next->scell = new Cell;
							crow->next->scell->next = nullptr;
							crow->next->scell->j = j;
							crow->next->scell->data = data;
							break;
						}
						else {
							crow = crow->next;
							continue; // advance
						}
					}
					else { // if last elem
						crow->next = new Row;
						crow->next->next = nullptr;
						crow->next->i = i;
						crow->next->scell = new Cell;
						crow->next->scell->next = nullptr;
						crow->next->scell->j = j;
						crow->next->scell->data = data;
						break;
					}
					break;
				}

			}
		}
	}


	SparseMatrix* input()
	{
		char Continue;
		SparseMatrix* mat = new SparseMatrix;

		std::cout << "Enter m: ";
		input_par(mat->m);

		std::cout << "Enter n: ";
		input_par(mat->n);

		int i, j, data;

		while (1)
		{
			std::cout << "Input i, j and data of cell: " << std::endl;
			std::cout << "i: ";
			input_par(i);
			std::cout << "j: ";
			input_par(j);
			std::cout << "data of cell: ";
			input_par(data);

			if (data != 0)
				set(mat, i, j, data);

			std::cout << "Press ESC to out or press Enter to continue: ";
			Continue = _getch();
			if (Continue == ESC)
			{
				std::cout << "ESC" << std::endl;
				break;
			}
			else
			{
				std::cout << "Continue" << std::endl;
			}

		}

		return mat;
	}

	void get_am(int a, int *b)
	{
		int count = 1;
		int d = 10;
		while (a >= d) 
		{ 
			d *= 10; 
			count++; 
		}
		*b = count;
	}

	void crit_1(int **ln, int len)
	{
		int sum = 0;
		int b = 0;
		for (int i = 0; i < len; i++)
		{
			get_am((*ln)[i], &b);
			sum += b;
		}
		int av = sum / len;
		for (int i = 0; i < len; i++)
		{
			get_am((*ln)[i], &b);
			if (b > av)
			{
				continue;
			}
			else
			{
				(*ln)[i] = 0;
			}
		}
	}


	bool is_in(int a, int *ln, int len)
	{
		for (int i = 0; i < len; i++)
		{
			if (ln[i] == a)
			{
				return true;
			}
		}
		return false;
	}

	SparseMatrix * by_criterion(SparseMatrix* mat)
	{
		SparseMatrix* mat_2 = new SparseMatrix;
		mat_2->m = mat->m;
		mat_2->n = mat->n;
		int *line;
		line = new int[mat->n];
		for (int i = 0; i < mat->n; i++)
			line[i] = 0;
		int counter = 0;
		Row* crow = mat->srow;

		Cell* ccell = nullptr;
		if (crow)
			ccell = crow->scell;

		while (crow) 
		{
			Cell* ccell_2 = ccell;

			while (ccell) 
			{
				line[counter] = ccell->data;
				ccell = ccell->next;
				counter++;
			}
			crit_1(&line, mat->n);
			counter = 0;

			while (ccell_2)
			{
				if (is_in(ccell_2->data, line, mat->n))
				{
					set(mat_2, crow->i, ccell_2->j, ccell_2->data);
				}
				ccell_2 = ccell_2->next;
			}

			for (int i = 0; i < mat->n; i++)
				line[i] = 0;
			

			crow = crow->next;
			if (crow)
				ccell = crow->scell;
		}

		return mat_2;
	}

	void output(SparseMatrix* mat)
	{
		if (!mat)
			return;


		std::cout << "[" << mat->m << " x " << mat->n << "]" << std::endl;

		Row* crow = mat->srow;

		Cell* ccell = nullptr;
		if (crow)
			ccell = crow->scell;

		while (crow) 
		{
			while (ccell) 
			{
				std::cout << "(" << crow->i << " " << ccell->j << ") " << ccell->data << std::endl;
				ccell = ccell->next;
			}



			crow = crow->next;
			if (crow)
				ccell = crow->scell;
		}

		std::cout << std::endl;
	}


	void erase(SparseMatrix* mat)
	{
		if (!mat)
			return;


		Row* tmprow;
		while (mat->srow) {
			tmprow = mat->srow->next;

			Cell* tmpcell;
			while (mat->srow->scell) {
				tmpcell = mat->srow->scell->next;
				delete mat->srow->scell;
				mat->srow->scell = tmpcell;
			}

			delete mat->srow;
			mat->srow = tmprow;
		}
	}

}
