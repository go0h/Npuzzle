/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeHeuristic.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 13:07:28 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/03 17:56:58 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>

#include "Node.h"
#include "PuzzExcept.h"

CELL manhattanScore(Node const & src)
{
	CELL score = 0;

	for (size_t i = 0; i != src.side; ++i) {
		for (size_t j = 0; j != src.side; ++j) {
			CELL num = src(i, j) - 1;
			if (!(num + 1) || (num / src.side == i && num % src.side == j))
				continue;
			int dy = num / src.side - i;
			int dx = num % src.side - j;
			score += std::abs(dx) + std::abs(dy);
		}
	}
	return score;
}
