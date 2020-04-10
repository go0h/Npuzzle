/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASearch.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 17:46:34 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/10 21:04:38 by astripeb         ###   ########.fr       */
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

static solution GenerateMoves(Node & target, HashTable & close)
{
	solution	moves;

	printf("States in close: %lu\n", close.size());
	target.printNode();
	moves.push_front(target.move);
	while (target.move != NONE)
	{
		undo(target, target.move);
		target = close.find(target)->STATE;
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

	if (!src.getScore())
		return solution();

	open.emplace(src, 0);
	close.emplace(src, 0);

	while (!open.empty())
	{
		desk = *(open.begin());
		open.erase(desk.STATE);
		if (!desk.STATE.score)
			break ;
		close.emplace(desk.STATE, desk.DEPTH);

		depth = desk.DEPTH + 1;
		for (size_t i = UP; i <= LEFT; ++i)
		{
			if (g_move[i](desk.STATE))
			{
				auto closeIt = close.find(desk.STATE);
				desk.STATE.getScore();
				if (closeIt == close.end())
				{
					auto openIt = open.find(desk.STATE);
					if (openIt == open.end() || depth < openIt->DEPTH)
					{
						if (openIt != open.end())
							open.erase(openIt);
						open.emplace(desk.STATE, depth);
					}
				}
				else if (depth < closeIt->DEPTH)
				{
					close.erase(desk.STATE);
					open.emplace(desk.STATE, depth);
				}
				undo(desk.STATE, i);
			}
		}
	}
	printf("States in open:  %lu\n", open.size());
	return GenerateMoves(desk.STATE, close);
}
