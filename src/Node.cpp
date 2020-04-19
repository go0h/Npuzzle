/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:17:23 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/19 22:10:54 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <iostream>

#include "Node.h"
#include "PuzzExcept.h"

size_t Node::side_		= 0;
size_t Node::length_	= 0;

Node::Node(void) { }

Node::Node(CELL side)
{
	side_ = side;
	length_ = side * side;
	field = new CELL[side * side];
}

Node::Node(Node const & src)
	: zero(src.zero),
	score(src.score),
	move(src.move)
{
	field = new CELL[length_];
	memcpy(field, src.field, sizeof(CELL) * length_);
}

Node::Node(Node && src)
{
	*this = std::move(src);
}

Node::~Node()
{
	delete [] field;
}

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

Node::operator bool(void)
{
	return field;
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

unsigned		Node::getScore(void) const
{
	return score;
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
