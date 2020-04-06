/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeHeuristic.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 13:07:28 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/06 08:47:02 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>

#include "Node.h"
#include "PuzzExcept.h"

extern size_t g_length;
extern size_t g_side;

size_t corners(CELL * field)
{
	size_t score = 0;

	if (field[0] == 1 && (field[1] != 2 || field[g_side] != g_side + 1))
		score += 2;
	return score;
}

size_t Node::getScore(void) const
{
	size_t score = 0;

	for (size_t i = 0; i != g_side; ++i)
	{
		for (size_t j = 0; j != g_side; ++j)
		{
			CELL num = (*this)(i, j) - 1;
			if (!(num + 1) || (num / g_side == i && num % g_side == j))
				continue;
			int dy = num / g_side - i;
			int dx = num % g_side - j;
			score += std::abs(dx) + std::abs(dy);
		}
	}
//	score += (3 * corners(field));
	return score;
}
