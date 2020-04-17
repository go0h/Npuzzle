/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeOperators.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 21:38:37 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/17 14:53:45 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.h"
#include "PuzzExcept.h"
#include <cstring>

Node &	Node::operator=(Node const & src)
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
	this->swap(src);
	return (*this);
}

bool Node::operator==(Node const & n) const
{
	return !std::memcmp(field, n.field, sizeof(CELL) * length_);
}

bool Node::operator!=(Node const & n) const
{
	return !(*this == n);
}

bool Node::operator<(Node const & n) const
{
	if (score < n.score)
		return true;
	if (score == n.score)
		return zero > n.zero;
	return false;
}

CELL & Node::operator()(size_t i, size_t j)
{
	if (i >= side_ && j >= side_)
		throw PuzzExcept(E_INDEX);
	return field[i * side_ + j];
}

CELL Node::operator()(size_t i, size_t j) const
{
	if (i >= side_ && j >= side_)
		throw PuzzExcept(E_INDEX);
	return field[i * side_ + j];
}

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

// size_t hashNode::operator()(Node const & puzzle) const
// {
// 	size_t hash = 0;
// 	for (size_t i = 0; i != g_length; ++i)
// 	{
// 		hash += puzzle.field[i] * (1ull << i);
// 	}
// 	return hash;
// }


/*
class CompareNode
{
public:
    bool operator() (Node const & n1, Node const & n2) const
    {
		if (n1.score > n2.score)
			return true;
		return false;
    }
};

class EqualNode
{
public:
    bool operator() (Node const & n1, Node const & n2) const
    {
		for (size_t i = 0; i != g_length; ++i)
		{
			if (n1.field[i] != n2.field[i])
				return false;
		}
		return true;
    }
};
*/
