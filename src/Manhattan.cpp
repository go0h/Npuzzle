/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manhattan.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 13:07:28 by astripeb          #+#    #+#             */
/*   Updated: 2020/06/02 10:54:54 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <cstring>

#include "Heuristic.h"
#include "PuzzExcept.h"

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

/*
**	Generate snail board state. Example for side == 3:
**		1 2 3
**		8 0	4
**		7 6 5
**
**	top left -> top right
**	top right -> bottom right
**	bottom right -> bottom left
**	bottom left -> top left
*/

static t_tile *	snail(t_tile * field, int side)
{
	int i = 0;
	int col, row;
	int count = 1;

	while (i < side / 2)
	{
		for (col = i, row = i; col < side - i; ++col)
			field[row * side + col] = count++ % (side * side);
		for (row = row + 1, col = col - 1; row < side - i; ++row)
			field[row * side + col]  = count++ % (side * side);
		for (col = col - 1, row = row - 1; col >= i; --col)
			field[row * side + col] = count++ % (side * side);
		for (row = row - 1, col = col + 1; row > i; --row)
			field[row * side + col] = count++ % (side * side);
		++i;
	}
	return field;
}

/*
static void		printField(size_t * field, size_t side)
{
	for (size_t i = 0; i != side; ++i)
	{
		for (size_t j = 0; j != side; ++j)
			printf("%-3lu ", field[i * side + j]);
		printf("\n");
	}
	printf("\n");
}
*/

static bool 	solvable(Node & src, t_tile * trg, size_t side)
{
	size_t length = side * side;
	size_t inversion = 0;
	size_t zero = 0;
	size_t * field = new size_t[length];

	for (size_t i = 0; i != length; ++i)
		field[trg[i]] = i;

	// printField(field, side);
	for (size_t i = 0; i != length - 1; ++i)
	{
		if (src.field[i] == 0)
			zero = i;
		for (size_t j = i + 1; j != length; ++j)
		{
			if (src.field[i] && src.field[j])
			{
				if (field[src.field[i]] > field[src.field[j]])
					++inversion;
			}
		}
	}
	delete [] field;
	zero = (length - zero - 1) / side + ((side / 2) & 1);
	if (side & 1)
		return !(inversion & 1);
	else
		return (zero & 1) ^ (inversion & 1);
	return false;
}

void			Manhattan::initialStates(t_tile * field, unsigned * colf,
				unsigned * rowf)
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

void			Manhattan::init(Node & src, Node & trg)
{
	side_ = src.getSide();
	length_ = side_ * side_;
	target = new t_tile[length_];
	memset(target, 0, sizeof(t_tile) * length_);

	if (trg)
	{
		for (size_t i = 0; i != length_; ++i)
			target[i] = trg(i / side_, i % side_);
	}
	else
		target = snail(target, side_);

	if (!solvable(src, target, side_))
		throw PuzzExcept(E_UNSOLVBL);

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

unsigned		Manhattan::operator()(Node & src)
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
