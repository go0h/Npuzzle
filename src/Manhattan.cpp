/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manhattan.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 13:07:28 by astripeb          #+#    #+#             */
/*   Updated: 2020/05/31 23:06:24 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <cstring>

#include "Heuristic.h"

/*
static void			printField(t_tile * field, size_t side)
{
	for (size_t i = 0; i != side; ++i)
	{
		for (size_t j = 0; j != side; ++j)
			printf("%-3u ", field[i * side + j]);
		printf("\n");
	}
	printf("\n");
}

static t_tile *		Classic(size_t side)
{
	t_tile * field = new t_tile[side * side];

	for (t_tile i = 0; i != (side * side); ++i)
	{
		field[i] = i + 1;
	}
	field[side * side - 1] = 0;
	return field;
}
*/

inline void		Manhattan::initialStates(t_tile * field, unsigned * colf, unsigned * rowf)
{
	unsigned m = 0;
	for (unsigned row = 0; row != side_; ++row)
	{
		for (unsigned col = 0; col != side_; ++col)
		{
			rowf[field[m]] = row;
			colf[field[m]] = col;
			++m;
		}
	}
}

void		Manhattan::init(Node & src, Node & trg)
{
	side_ = src.getSide();
	length_ = side_ * side_;

	target = new t_tile[length_];
	for (size_t row = 0; row != side_; ++row) {
		for (size_t col = 0; col != side_; ++col)
		{
			target[row * side_ + col] = trg(row, col);
		}
	}

	rowCur = new unsigned[length_];
	colCur = new unsigned[length_];
	rowTrg = new unsigned[length_];
	colTrg = new unsigned[length_];

	initialStates(target, colTrg, rowTrg);
}


Manhattan::~Manhattan()
{
	delete [] rowCur;
	delete [] colCur;
	delete [] rowTrg;
	delete [] colTrg;
	delete [] target;
}

unsigned	Manhattan::operator()(Node & src)
{
	src.score = 0;

	initialStates(src.field, colCur, rowCur);
	for (unsigned i = 1; i != length_; ++i)
	{
		src.score += std::abs((int)rowTrg[i] - (int)rowCur[i]);
		src.score += std::abs((int)colTrg[i] - (int)colCur[i]);
	}
	return src.score;
}
