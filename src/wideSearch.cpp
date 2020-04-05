/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wideSearch.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 17:46:34 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/05 17:56:05 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <queue>
#include <unordered_set>

#include "Node.h"
#include "Npuzzle.h"

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
	Node		temp;
	solution	moves;

	moves.push_front(target.move);
	undo(target, target.move);
	while (target.depth)
	{
		target = *(close.find(target));
		moves.push_front(target.move);
		undo(target, target.move);
		target.depth -= 1;
	}
	return moves;
}

solution Search(Node & src)
{
	hash_table		close;
	priority_queue	open;

	// close.reserve(g_length * g_side);

	if (!src.getScore())
		return solution();

	open.push(src);
	close.insert(src);

	Node	temp;
	while (!open.empty())
	{
		temp = open.top();
		open.pop();
		close.insert(temp);
		temp.depth += 1;
		for (size_t i = UP; i <= LEFT; ++i)
		{
			if (g_move[i](temp))
			{
				auto it = close.find(temp);
				if (it != close.end())
				{
					if (temp.depth < it->depth)
					{
						// printf("old = %u, new = %u\n", it->depth, temp.depth);
						close.erase(it);
						close.insert(temp);
					}
				}
				else
				{
					open.push(temp);
					if (!temp.getScore())
						return GenerateMoves(temp, close);
				}
				undo(temp, i);
			}
		}
	}
	return solution();
}
