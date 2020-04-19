/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptimalH.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 20:45:00 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/19 19:40:42 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Heuristic.h"

#define TOP_LEFT 0
#define TOP_RIGHT (side_ - 1)
#define BOTTOM_LEFT (length_ - side_)
#define BOTTOM_RIGHT (length_ - 1)

void 		OptimalH::init(Node & src, Node & trg)
{
	LinearConflict::init(src, trg);
}

unsigned	OptimalH::operator()(Node & src)
{
	CELL * field = src.field;
	unsigned score = LinearConflict::operator()(src);

	// CORNERS
	if (field[TOP_LEFT] != target[TOP_LEFT])
	{
		if (field[TOP_LEFT + 1] == target[TOP_LEFT + 1])
			score += 2;
		if (field[TOP_LEFT + side_] == target[TOP_LEFT + side_])
			score += 2;
	}
	if (field[TOP_RIGHT] != target[TOP_RIGHT])
	{
		if (field[TOP_RIGHT - 1] == target[TOP_RIGHT - 1])
			score += 2;
		if (field[TOP_RIGHT + side_] == target[TOP_RIGHT + side_])
			score += 2;
	}
	if (field[BOTTOM_LEFT] != target[BOTTOM_LEFT])
	{
		if (field[BOTTOM_LEFT + 1] == target[BOTTOM_LEFT + 1])
			score += 2;
		if (field[BOTTOM_LEFT - side_] == target[BOTTOM_LEFT - side_])
			score += 2;
	}

	// LAST_MOVE
	if (score && target[BOTTOM_RIGHT] == 0)
	{
		if (field[BOTTOM_RIGHT] != target[BOTTOM_RIGHT - 1])
			score += 2;
		if (field[BOTTOM_RIGHT] != target[BOTTOM_RIGHT - side_])
			score += 2;
	}
	src.score = score;
	return score;
}
