/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeHeuristic.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 13:07:28 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/17 13:06:52 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <cstring>

#include "Npuzzle.h"
#include "PuzzExcept.h"

extern size_t g_length;
extern size_t g_side;

unsigned lastMove(CELL * field)
{
	unsigned score = 0;

	if (field[g_length - 1] != 0)
		return score;

	if (field[g_length - 1] != g_length - 1)
		score += 1;
	if (field[g_length - g_side - 1] != g_length - g_side)
		score += 1;
	return score;
}

// LEFT UP CORNER
#define LU 0

// RIGHT UP CORNER
#define RU (g_side - 1)

// LEFT DOWN CORNER
#define LD (g_side * g_side - g_side)

void		printField(int * field)
{
	for (size_t i = 0; i != g_side; ++i)
	{
		for (size_t j = 0; j != g_side; ++j)
			printf("%-3u ", field[i * g_side + j]);
		printf("\n");
	}
	printf("\n");
}

unsigned	corners(CELL * field)
{
	unsigned score = 0;

	if (field[LU] != 1 && field[LU + 1] == 2)
		score += 1;
	if (field[LU] != 1 && field[g_side] == g_side + 1)
		score += 1;
	if (field[RU] != g_side && field[RU - 1] == g_side - 1)
		score += 1;
	if (field[RU] != g_side && field[g_side * 2 - 1] == g_side * 2)
		score += 1;
	if (field[LD] != LD + 1 && field[LD + 1] == g_side * g_side - g_side + 2)
		score += 1;
	return score;
}

unsigned	rowConflict(CELL * field)
{
	unsigned score = 0;

	for (size_t i = 0; i != g_side; ++i)
	{
		for (size_t j = 0; j != g_side - 1; ++j)
		{
			unsigned a = i * g_side + j;
			if (field[a] && field[a] != a + 1  && (field[a] - 1) / g_side == i)
			{
				for (size_t k = j + 1; k != g_side; ++k)
				{
					unsigned b = i * g_side + k;
					if (field[b] != b + 1  && (field[b] - 1) / g_side == i)
						score += b - a;
				}
			}
		}
	}
	return score;
}

unsigned	colConflict(CELL * field)
{
	unsigned score = 0;

	for (size_t i = 0; i != g_side; ++i)
	{
		for (size_t j = 0; j != g_side - 1; ++j)
		{
			unsigned a = j * g_side + i;
			if (field[a] && field[a] != a + 1 && (field[a] - 1) % g_side == i)
			{
				for (size_t k = j + 1; k != g_side; ++k)
				{
					unsigned b = j * g_side + k;
					if (field[b] != b + 1 && (field[b] - 1) % g_side == i)
						score += b - a;
				}
			}
		}
	}
	return score;
}

unsigned	linearConflict(CELL * field, int * rowCon, int * colCon, int * line)
{
	unsigned score = 0, lineScore, count;

	for (size_t i = 0; i != g_side; ++i)
	{
		// для каждого ряда записываем числа которые стоят в своем ряду
		// и запоминаем их количество
		count = 0;
		for (size_t j = 0; j != g_side; ++j)
		{
			unsigned pos = i * g_side + j;
			if (field[pos] && rowCon[field[pos]] == (int)i)
			{
				line[count] = field[pos];
				count++;
			}
		}

		lineScore = 0;
		for (size_t j = 0; j < count; ++j)
		{
			for (size_t k = j + 1; k < count; ++k)
			{
				if (colCon[line[j]] > colCon[line[k]])
					lineScore += 1;
			}
		}
		score += lineScore + (lineScore % 2);
	}

	for (size_t i = 0; i != g_side; ++i)
	{
		// для каждой колонки записываем числа которые стоят в своем ряду
		// и запоминаем их количество
		count = 0;
		for (size_t j = 0; j != g_side; ++j)
		{
			unsigned pos = j * g_side + i;
			if (field[pos] && colCon[field[pos]] == (int)i)
			{
				line[count] = field[pos];
				count++;
			}
		}

		lineScore = 0;
		for (size_t j = 0; j < count; ++j)
		{
			for (size_t k = j + 1; k < count; ++k)
			{
				if (rowCon[line[j]] > rowCon[line[k]])
					lineScore += 1;
			}
		}
		score += lineScore + (lineScore % 2);
	}
	return score;
}

