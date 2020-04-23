/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GreedySearch.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 17:46:34 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/23 14:38:59 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Npuzzle.h"
#include <queue>
#include <unordered_set>

#define DEPTH		first
#define STATE		second

extern move_func	g_move[];

using Desk			= std::pair< unsigned, Node >;
using PriorityQueue	= std::map< size_t, std::set <Node> >;
using HashTable		= std::unordered_set< Node, hashNode >;

inline static void		undo(Node & node, size_t i)
{
	node.move = NONE;
	if (i % 2 == 0)
		g_move[i - 1](node);
	else
		g_move[i + 1](node);
}

static Solution			GenerateMoves(Node & src, Node & target,
									HashTable & close)
{
	Solution	moves;

	target.printNode();
	while (target != src)
	{
		moves.push_front(target.move);
		undo(target, target.move);
		target = *close.find(target);
	}
	return moves;
}

inline static void getFirst(PriorityQueue & open, Node & state)
{
	auto it = open.begin();
	state = *(it->second.begin());
	it->second.erase(it->second.begin());
	if (it->second.empty())
		open.erase(it);
}

Solution				GreedySearch(Node & src, IHeuristic & getScore)
{
	HashTable		close;
	PriorityQueue	open;
	Node			state = src;
	size_t			score = 0;

	if (!getScore(state))
		return Solution();
	open[state.getScore()].insert(state);
	while (!open.empty())
	{
		getFirst(open, state);
		if (!state.getScore())
			break;
		close.insert(state);
		for (size_t i = UP; i <= LEFT; ++i)
		{
			if (g_move[i](state))
			{
				score = getScore(state);
				if (close.find(state) == close.end())
					open[score].insert(state);
				undo(state, i);
			}
		}
	}
	printf("States in open:  %lu\n", open.size());
	printf("States in close: %lu\n", close.size());
	return GenerateMoves(src, state, close);
}
