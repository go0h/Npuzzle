/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UniformCostSearch.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 21:24:54 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/07 23:06:38 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Npuzzle.h"

#include <unordered_set>
#include <map>
#include <set>

#include "Npuzzle.h"

extern move_func	g_move[];

using PriorityQueue	= std::multiset< Node >;
using HashTable		= std::unordered_set< Node, hashNode >;


static Solution		GenerateMoves(Node & src, Node & trg, HashTable & close)
{
	Solution	moves;

	while (trg != src)
	{
		moves.push_front(trg.getMove());
		undo(trg, trg.getMove());
		trg = *close.find(trg);
	}
	return moves;
}

Solution			UniformCostSearch(Node & src, IHeuristic & h, marks & bench)
{
	HashTable		close;
	PriorityQueue	open;
	Node			state = src;
	size_t			depth = 0;

	bench.func = __func__;
	open.insert(state);
	while (!open.empty())
	{
		state = *(open.begin());
		open.erase(open.begin());
		if (!h(state))
			break;
		close.insert(state);
		for (size_t i = UP; i <= LEFT; ++i)
		{
			if (g_move[i](state))
			{
				state.setScore(depth);
				if (close.find(state) == close.end())
				{
					open.insert(state);
					bench.sizeComplexity++;
				}
				undo(state, i);
			}
		}
		depth += COST;
	}
	bench.timeComplexity += close.size();
	bench.t2 = std::chrono::system_clock::now();
	return GenerateMoves(src, state, close);
}
