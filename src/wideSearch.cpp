/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wideSearch.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 17:46:34 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/03 22:41:55 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <unordered_map>
#include <queue>
#include <list>

#include "Node.h"

typedef	bool (*move_func)(Node &);

typedef	enum {
	UP,
	DOWN,
	RIGHT,
	LEFT
} MOVE;

move_func moves[] = {&up, &down, &right, &left};

namespace std {
template<>
class hash<Node> {
public:
	size_t operator()(Node const & puzzle) const
	{
		size_t hash = 0;
		for (size_t i = 0; i != puzzle.length; ++i) {
			hash = hash ^ std::hash<CELL>()(puzzle.field[i]);
		}
		return hash;
	}
};
}

std::list<int> Search(Node & src)
{
	CELL 							score = 0;
	std::unordered_map<Node, CELL>	close;
	std::queue<Node>				queqe;
	std::list<int>					solution;

	queqe.push(src);
	score = manhattanScore(src);
	if (!score)
		return solution;

	close.emplace(src, score);
	while (!queqe.empty()) {
		Node cur = queqe.front();
		queqe.pop();
		Node temp(cur);
		close.emplace(cur, manhattanScore(src));
		for (size_t i = UP; i <= LEFT; ++i) {
			if (moves[i](temp)) {
				if (close.find(temp) == close.end()) {
					if (!(score = manhattanScore(temp)))
						return solution;
					queqe.push(temp);
					solution.push_back(i);
					temp = cur;
				}
			}
		}
	}
	return solution;
}
