/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeUtils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 22:48:24 by astripeb          #+#    #+#             */
/*   Updated: 2020/06/01 00:05:11 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.h"

/*
**	Generate snail board state. Example for side == 3:
**		1 2 3
**		8 0	4
**		7 6 5
**
**	top left -> top right
**	top right -> bottom right
**	bottom right -> bottom left
**	bottom left -> top left
*/

Node		snail(int side)
{
	Node temp(side);
	int i = 0;
	int col, row;
	int count = 1;

	while (i < side / 2)
	{
		for (col = i, row = i; col < side - i; ++col)
			temp(row, col) = count++ % (side * side);
		for (row = row + 1, col = col - 1; row < side - i; ++row)
			temp(row, col) = count++ % (side * side);
		for (col = col - 1, row = row - 1; col >= i; --col)
			temp(row, col) = count++ % (side * side);
		for (row = row - 1, col = col + 1; row > i; --row)
			temp(row, col) = count++ % (side * side);
		++i;
	}
	return temp;
}

/*
bool 		solvable(Node & src, Node & trg)
{
	size_t	sum = 0;
	size_t	zPos = 0;

	for (size_t i = 0; i != length_; ++i)
	{
		if (!field[i])
			zPos = i;
		for (size_t j = i + 1; j < length_; ++j)
		{
			if (field[i] && field[j])
			{
				if (field[i] > field[j])
					sum++;
			}
		}
	}
	return (sum + ((zPos / side_) + 1)) % 2 == 0;
}
*/

size_t		Node::getHash(void) const
{
	size_t hash = 0;
	size_t pow = 31;
	for (size_t i = 0; i != length_; ++i)
	{
		hash = hash + (field[i] * pow);
		pow *= 31;
	}
	return hash;
}

unsigned	Node::getScore(void) const
{
	return score;
}

void		Node::printNode(void) const
{
	for (size_t i = 0; i != side_; ++i)
	{
		for (size_t j = 0; j != side_; ++j)
			printf("%-3u ", (*this)(i, j));
		printf("\n");
	}
	printf("\n");
}




