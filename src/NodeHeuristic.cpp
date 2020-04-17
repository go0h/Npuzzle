/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeHeuristic.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 13:07:28 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/17 20:11:00 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <cstring>

#include "Npuzzle.h"
#include "PuzzExcept.h"

size_t g_side = DEFAULT_SIZE;

unsigned lastMove(CELL * field, size_t side, size_t length)
{
	unsigned score = 0;

	if (field[length - 1] != 0)
		return score;

	if (field[length - 1] != length - 1)
		score += 1;
	if (field[length - side - 1] != length - side)
		score += 1;
	return score;
}

// LEFT UP CORNER
#define LU 0

// RIGHT UP CORNER
#define RU (side - 1)

// LEFT DOWN CORNER
#define LD (side * side - side)

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

void		initialStates(CELL * field, int * colCon, int * rowCon, size_t length)
{
	for (size_t i = 0; i != length; ++i)
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

unsigned	corners(CELL * field, size_t side)
{
	unsigned score = 0;

	if (field[LU] != 1 && field[LU + 1] == 2)
		score += 1;
	if (field[LU] != 1 && field[side] == side + 1)
		score += 1;
	if (field[RU] != side && field[RU - 1] == side - 1)
		score += 1;
	if (field[RU] != side && field[side * 2 - 1] == side * 2)
		score += 1;
	if (field[LD] != LD + 1 && field[LD + 1] == side * side - side + 2)
		score += 1;
	return score;
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

size_t		find_max(int * line, size_t side)
{
	size_t max = 0;

	for (size_t i = 0; i != side; ++i)
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
		max = find_max(line, g_side);
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
			max = find_max(line, g_side);
		}
	}

	// for each column in state
	for (size_t i = 0; i != g_side; ++i)
	{
		countColConflict(field, i, rowCon, colCon, line);
		max = find_max(line, g_side);
		while (line[max])
		{
			score += 1;
			line[max] = 0;
			a = g_side * max + i;
			for (size_t j = 0; j != g_side; ++j)
			{
				b = g_side * j + i;
				if (rowCon[a] < rowCon[b] && j > max)
					line[j] -= 1;
				else if (rowCon[a] > rowCon[b] && j < max)
					line[j] -= 1;
			}
			max = find_max(line, g_side);
		}
	}
	return score;
}

unsigned 	Node::getScore(bool again)
{
	if (again)
	{
		score = 0;
		static int *	rowCon = new int[length_];	// номер ряда в котором должна быть ячейка
		static int *	colCon = new int[length_];	// номер колонки в которой должна быть ячейка
		static int *	line = new int[side_];		// количество конфликтов в ряду/колонке

		initialStates(field, colCon, rowCon, length_);
		for (size_t i = 0; i != length_; ++i)
		{
			if (field[i])
			{
				score += std::abs((int)(i / side_) - rowCon[i]);
				score += std::abs((int)(i % side_) - colCon[i]);
			}
		}
		score += 2 * linearConflict2(field, rowCon, colCon, line);
		score += corners(field, side_);
		if (score)
			score += lastMove(field, side_, length_);
	}
	return score;
}
