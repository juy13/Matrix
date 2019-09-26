#include <iostream>
#include <conio.h>
#include <sstream>
#include "SparseMatrix.h"

#define ESC 27
#define ENTER 13

namespace sm {

	/* ¬вод целых чисел из потока */
	static bool getNum(int& num)
	{
		int n;
		std::cin >> n;

		bool g = std::cin.good();

		if (g)
			num = n;

		return g;
	}

	/* ќбработчик введенных чисел */
	static void input_par(int &par)
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
				//if (a < 0)
				//{
				//	std::cout << "Error, try again: ";
				//	std::cin.clear();
				//	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				//	continue;
				//}
				par = a;
				break;
			}
		}
	}

	/* ¬вод в матрицу значений. »спользуем алгоритм таблицы и списков */
	static RC set(SparseMatrix* mat, int i, int j, int data)
	{
		/* проверка существовани€ матрицы и корректности ввода значений*/
		if (!mat || i < 0 || i >= mat->m || j < 0 || j >= mat->n)
			return EC_BAD;


		
		/* Ќаходим строку */
		Row* crow = mat->srow;

		/*если строки не существует, то инициализируем начальный элемент списка */
		if (!crow)
		{

			mat->srow = new Row;
			mat->srow->i = i;
			mat->srow->next = nullptr;
			mat->srow->scell = new Cell;
			mat->srow->scell->next = nullptr;
			mat->srow->scell->j = j;
			mat->srow->scell->data = data;

		}
		else /* иначе идем по списку строк и добавл€ем клетки */
		{
			if (i < crow->i)
			{ 
				/* вставка в начало списка */
				mat->srow = new Row;
				mat->srow->i = i;
				mat->srow->next = crow;
				mat->srow->scell = new Cell;
				mat->srow->scell->next = nullptr;
				mat->srow->scell->j = j;
				mat->srow->scell->data = data;

			}
			else
			{ 
				/* если клетка в середине */
				while (i >= crow->i)
				{
					if (i == crow->i)
					{

						/* находим клетки и вставл€ем - алгоритм списка*/

						Cell* ccell = crow->scell;

						if (j < ccell->j)
						{ 
							crow->scell = new Cell;
							crow->scell->next = ccell;
							crow->scell->j = j;
							crow->scell->data = data;
							break;
						}
						else
						{ 

							while (j >= ccell->j)
							{

								if (j == ccell->j)
								{
									ccell->data = data;
									break;
								}
								else if (ccell->next)
								{

									if (j < ccell->next->j)
									{	/* вставка в начало списка*/
										Cell* oldnext = ccell->next;
										ccell->next = new Cell;
										ccell->next->next = oldnext;
										ccell->next->j = j;
										ccell->next->data = data;
										break;
									}
									else
									{
										ccell = ccell->next;
										continue;
									}

								}
								else
								{	/* вставка в последнюю клетку списка клеток*/
									ccell->next = new Cell;
									ccell->next->next = nullptr;
									ccell->next->j = j;
									ccell->next->data = data;
									break;
								}

							}

						}

					}
					else if (crow->next)
					{	/* вставка списка строк в начало */
						if (i < crow->next->i)
						{
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
						else
						{
							
							crow = crow->next;
							continue; 
						}
					}
					else
					{ /* вставка списка строк в конец */
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
		return EC_GOOD;
	}

	/* ‘ункци€ записи элемента матрицы (записываем по индексам) */
	SparseMatrix* input()
	{
		char Continue;
		int m, n;
		SparseMatrix* mat = new SparseMatrix;

		while (true)
		{
			std::cout << "Enter m: ";
			input_par(m);
			if (m < 1)
			{
				std::cout << "Error, too small m" << std::endl;
				continue;
			}
			else
			{
				mat->m = m;
				break;
			}
		}

		while (true)
		{
			std::cout << "Enter n: ";
			input_par(n);
			if (n < 1)
			{
				std::cout << "Error, too small n" << std::endl;
				continue;
			}
			else
			{
				mat->n = n;
				break;
			}
		}

		int i, j, data;

		while (true)
		{
			std::cout << "Input i, j and data of cell: " << std::endl;
			std::cout << "i: ";
			input_par(i);
			if (i >= mat->m || i < 0)
			{
				std::cout << "Error, i bigger than m or smaller than 0, try again" << std::endl;
				continue;
			}
			std::cout << "j: ";
			input_par(j);
			if (j >= mat->n || j < 0)
			{
				std::cout << "Error, j bigger than n or smaller than 0, try again" << std::endl;
				continue;
			}
			std::cout << "data of cell: ";
			input_par(data);

			if (data != 0)
				set(mat, i, j, data);

			while (true)
			{
				std::cout << "Press ESC to out or press Enter to continue: ";
				Continue = _getch();
				if (Continue == ESC)
				{
					std::cout << "ESC" << std::endl;
					return mat;
				}
				if (Continue == ENTER)
				{
					std::cout << "Continue" << std::endl;
					break;
				}
				std::cout << std::endl;
			}
		}

		return mat;
	}

	/* ‘ункци€ посчета кол-ва цифр в числе (в b записываетс€ количество) */
	static void get_am(int a, int *b)
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

	/* ќбработка первого критери€									*/
	/* »щем среднее количество цифр в числе, потом ищем те числа,	*/
	/* в которых кол-во цифр больше чем среднее						*/
	static void crit_1(int **ln, int len)
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

	/* ќбработка второго критери€				*/
	/* ќставл€ем в матрице числа, кратные двум	*/
	static void crit_2(int **ln, int len)
	{
		int sum = 0;
		for (int i = 0; i < len; i++)
		{
			if ((*ln)[i] % 2 != 0)
			{
				(*ln)[i] = 0;
			}
		}
	}

	/* поиск на наличие элемента в строке */
	static bool is_in(int a, int *ln, int len)
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

	/* обработка матрицы по критерию и создание новой */
	SparseMatrix * by_criterion(SparseMatrix* mat, int tp)
	{
		SparseMatrix* mat_2 = new SparseMatrix;
		mat_2->m = mat->m;
		mat_2->n = mat->n;
		int *line;						// создаем строку на длину строки матрицы
		line = new int[mat->n];
		for (int i = 0; i < mat->n; i++)
			line[i] = 0;				// инициализируем нул€ми 
		int counter = 0;
		Row* crow = mat->srow;			// берем первую строку матрицы 

		Cell* ccell = nullptr;			
		if (crow)
			ccell = crow->scell;		// берем список элементов строки

		while (crow)					// идем по строкам матрицы
		{
			Cell* ccell_2 = ccell;		// "дублируем" список €чеек

			while (ccell)				// идем по €чейкам матрицы
			{
				line[counter] = ccell->data;
				ccell = ccell->next;
				counter++;
			}
			switch (tp)					// обработка критери€ 
			{
			case 1:
				crit_1(&line, mat->n);
				break;
			case 2:
				crit_2(&line, mat->n);
				break;
			default:
				return nullptr;
			}
			
			counter = 0;

			while (ccell_2)			// заполнение второй матрицы 
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

	/* вывод новоой матрицы */
	RC output(SparseMatrix* mat)
	{
		if (!mat)
			return EC_BAD;


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
		return EC_GOOD;
	}

	/* очистка матрицы */
	RC erase(SparseMatrix* mat)
	{
		if (!mat)
			return EC_BAD;


		Row* tmprow;
		while (mat->srow)
		{
			tmprow = mat->srow->next;

			Cell* tmpcell;
			while (mat->srow->scell)
			{
				tmpcell = mat->srow->scell->next;
				delete mat->srow->scell;
				mat->srow->scell = tmpcell;
			}

			delete mat->srow;
			mat->srow = tmprow;
		}
		return EC_GOOD;
	}

}
