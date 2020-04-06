/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASearch.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 17:46:34 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/06 08:43:53 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <queue>
#include <unordered_set>

#include "Node.h"
#include "Npuzzle.h"
#include "PriorityQueue.h"

extern size_t			g_length;
extern size_t			g_side;
extern move_func		g_move[];

using priority_queue	= std::priority_queue<Node>;
using hash_table		= std::unordered_set<Node, hashNode>;


static void undo(Node & node, size_t i)
{
	node.move = NONE;
	if (i % 2 == 0)
		g_move[i - 1](node);
	else
		g_move[i + 1](node);
}

static solution GenerateMoves(Node target, hash_table & close)
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
	hash_table		close;
	PriorityQueue	open;
	Node			temp;

	// close.reserve(g_length * g_side);

	if (!src.getScore())
		return solution();

	open.push(src);
	close.insert(src);

	while (!open.empty())
	{
		temp = open.pop();
		temp.depth += 1;
		close.insert(temp);
		for (size_t i = UP; i <= LEFT; ++i)
		{
			if (g_move[i](temp))
			{
				if (close.find(temp) == close.end())
				{
					auto it = open.find(temp);
					if (it != open.end())
					{
						if (temp.depth < (*it).depth)
							open.remove(it);
					}
					open.push(temp);
					if (!temp.getScore())
						return GenerateMoves(temp, close);
				}
				undo(temp, i);
			}
		}
	}
	temp.printNode();
	return solution();
}
