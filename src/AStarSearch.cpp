/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStarSearch.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 17:46:34 by astripeb          #+#    #+#             */
/*   Updated: 2020/06/02 14:11:05 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Npuzzle.h"

#include <unordered_map>
#include <map>
#include <set>

#define DEPTH		first
#define STATE		second

extern move_func	g_move[];

using Desk			= std::pair< unsigned, Node >;
using PriorityQueue	= std::map< unsigned, std::set< Node > >;
using HashTable		= std::unordered_map< Node, unsigned, hashNode >;
using ItOpen 		= std::pair< typename PriorityQueue::iterator, \
								typename std::set< Node >::iterator >;

void				undo(Node & node, size_t i)
{
	node.getMove() = NONE;
	if (i & 1U)
		g_move[i + 1](node);
	else
		g_move[i - 1](node);
}

static Solution			GenerateMoves(Node & src, Node & trg, HashTable & close)
{
	Solution	moves;

	while (trg != src)
	{
		moves.push_front(trg.getMove());
		undo(trg, trg.getMove());
		trg = close.find(trg)->first;
	}
	return moves;
}

inline static Desk &	getFirstDesk(PriorityQueue & open, Desk & desk)
{
	auto it = open.begin();
	desk.STATE = *(it->second.begin());
	desk.DEPTH = it->first - desk.STATE.getScore();

	open[it->first].erase(it->second.begin());
	if (open[it->first].empty())
		open.erase(it->first);
	return desk;
}

inline static bool		inOpen(PriorityQueue & open, Desk & desk, ItOpen & it)
{
	auto i = open.lower_bound(desk.STATE.getScore() + desk.DEPTH);
	for (; i != open.end(); ++i)
	{
		auto deskIt = i->second.find(desk.STATE);
		if (deskIt != i->second.end() && *deskIt == desk.STATE)
		{
			it.first = i;
			it.second = deskIt;
			return true;
		}
	}
	return false;
}

Solution				AStarSearch(Node & src, IHeuristic & h, marks & bench)
{
	HashTable		close;
	PriorityQueue	open;
	Desk			desk;
	ItOpen			openIt;
	unsigned		depth, score;

	bench.func = __func__;
	close.reserve(1000000);
	open[h(src)].insert(src);
	while (!open.empty())
	{
		desk = getFirstDesk(open, desk);
		if (!desk.STATE.getScore())
			break;
		close.emplace(desk.STATE, desk.DEPTH);
		depth = desk.DEPTH + COST;

		for (size_t i = UP; i <= LEFT; ++i)
		{
			if (g_move[i](desk.STATE))
			{
				auto closeIt = close.find(desk.STATE);
				score = h(desk.STATE) + depth;
				if (closeIt == close.end())
				{
					bool exist = inOpen(open, desk, openIt);
					if (!exist || score < openIt.first->first)
					{
						if (exist)
						{
							open[openIt.first->DEPTH].erase(openIt.second);
							if (open[openIt.first->DEPTH].empty())
								open.erase(openIt.first);
							bench.sizeComplexity--;
						}
						open[score].insert(desk.STATE);
					}
				}
				else if (depth < closeIt->second)
				{
					close.erase(closeIt);
					open[score].insert(desk.STATE);
				}
				bench.sizeComplexity++;
				undo(desk.STATE, i);
			}
		}
	}
	bench.sizeComplexity += close.size();
	bench.timeComplexity = close.size();
	bench.t2 = std::chrono::system_clock::now();
	return GenerateMoves(src, desk.STATE, close);
}
