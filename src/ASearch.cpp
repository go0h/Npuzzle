/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASearch.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 17:46:34 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/08 09:58:23 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Npuzzle.h"

extern size_t			g_length;
extern size_t			g_side;
extern move_func		g_move[];

#define STATE			first
#define DEPTH			second

static void undo(Node & node, size_t i)
{
	node.move = NONE;
	if (i % 2 == 0)
		g_move[i - 1](node);
	else
		g_move[i + 1](node);
}

static solution GenerateMoves(Node target, HashTable & close)
{
	solution	moves;

	printf("States in close: %lu\n", close.size());
	target.printNode();
	moves.push_front(target.move);
	while (target.move != NONE)
	{
		undo(target, target.move);
		target = *(close.find(target));
		moves.push_front(target.move);
	}
	return moves;
}

solution Search(Node & src)
{
	HashTable		close;
	PriorityQueue	open;
	Desk			desk;
	unsigned		depth = 0;

	if (!src.getScore(true))
		return solution();

	open.insert(std::make_pair(src, 0));
	close.insert(src);

	while (!open.empty())
	{
		desk = *(open.begin());
		open.erase(desk.STATE);
		depth = desk.DEPTH + 1;

		close.insert(desk.STATE);
		for (size_t i = UP; i <= LEFT; ++i)
		{
			if (g_move[i](desk.STATE))
			{
				if (!desk.STATE.getScore(true))
					return GenerateMoves(desk.STATE, close);
				auto closeIt = close.find(desk.STATE);
				if (closeIt == close.end())
				{
					auto openIt = open.find(desk.STATE);
					if (openIt == open.end() || depth < openIt->DEPTH)
					{
						if (openIt != open.end())
							open.erase(openIt);
						open.insert(std::make_pair(desk.STATE, depth));
					}
				}
				undo(desk.STATE, i);
			}
		}
	}
	desk.STATE.printNode();
	return solution();
}
