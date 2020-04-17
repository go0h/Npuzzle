/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeMove.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 14:16:28 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/17 13:02:34 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.h"
#include "Npuzzle.h"

move_func 		g_move[] = {nullptr, &up, &down, &right, &left};
extern size_t	g_side;

static void swap(CELL & a, CELL & b)
{
	CELL temp = a;
	a = b;
	b = temp;
}

bool up(Node & puzzle)
{
	CELL x = puzzle.zero % g_side;
	CELL y = puzzle.zero / g_side;

	if (y > 0 && puzzle.move != DOWN)
	{
		swap(puzzle(y, x), puzzle(y - 1, x));
		puzzle.zero -= g_side;
		puzzle.move = UP;
		return true;
	}
	return false;
}

bool down(Node & puzzle)
{
	CELL x = puzzle.zero % g_side;
	CELL y = puzzle.zero / g_side;

	if (y < g_side - 1 && puzzle.move != UP)
	{
		swap(puzzle(y, x), puzzle(y + 1, x));
		puzzle.zero += g_side;
		puzzle.move = DOWN;
		return true;
	}
	return false;
}

bool left(Node & puzzle)
{
	CELL x = puzzle.zero % g_side;
	CELL y = puzzle.zero / g_side;

	if (x > 0 && puzzle.move != RIGHT)
	{
		swap(puzzle(y, x), puzzle(y, x - 1));
		puzzle.zero -= 1;
		puzzle.move = LEFT;
		return true;
	}
	return false;
}

bool right(Node & puzzle)
{
	CELL x = puzzle.zero % g_side;
	CELL y = puzzle.zero / g_side;

	if (x < g_side - 1 && puzzle.move != LEFT)
	{
		swap(puzzle(y, x), puzzle(y, x + 1));
		puzzle.zero += 1;
		puzzle.move = RIGHT;
		return true;
	}
	return false;
}

