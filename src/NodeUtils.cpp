/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeUtils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 18:27:54 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/06 21:17:42 by astripeb         ###   ########.fr       */
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
	std::swap(depth, src.depth);
	std::swap(score, src.score);
	std::swap(field, src.field);
}

void Node::printNode(void) noexcept
{
	for (size_t i = 0; i != g_side; ++i)
	{
		for (size_t j = 0; j != g_side; ++j)
			printf("%-3u ", (*this)(i, j));
		printf("\n");
	}
	printf("\n");
}


void printMoves(Node src, solution & movSet)
{
	for (auto i = std::next(movSet.begin()); i != movSet.end(); ++i)
	{
		g_move[*i](src);
		src.printNode();
	}
	if (!src.getScore(false))
		printf("Well done!\n");
}
