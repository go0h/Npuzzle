/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GreedySearch.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 17:46:34 by astripeb          #+#    #+#             */
/*   Updated: 2020/06/02 10:52:30 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unordered_set>
#include <map>
#include <set>

#include "Npuzzle.h"

#define DEPTH		first
#define STATE		second

extern move_func	g_move[];

using Desk			= std::pair< unsigned, Node >;
using PriorityQueue	= std::map< size_t, std::set <Node> >;
using HashTable		= std::unordered_set< Node, hashNode >;

static Solution		GenerateMoves(Node & src, Node & trg, HashTable & close)
{
	Solution	moves;

	while (trg != src)
	{
		moves.push_front(trg.move);
		undo(trg, trg.move);
		trg = *close.find(trg);
	}
	return moves;
}

inline static void	getFirst(PriorityQueue & open, Node & state)
{
	auto it = open.begin();
	state = *(it->second.begin());
	it->second.erase(it->second.begin());
	if (it->second.empty())
		open.erase(it);
}

Solution			GreedySearch(Node & src, IHeuristic & h, marks & bench)
{
	HashTable		close;
	PriorityQueue	open;
	Node			state = src;
	size_t			score = 0;

	bench.func = __func__;
	open[h(state)].insert(state);
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
				score = h(state);
				if (close.find(state) == close.end())
				{
					open[score].insert(state);
					bench.compl_size++;
				}
				undo(state, i);
			}
		}
	}
	bench.compl_time += close.size();
	bench.t2 = std::chrono::system_clock::now();
	return GenerateMoves(src, state, close);
}
