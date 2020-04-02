/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeUtils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 18:27:54 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/02 20:06:53 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <set>
#include <iostream>

#include "Node.h"
#include "PuzzExcept.h"

void Node::swap(Node & src)
{
	std::swap(side, src.side);
	std::swap(field, src.field);
}

// эта часть добавление в readPuzzle
/*
void	Node::validate(void)
{
	std::set<CELL> order;

	for (size_t i = 0; i != side; ++i) {
		for (size_t j = 0; j != side; ++j)
			order.insert(field[i][j]);
	}
	if (order.size() != side * side)
		throw PuzzExcept(E_SFIELDS);
	auto it = order.begin();
	for (size_t i = 0; i != (side * side) && it != order.end(); ++i, ++it) {
		if (*it != i)
			throw PuzzExcept(E_ORDER);
	}
}
*/

void Node::printNode(void) noexcept
{
	for (size_t i = 0; i != side; ++i) {
		for (size_t j = 0; j != side; ++j)
			std::cout << field[i][j] << ' ';
		std::cout << '\n';
	}
}
