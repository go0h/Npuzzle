/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALL_HEURISTIC.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 13:07:28 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/22 17:22:40 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <cstring>

#include "Heuristic.h"
#include "PuzzExcept.h"

void		printField(int * field, size_t side)
{
	for (size_t i = 0; i != side; ++i)
	{
		for (size_t j = 0; j != side; ++j)
			printf("%-3u ", field[i * side + j]);
		printf("\n");
	}
	printf("\n");
}

unsigned lastMove(t_tile * field, size_t g_side, size_t g_length)
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


unsigned	corners(t_tile * field, size_t g_side)
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

unsigned	rowConflict(t_tile * field, size_t g_side)
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

unsigned	colConflict(t_tile * field, size_t g_side)
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

unsigned	linearConflict(t_tile * field, int * rowCon, int * colCon, int * line, size_t g_side)
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

void		countRowConflict(t_tile * field, int row,
			int * rowCon, int * colCon, int * line, size_t g_side)
{
	unsigned a, b;

	std::memset(line, 0, sizeof(int) * g_side);
	for (size_t j = 0; j != g_side; ++j)
	{
		// determie number of t_tiles in row i,
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

void		countColConflict(t_tile * field, int col,
			int * rowCon, int * colCon, int * line, size_t g_side)
{
	unsigned a, b;

	std::memset(line, 0, sizeof(int) * g_side);
	for (size_t j = 0; j != g_side; ++j)
	{
		// determie number of t_tiles in row i,
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

size_t		find_max(int * line, size_t & side)
{
	size_t max = 0;

	for (size_t i = 0; i != side; ++i)
	{
		if (line[i] > line[max])
			max = i;
	}
	return max;
}

unsigned 	Manhattan::linearConflict2(t_tile * field)
{
	unsigned	score = 0;
	int			a, b;
	size_t		max;


	// for each row in state
	for (size_t i = 0; i != g_side; ++i)
	{
		countRowConflict(field, i, rowCur, colCur, line, g_side);
		max = find_max(line, g_side);
		while (line[max])
		{
			line[max] = 0;
			score += 1;
			a = i * g_side + max;
			for (size_t j = 0; j != g_side; ++j)
			{
				b = i * g_side + j;
				if (colCur[a] < colCur[b] && j > max)
					line[j] -= 1;
				else if (colCur[a] > colCur[b] && j < max)
					line[j] -= 1;
			}
			max = find_max(line, g_side);
		}
	}

	// for each column in state
	for (size_t i = 0; i != g_side; ++i)
	{
		countColConflict(field, i, rowCur, colCur, line, g_side);
		max = find_max(line, g_side);
		while (line[max])
		{
			score += 1;
			line[max] = 0;
			a = g_side * max + i;
			for (size_t j = 0; j != g_side; ++j)
			{
				b = g_side * j + i;
				if (colCur[a] < colCur[b] && j > max)
					line[j] -= 1;
				else if (colCur[a] > colCur[b] && j < max)
					line[j] -= 1;
			}
			max = find_max(line, g_side);
		}
	}
	return score;
}

unsigned	Manhattan::operator()(Node & src)
{
	size_t score = 0;

	initialStates(src.field, colCur, rowCur);
	for (size_t i = 0; i != length_; ++i)
	{
		score += std::abs(rowTrg[i] - rowCur[i]);
		score += std::abs(colTrg[i] - colCur[i]);
	}
	score += 2 * linearConflict2(src.field);
	score += corners(src.field, side_);
	if (score)
		score += lastMove(src.field, side_, length_);
	src.score = score;
	return score;
}
