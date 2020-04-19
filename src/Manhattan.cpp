/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manhattan.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 13:07:28 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/19 19:39:57 by astripeb         ###   ########.fr       */
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

CELL * 		genSample(size_t side)
{
	CELL * field = new CELL[side * side];

	for (CELL i = 0; i != (side * side); ++i)
	{
		field[i] = i + 1;
	}
	field[side * side - 1] = 0;
	return field;
}

void		Manhattan::initialStates(CELL * field, int * colf, int * rowf)
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
	CELL m = 0;
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
		target = new CELL[length_];
		std::memcpy(target, trg.field, sizeof(CELL) * length_);
	}
	else
		target = genSample(side_);

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
