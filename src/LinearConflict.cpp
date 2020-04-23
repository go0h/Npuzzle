/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LinearConflict.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 14:25:00 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/23 20:28:09 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Heuristic.h"
#include <cstring>

void	LinearConflict::init(Node & src, Node & trg)
{
	Manhattan::init(src, trg);
	line_ = new unsigned[side_];
}

LinearConflict::~LinearConflict()
{
	delete [] line_;
}

inline size_t		find_max(unsigned * line, size_t & side)
{
	size_t max = 0;

	for (size_t i = 0; i != side; ++i)
	{
		if (line[i] > line[max])
			max = i;
	}
	return max;
}

unsigned		LinearConflict::rowConflicts(t_tile * field)
{
	unsigned	a, b;
	unsigned	score = 0;

	// for each row in state
	for (size_t row = 0; row != side_; ++row)
	{
		std::memset(line_, 0, sizeof(unsigned) * side_);
		for (size_t j = 0; j != side_ - 1; ++j)
		{
			// determie number of t_tiles in row i,
			// with which field[i, j] is conflict
			a = field[row * side_ + j];
			if ( !(rowTrg[a] - row) && a)
			{
				for (size_t k = j + 1; k != side_; ++k)
				{
					b = field[row * side_ + k];
					if (b && !(rowTrg[b] - row) && colTrg[a] > colTrg[b])
					{
						line_[j] += 1;
						line_[k] += 1;
					}
				}
			}
		}
		a = find_max(line_, side_);
		score = score + line_[a] + (line_[a] & 1);
	}
	return score;
}

unsigned		LinearConflict::colConflicts(t_tile * field)
{
	unsigned	a, b;
	unsigned	score = 0;
	// for each column in state
	for (size_t col = 0; col != side_; ++col)
	{
		std::memset(line_, 0, sizeof(unsigned) * side_);
		for (size_t j = 0; j != side_ - 1; ++j)
		{
			// determie number of t_tiles in row i,
			// with which field[i, j] is conflict
			a = field[side_ * j + col];
			if ( !(colTrg[a] - col) && a) // colTrg[a] == col
			{
				for (size_t k = j + 1; k != side_; ++k)
				{
					b = field[side_ * k + col];
					if (b && !(colTrg[b] - col) && rowTrg[a] > rowTrg[b])
					{
						line_[j] += 1;
						line_[k] += 1;
					}
				}
			}
		}
		a = find_max(line_, side_);
		score = score + line_[a] + (line_[a] & 1); //n  & (d - 1)
	}
	return score;
}

unsigned	LinearConflict::operator()(Node & src)
{
	unsigned	score = Manhattan::operator()(src);
	score += (2 * rowConflicts(src.field));
	score += (2 * colConflicts(src.field));
	src.score = score;
	return score;
}
