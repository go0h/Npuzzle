/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IDAStarSearch.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 14:13:30 by astripeb          #+#    #+#             */
/*   Updated: 2020/06/02 13:53:14 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Npuzzle.h"
#include "PuzzExcept.h"
#include <algorithm>

using PathCont		= std::list< Node >;

extern move_func	g_move[];

static Solution	GenerateMoves(PathCont & path)
{
	Solution	moves;

	for (auto it = path.rbegin(); it != path.rend(); ++it)
		moves.push_front((*it).getMove());
	moves.pop_front();
	return moves;
}

static size_t 	search(Node src, size_t depth, size_t bound,
			IHeuristic & h, PathCont & path, marks & bench)
{
	size_t t;
	size_t f = depth + h(src);
	if (f > bound)
		return f;
	if (!src.getScore())
		return 0;

	size_t min = SIZE_MAX;
	for (size_t i = UP; i <= LEFT; ++i)
	{
		if (g_move[i](src))
		{
			auto it = std::find(path.begin(), path.end(), src);
			if (it == path.end())
			{
				path.push_back(src);
				t = search(src, depth + COST, bound, h, path, bench);
				bench.timeComplexity++;
				bench.sizeComplexity = std::max(path.size(), bench.sizeComplexity);
				if (!t)
					return t;
				if (t < min)
					min = t;
				path.pop_back();
			}
			undo(src, i);
		}
	}
	return min;
}

Solution		IDAStarSearch(Node & root, IHeuristic & h, marks & bench)
{
	size_t t;
	size_t bound = h(root);
	PathCont path;

	bench.func = __func__;
	path.push_back(root);
	if (!bound)
		return Solution();
	while (true)
	{
		t = search(root, 0, bound, h, path, bench);
		if (!t)
		{
			bench.t2 = std::chrono::system_clock::now();
			return GenerateMoves(path);
		}
		else if (t == SIZE_MAX)
			throw PuzzExcept(E_UNSOLVBL);
		bound = t;
	}
	return Solution();
}
