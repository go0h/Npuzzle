/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:17:23 by astripeb          #+#    #+#             */
/*   Updated: 2020/05/31 22:49:19 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>

#include "Node.h"
#include "PuzzExcept.h"

extern move_func	g_move[];;

size_t Node::side_		= 0;
size_t Node::length_	= 0;

Node::Node(void) { }

Node::Node(t_tile side) : field(new t_tile[side * side])
{
	side_ = side;
	length_ = side * side;
}

Node::Node(Node const & src)
	: field(new t_tile[length_]),
	score(src.score),
	zero(src.zero),
	move(src.move)
{
	memcpy(field, src.field, sizeof(t_tile) * length_);
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

bool	Node::operator==(Node const & n) const
{
	return !std::memcmp(field, n.field, sizeof(t_tile) * length_);
}

bool	Node::operator!=(Node const & n) const
{
	return !(*this == n);
}

bool	Node::operator<(Node const & n) const
{
	if (score < n.score)
		return true;
	if ( !(score - n.score) && zero > n.zero)
		return true;
	return false;
}

t_tile &	Node::operator()(size_t i, size_t j)
{
	if (i >= side_ && j >= side_)
		throw PuzzExcept(E_INDEX);
	return field[i * side_ + j];
}

t_tile		Node::operator()(size_t i, size_t j) const
{
	if (i >= side_ && j >= side_)
		throw PuzzExcept(E_INDEX);
	return field[i * side_ + j];
}

Node::operator bool(void)
{
	return field;
}

void		Node::swap(Node & src)
{
	std::swap(zero, src.zero);
	std::swap(move, src.move);
	std::swap(score, src.score);
	std::swap(field, src.field);
}
