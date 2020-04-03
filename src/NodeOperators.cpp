/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeOperators.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 21:38:37 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/03 21:47:08 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.h"
#include "PuzzExcept.h"

Node & Node::operator=(Node const & src)
{
	if (this == &src)
		return *this;
	Node temp(src);
	temp.swap(*this);
	return *this;
}

Node &	Node::operator=(Node && src)
{
	if (this == &src)
		return *this;
	swap(src);
	return (*this);
}

bool operator==(Node const & n1, Node const & n2)
{
	if (n1.side != n2.side || n1.zero != n2.zero)
		return false;
	for (size_t i = 0; i != n1.length; ++i) {
		if (n1.field[i] != n2.field[i])
			return false;
	}
	return true;
}

bool operator!=(Node const & n1, Node const & n2)
{
	return !(n1 == n2);
}

bool operator<(Node const & n1, Node const & n2)
{
	return manhattanScore(n1) < manhattanScore(n2);
}

CELL & Node::operator()(size_t i, size_t j)
{
	if (i >= side && j >= side)
		throw PuzzExcept(E_INDEX);
	return field[i * side + j];
}

CELL Node::operator()(size_t i, size_t j) const
{
	if (i >= side && j >= side)
		throw PuzzExcept(E_INDEX);
	return field[i * side + j];
}
