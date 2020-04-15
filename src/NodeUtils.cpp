/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeUtils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 18:27:54 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/12 18:13:04 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <set>
#include <iostream>

#include "Node.h"
#include "PuzzExcept.h"
#include "Npuzzle.h"

extern size_t		g_side;
extern move_func	g_move[];;

void Node::swap(Node & src)
{
	std::swap(zero, src.zero);
	std::swap(move, src.move);
	std::swap(score, src.score);
	std::swap(field, src.field);
}

void Node::printNode(void) const
{
	for (size_t i = 0; i != g_side; ++i)
	{
		for (size_t j = 0; j != g_side; ++j)
			printf("%-3u ", (*this)(i, j));
		printf("\n");
	}
	printf("\n");
}

// void printMoves(Node src, Solution & movSet)
// {
// 	unsigned i = 1;

// 	printf("Step #0:\n");
// 	src.printNode();
// 	for (auto it = std::next(movSet.begin()); it != movSet.end(); ++i, ++it)
// 	{
// 		printf("Step #%u:\n", i);
// 		g_move[*it](src);
// 		src.printNode();
// 	}
// }
