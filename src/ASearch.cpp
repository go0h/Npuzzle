/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASearch.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 17:46:34 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/20 22:12:28 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Npuzzle.h"

extern move_func		g_move[];

#define DEPTH			first
#define STATE			second

inline static void		undo(Node & node, size_t i)
{
	node.move = NONE;
	if (i % 2 == 0)
		g_move[i - 1](node);
	else
		g_move[i + 1](node);
}

static Solution	GenerateMoves(Node & src, Node & target, HashTable & close)
{
	Solution	moves;

	target.printNode();
	moves.push_front(target.move);
	while (target != src)
	{
		undo(target, target.move);
		target = close.find(target)->first;
		moves.push_front(target.move);
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
	auto i = open.lower_bound(desk.STATE.score + desk.DEPTH);
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

Solution		ASearch(Node & src, IHeuristic & getScore)
{
	HashTable		close;
	PriorityQueue	open;
	Desk			desk;
	ItOpen			openIt;
	unsigned		depth, score;

	close.reserve(1000000);
	if (!getScore(src))
		return Solution();
	open[src.getScore()].insert(src);

	while (!open.empty())
	{
		desk = getFirstDesk(open, desk);
		if (!desk.STATE.getScore())
			break;
		close.emplace(desk.STATE, desk.DEPTH);
		depth = desk.DEPTH + 1;

		for (size_t i = UP; i <= LEFT; ++i)
		{
			if (g_move[i](desk.STATE))
			{
				auto closeIt = close.find(desk.STATE);
				score = getScore(desk.STATE) + depth;
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
						}
						open[score].insert(desk.STATE);
					}
				}
				else if (depth < closeIt->second)
				{
					close.erase(closeIt);
					open[score].insert(desk.STATE);
				}
				undo(desk.STATE, i);
			}
		}
	}
	printf("States in open:  %lu\n", open.size());
	printf("States in close: %lu\n", close.size());
	return GenerateMoves(src, desk.STATE, close);
}
