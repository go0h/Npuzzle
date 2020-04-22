/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manhattan.cpp                                      :+:      :+:    :+:   */
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

void		printField(t_tile * field, size_t side)
{
	for (size_t i = 0; i != side; ++i)
	{
		for (size_t j = 0; j != side; ++j)
			printf("%-3u ", field[i * side + j]);
		printf("\n");
	}
	printf("\n");
}

t_tile * 		Classic(size_t side)
{
	t_tile * field = new t_tile[side * side];

	for (t_tile i = 0; i != (side * side); ++i)
	{
		field[i] = i + 1;
	}
	field[side * side - 1] = 0;
	return field;
}

t_tile *		Snail(int side)
{
	t_tile * field = new t_tile[side * side];
	int i = 0;
	int col, row;
	int count = 1;

	while (i < side / 2)
	{
		// left -> right
		for (col = i, row = i; col < side - i; ++col)
			field[row * side + col] = count++ % (side * side);

		// top -> bottom
		for (row = row + 1, col = col - 1; row < side - i; ++row)
			field[row * side + col] = count++ % (side * side);

		// right -> left
		for (col = col - 1, row = row - 1; col >= i; --col)
			field[row * side + col] = count++ % (side * side);

		// bottom -> top
		for (row = row - 1, col = col + 1; row > i; --row)
			field[row * side + col] = count++ % (side * side);
		++i;
	}
	return field;
}

void		Manhattan::initialStates(t_tile * field, int * colf, int * rowf)
{
/*
	for (size_t i = 0; i != length_; ++i)
	{
		if (field[i])
		{
			row[i] = (field[i] - 1) / side_;
			col[i] = (field[i] - 1) % side_;
		}
		else
		{
			row[i] = 0;
			col[i] = 0;
		}
	}
*/
	t_tile m = 0;
	for (size_t row = 0; row < side_; ++row)
	{
		for (size_t col = 0; col < side_; ++col)
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

	if (trg)
	{
		target = new t_tile[length_];
		std::memcpy(target, trg.field, sizeof(t_tile) * length_);
	}
	else
		target = Snail(side_);

	rowCur = new int[length_];
	colCur = new int[length_];
	rowTrg = new int[length_];
	colTrg = new int[length_];

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
	for (size_t i = 1; i != length_; ++i)
	{
		src.score += std::abs(rowTrg[i] - rowCur[i]);
		src.score += std::abs(colTrg[i] - colCur[i]);
	}
	return src.score;
}
