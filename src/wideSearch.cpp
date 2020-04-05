/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wideSearch.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 17:46:34 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/05 14:51:17 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <unordered_map>
#include <queue>
#include <list>
#include <functional>

#include "Node.h"

extern size_t g_length;
extern size_t g_side;

class hashNode {
public:
	size_t operator()(Node const & puzzle) const
	{
		size_t hash = 0;
		for (size_t i = 0; i != g_length; ++i) {
			hash += puzzle.field[i] * (1ull << i);
		}
		return hash;
	}
};

typedef	bool (*move_func)(Node &);

using priority_queue = std::priority_queue<Node, std::vector<Node>>;
using hash_table = std::unordered_map<Node, CELL, hashNode>;
using solution = std::list<char>;

move_func moves[] = {nullptr, &up, &down, &right, &left};

static void undo(Node & node, size_t & i)
{
	node.move = NONE;
	if (i % 2 == 0)
		moves[i - 1](node);
	else
		moves[i + 1](node);
}

solution Search(Node & src)
{
	hash_table		close;
	priority_queue	open;
	solution		solut;

	close.reserve(g_length * g_side);

	if (!src.getScore(true))
		return solut;

	open.push(src);
	close.emplace(src, src.getScore(true));

	Node temp;
	while (!open.empty()) {
		temp = open.top();
		open.pop();
		close.emplace(temp, temp.getScore(false));
		for (size_t i = UP; i <= LEFT; ++i) {
			if (moves[i](temp)) {
				if (close.find(temp) == close.end()) {
					temp.getScore(true);
					open.push(temp);
					solut.push_back(i);
					if (!temp.score) {
						temp.printNode();
						return solut ;
					}
				}
				undo(temp, i);
			}
		}
	}
	return solut;
}
