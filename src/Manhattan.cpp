/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manhattan.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 13:07:28 by astripeb          #+#    #+#             */
/*   Updated: 2020/06/02 14:04:59 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <cstring>
#include <vector>
#include <random>

#include "Heuristic.h"
#include "PuzzExcept.h"

extern move_func	g_move[];

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

static Node		snail(int side)
{
	int i = 0;
	int col, row;
	int count = 1;
	Node board(side);

	while (i < side / 2)
	{
		for (col = i, row = i; col < side - i; ++col)
			board(row, col) = count++ % (side * side);
		for (row = row + 1, col = col - 1; row < side - i; ++row)
			board(row, col)  = count++ % (side * side);
		for (col = col - 1, row = row - 1; col >= i; --col)
			board(row, col) = count++ % (side * side);
		for (row = row - 1, col = col + 1; row > i; --row)
			board(row, col) = count++ % (side * side);
		++i;
	}
	board.setZero();
	return board;
}

Node		createRandomNode(Node randomNode)
{
	int side = (int) Node::getSide();
	std::random_device rd;
	std::uniform_int_distribution<int> dist(1, 4);
	std::vector<t_move> positions = std::vector<t_move>();

	for (size_t i = 0; i < 10000; ++i)
	{
		int pos = (int) randomNode.getZero();
		if (pos / side > 0)
			positions.push_back(UP);
		if (pos / side < side - 1)
			positions.push_back(DOWN);
		if (pos % side > 0)
			positions.push_back(LEFT);
		if (pos % side < side - 1)
			positions.push_back(RIGHT);
		g_move[dist(rd)](randomNode);
		positions.clear();
	}
	randomNode.getMove() = NONE;
	return randomNode;
}

static bool 	calcInversion(const t_tile * field, size_t side)
{
	size_t inversion = 0;
	size_t length = side * side;
	size_t zero = 0;

	for (size_t i = 0; i < length - 1; ++i)
	{
		if (field[i] == 0)
			zero = i;
		for (size_t j = i + 1; j < length - 1; ++j)
		{
			if (field[i] > field[j])
				++inversion;
		}
	}
	zero = (length - zero - 1) / side + ((side / 2) & 1U);
	if (side & 1U)
		return !(inversion & 1U);
	else
		return (zero & 1U) ^ (inversion & 1U);
}

/*
**	SOLVABLE
**	Checks if it possible solve the puzzle
**	from source board state to target
**
**	Move blank tile to bottom right corner, and check
**	number of inversions in source and target board state
**
*/

static bool		solvable(Node src, Node trg)
{
	while (down(src) || right(src)) ;
	while (down(trg) || right(trg)) ;

	bool inv1 = calcInversion(src.getField(), Node::getSide());
	bool inv2 = calcInversion(trg.getField(), Node::getSide());
	return  inv1 == inv2;
}

void			Manhattan::initialStates(t_tile * field, unsigned * columnFields,
				unsigned * rowFields)
{
	unsigned m = 0;
	for (unsigned row = 0; row != side_; ++row)
	{
		for (unsigned col = 0; col != side_; ++col)
		{
			rowFields[field[m]] = row;
			columnFields[field[m]] = col;
			++m;
		}
	}
}

void			Manhattan::init(Node & src, Node & trg)
{
	side_ = Node::getSide() == 0 ? 4 : Node::getSide();
	length_ = side_ * side_;
	target = new t_tile[length_];
	memset(target, 0, sizeof(t_tile) * length_);

	if (!trg)
		trg = snail(side_);
	if (!src)
		src = createRandomNode(trg);

	if (!solvable(src, trg))
		throw PuzzExcept(E_UNSOLVBL);

	for (size_t i = 0; i != length_; ++i)
		target[i] = trg(i / side_, i % side_);

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
