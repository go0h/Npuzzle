/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeHeuristic.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 13:07:28 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/08 10:55:12 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>

#include "Node.h"
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

unsigned corners(CELL * field)
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

unsigned rowConflict(CELL * field)
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

unsigned colConflict(CELL * field)
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

unsigned Node::getScore(bool again = false)
{
	if (again)
	{
		CELL num	= 0;
		score 		= 0;
		for (size_t i = 0; i != g_length; ++i)
		{
			if (!field[i])
				continue;
			num = field[i] - 1;
			score += std::abs((int)(i / g_side) - (int)(num / g_side));
			score += std::abs((int)(i % g_side) - (int)(num % g_side));
		}
		score += rowConflict(field);
		score += colConflict(field);
		score += corners(field);
		if (score)
			score += lastMove(field);
	}
	return score;
}
