/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeOperators.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 21:38:37 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/15 20:23:09 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.h"
#include "PuzzExcept.h"
#include <cstring>

extern size_t g_length;
extern size_t g_side;

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

bool operator==(Node const & n1, Node const & n2)
{
	// for (size_t i = 0; i != g_length; ++i)
	// {
	// 	if (n1.field[i] != n2.field[i])
	// 		return false;
	// }
	// return true;
	return !std::memcmp(n1.field, n2.field, sizeof(CELL) * g_length);
}

bool operator!=(Node const & n1, Node const & n2)
{
	// if (n1 < n2 || n2 < n1)
	// 	return true;
	return !(n1 == n2);
}

bool operator<(Node const & n1, Node const & n2)
{
	if (n1.score < n2.score)
		return true;
	if (n1.score == n2.score)
		return n1.zero > n2.zero;
	return false;
}

CELL & Node::operator()(size_t i, size_t j)
{
	if (i >= g_side && j >= g_side)
		throw PuzzExcept(E_INDEX);
	return field[i * g_side + j];
}

CELL Node::operator()(size_t i, size_t j) const
{
	if (i >= g_side && j >= g_side)
		throw PuzzExcept(E_INDEX);
	return field[i * g_side + j];
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

size_t hashNode::operator()(Node const & puzzle) const
{
	size_t hash = 0;
	size_t pow = 31;
	for (size_t i = 0; i != g_length; ++i)
	{
		hash = hash + (puzzle.field[i] * pow);
		pow *= 31;
	}
	return hash;
}

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