void		initialStates(CELL * field, int * colCon, int * rowCon)
{
	for (size_t i = 0; i != g_length; ++i)
	{
		if (field[i])
		{
			rowCon[i] = (field[i] - 1) / g_side;
			colCon[i] = (field[i] - 1) % g_side;
		}
		else
		{
			rowCon[i] = field[i];
			colCon[i] = field[i];
		}
	}
}

void		countRowConflict(CELL * field, int row,
			int * rowCon, int * colCon, int * line)
{
	unsigned a, b;

	std::memset(line, 0, sizeof(int) * g_side);
	for (size_t j = 0; j != g_side; ++j)
	{
		// determie number of tiles in row i,
		// with which field[i, j] is conflict
		a = row * g_side + j;
		if (rowCon[a] == row && field[a])
		{
			for (size_t k = 0; k < g_side; ++k)
			{
				b = row * g_side + k;
				if (rowCon[b] == row && field[b] && k != j)
				{
					if (colCon[a] < colCon[b] && j > k)
						line[j] += 1;
					else if (colCon[a] > colCon[b] && j < k)
						line[j] += 1;
				}
			}
		}
	}
}

void		countColConflict(CELL * field, int col,
			int * rowCon, int * colCon, int * line)
{
	unsigned a, b;

	std::memset(line, 0, sizeof(int) * g_side);
	for (size_t j = 0; j != g_side; ++j)
	{
		// determie number of tiles in row i,
		// with which field[i, j] is conflict
		a = g_side * j + col;
		if (colCon[a] == col && field[a])
		{
			for (size_t k = 0; k < g_side; ++k)
			{
				b = g_side * k + col;
				if (colCon[b] == col && field[b] && k != j)
				{
					if (rowCon[a] < rowCon[b] && j > k)
						line[j] += 1;
					else if (rowCon[a] > rowCon[b] && j < k)
						line[j] += 1;
				}
			}
		}
	}
}

size_t		find_max(int * line)
{
	size_t max = 0;

	for (size_t i = 0; i != g_side; ++i)
	{
		if (line[i] > line[max])
			max = i;
	}
	return max;
}

unsigned 	linearConflict2(CELL * field, int * rowCon, int * colCon, int * line)
{
	unsigned	score = 0;
	int			a, b;
	size_t		max;


	// for each row in state
	for (size_t i = 0; i != g_side; ++i)
	{
		countRowConflict(field, i, rowCon, colCon, line);
		max = find_max(line);
		while (line[max])
		{
			line[max] = 0;
			score += 1;
			a = i * g_side + max;
			for (size_t j = 0; j != g_side; ++j)
			{
				b = i * g_side + j;
				if (colCon[a] < colCon[b] && j > max)
					line[j] -= 1;
				else if (colCon[a] > colCon[b] && j < max)
					line[j] -= 1;
			}
			max = find_max(line);
		}
	}

	// for each column in state
	for (size_t i = 0; i != g_side; ++i)
	{
		countColConflict(field, i, rowCon, colCon, line);
		max = find_max(line);
		while (line[max])
		{
			score += 1;
			line[max] = 0;
			a = g_side * max + i;
			for (size_t j = 0; j != g_side; ++j)
			{
				b = g_side * j + i;
				if (colCon[a] < colCon[b] && j > max)
					line[j] -= 1;
				else if (colCon[a] > colCon[b] && j < max)
					line[j] -= 1;
			}
			max = find_max(line);
		}
	}
	return score;
}

unsigned 	Node::getScore(bool again)
{
	if (again)
	{
		score 		= 0;
		// int * 		rowCon = new int[g_length];	// номер ряда в котором должна быть ячейка
		// int * 		colCon = new int[g_length];	// номер колонки в которой должна быть ячейка
		// int * 		line = new int[g_side];		// количество конфликтов в ряду/колонке

		int  rowCon[g_length];	// номер ряда в котором должна быть ячейка
		int  colCon[g_length];	// номер колонки в которой должна быть ячейка
		int  line[g_side];

		initialStates(field, colCon, rowCon);
		for (size_t i = 0; i != g_length; ++i)
		{
			if (field[i])
			{
				score += std::abs((int)(i / g_side) - rowCon[i]);
				score += std::abs((int)(i % g_side) - colCon[i]);
			}
		}
		score += 2 * linearConflict2(field, rowCon, colCon, line);
		score += corners(field);
		if (score)
			score += lastMove(field);
	}
	return score;
}
