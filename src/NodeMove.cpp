/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeMove.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 14:16:28 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/23 21:39:46 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.h"

static void swap(t_tile & a, t_tile & b)
{
	t_tile temp = a;
	a = b;
	b = temp;
}

bool up(Node & puzzle)
{
	t_tile x = puzzle.zero % Node::side_;
	t_tile y = puzzle.zero / Node::side_;

	if (y > 0 && puzzle.move != DOWN)
	{
		swap(puzzle(y, x), puzzle(y - 1, x));
		puzzle.zero -= Node::side_;
		puzzle.move = UP;
		return true;
	}
	return false;
}

bool down(Node & puzzle)
{
	t_tile x = puzzle.zero % Node::side_;
	t_tile y = puzzle.zero / Node::side_;

	if (y < Node::side_ - 1 && puzzle.move != UP)
	{
		swap(puzzle(y, x), puzzle(y + 1, x));
		puzzle.zero += Node::side_;
		puzzle.move = DOWN;
		return true;
	}
	return false;
}

bool left(Node & puzzle)
{
	t_tile x = puzzle.zero % Node::side_;
	t_tile y = puzzle.zero / Node::side_;

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
	t_tile x = puzzle.zero % Node::side_;
	t_tile y = puzzle.zero / Node::side_;

	if (x < Node::side_ - 1 && puzzle.move != LEFT)
	{
		swap(puzzle(y, x), puzzle(y, x + 1));
		puzzle.zero += 1;
		puzzle.move = RIGHT;
		return true;
	}
	return false;
}

move_func 		g_move[] = {nullptr, &up, &down, &right, &left};
