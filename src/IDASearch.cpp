/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IDASearch.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 14:13:30 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/23 15:11:38 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Npuzzle.h"
#include "PuzzExcept.h"
#include <algorithm>

#define COST 1

using PathCont		= std::list< Node >;
extern move_func	g_move[];

/*
** PSEUDOCODE
node              текущий узел
g                 стоимость начала решения root..node
f                 оценка стоимости минимального пути через node
h(node)           эвристическая оценка стоимости остатка пути node..goal
cost(node, succ)  функция стоимости пути
is_goal(node)     функция проверки цели
successors(node)  функция развёртывания узла node

procedure ida_star(root, cost(), is_goal(), h())
bound := h(root)
loop
	t := search(root, 0, bound)
	if t = FOUND then return FOUND
	if t = ∞ then return NOT_FOUND
	bound := t
end loop
end procedure

function search(node, g, bound)
f := g + h(node)
if f > bound then return f
if is_goal(node) then return FOUND
min := ∞
for succ in successors(node) do
	t := search(succ, g + cost(node, succ), bound)
	if t = FOUND then return FOUND
	if t < min then min := t
end for
return min
end function
**
*/

inline static void		undo(Node & node, size_t i)
{
	node.move = NONE;
	if (i % 2 == 0)
		g_move[i - 1](node);
	else
		g_move[i + 1](node);
}

static Solution	GenerateMoves(PathCont & path)
{
	Solution	moves;

	(*path.rbegin()).printNode();
	for (auto it = path.rbegin(); it != path.rend(); ++it)
		moves.push_front((*it).move);
	moves.pop_front();
	return moves;
}

size_t search(Node src, size_t depth, size_t bound,
			IHeuristic & h, PathCont & path)
{
	size_t t = 0;
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
				t = search(src, depth + COST, bound, h, path);
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

Solution IDASearch(Node & root, IHeuristic & h)
{
	size_t t = 0;
	size_t bound = h(root);
	PathCont path;

	path.push_back(root);
	if (!bound)
		return Solution();
	while (true)
	{
		t = search(root, 0, bound, h, path);
		if (!t)
			return GenerateMoves(path);
		else if (t == SIZE_MAX)
			throw PuzzExcept(E_UNSOLVBL);
		bound = t;
	}
	return Solution();
}
