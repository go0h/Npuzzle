/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeMove.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 14:16:28 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/03 20:28:11 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.h"
#include <iostream>

static void swap(CELL & a, CELL & b)
{
	CELL temp = a;
	a = b;
	b = temp;
}

bool up(Node & puzzle)
{
	CELL x = puzzle.zero % puzzle.side;
	CELL y = puzzle.zero / puzzle.side;

	if (y > 0)
	{
		swap(puzzle(y, x), puzzle(y - 1, x));
		puzzle.zero -= puzzle.side;
		return true;
	}
	return false;
}

bool down(Node & puzzle)
{
	CELL x = puzzle.zero % puzzle.side;
	CELL y = puzzle.zero / puzzle.side;

	if (y < puzzle.side - 1)
	{
		swap(puzzle(y, x), puzzle(y + 1, x));
		puzzle.zero += puzzle.side;
		return true;
	}
	return false;
}

bool left(Node & puzzle)
{
	CELL x = puzzle.zero % puzzle.side;
	CELL y = puzzle.zero / puzzle.side;

	if (x > 0)
	{
		swap(puzzle(y, x), puzzle(y, x - 1));
		puzzle.zero -= 1;
		return true;
	}
	return false;
}

bool right(Node & puzzle)
{
	CELL x = puzzle.zero % puzzle.side;
	CELL y = puzzle.zero / puzzle.side;

	if (x < puzzle.side - 1)
	{
		swap(puzzle(y, x), puzzle(y, x + 1));
		puzzle.zero += 1;
		return true;
	}
	return false;
}

