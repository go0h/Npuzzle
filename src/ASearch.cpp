/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASearch.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 17:46:34 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/07 18:27:21 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Npuzzle.h"

extern size_t			g_length;
extern size_t			g_side;
extern move_func		g_move[];

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
	Node			temp;
	unsigned		score = 0;

	// close.reserve(g_length * g_side);

	if (!src.getScore(true))
		return solution();

	open.insert(src);
	close.insert(src);

	while (!open.empty())
	{
		temp = *(open.begin());
		open.erase(temp);
		temp.depth += 1;
		score = temp.getScore(false);

		close.insert(temp);
		for (size_t i = UP; i <= LEFT; ++i)
		{
			if (g_move[i](temp))
			{
				if (!temp.getScore(true))
					return GenerateMoves(temp, close);
				auto closeIt = close.find(temp);
				if (closeIt == close.end())
				{
					auto it = open.find(temp);
					if (it != open.end() && temp.depth < (*it).depth)
					{
						open.erase(it);
					}
					open.insert(temp);
				}
				// else
				// {
				// 	if (temp.depth < closeIt->depth)
				// 	{
				// 		close.erase(closeIt);
				// 		close.insert(temp);
				// 	}
				// }
				temp.score = score;
				undo(temp, i);
			}
		}
	}
	temp.printNode();
	return solution();
}
