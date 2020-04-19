/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LinearConflict.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 14:25:00 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/19 19:40:26 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Heuristic.h"
#include <cstring>

void	LinearConflict::init(Node & src, Node & trg)
{
	Manhattan::init(src, trg);
	line = new int[side_];
}

LinearConflict::~LinearConflict()
{
	delete [] line;
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

void		LinearConflict::countRowConflict(CELL * field, int row)
{
	unsigned a, b;

	std::memset(line, 0, sizeof(int) * side_);
	for (size_t j = 0; j != side_; ++j)
	{
		// determie number of tiles in row i,
		// with which field[i, j] is conflict
		a = field[row * side_ + j];
		if (rowTrg[a] == row && a)
		{
			for (size_t k = 0; k < side_; ++k)
			{
				b = field[row * side_ + k];
				if (rowTrg[b] == row && b && k != j)
				{
					if (colTrg[a] < colTrg[b] && j > k)
						line[j] += 1;
					else if (colTrg[a] > colTrg[b] && j < k)
						line[j] += 1;
				}
			}
		}
	}
}

void		LinearConflict::countColConflict(CELL * field, int col)
{
	unsigned a, b;

	std::memset(line, 0, sizeof(int) * side_);
	for (size_t j = 0; j != side_; ++j)
	{
		// determie number of tiles in row i,
		// with which field[i, j] is conflict
		a = field[side_ * j + col];
		if (colTrg[a] == col && a)
		{
			for (size_t k = 0; k < side_; ++k)
			{
				b = field[side_ * k + col];
				if (colTrg[b] == col && b && k != j)
				{
					if (rowTrg[a] < rowTrg[b] && j > k)
						line[j] += 1;
					else if (rowTrg[a] > rowTrg[b] && j < k)
						line[j] += 1;
				}
			}
		}
	}
}

unsigned	LinearConflict::operator()(Node & src)
{
	unsigned	score = Manhattan::operator()(src);
	int			a, b;
	size_t		max;

	// for each row in state
	for (size_t i = 0; i != side_; ++i)
	{
		countRowConflict(src.field, i);
		max = find_max(line, side_);
		while (line[max])
		{
			line[max] = 0;
			score += 2;
			a = src.field[i * side_ + max];
			for (size_t j = 0; j != side_; ++j)
			{
				b = src.field[i * side_ + j];
				if (colTrg[a] < colTrg[b] && j > max)
					line[j] -= 1;
				else if (colTrg[a] > colTrg[b] && j < max)
					line[j] -= 1;
			}
			max = find_max(line, side_);
		}
	}

	// for each column in state
	for (size_t i = 0; i != side_; ++i)
	{
		countColConflict(src.field, i);
		max = find_max(line, side_);
		while (line[max])
		{
			score += 2;
			line[max] = 0;
			a = src.field[side_ * max + i];
			for (size_t j = 0; j != side_; ++j)
			{
				b = src.field[side_ * j + i];
				if (rowTrg[a] < rowTrg[b] && j > max)
					line[j] -= 1;
				else if (rowTrg[a] > rowTrg[b] && j < max)
					line[j] -= 1;
			}
			max = find_max(line, side_);
		}
	}

	src.score = score;
	return score;
}
