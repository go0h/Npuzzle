/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:17:23 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/17 20:12:12 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <iostream>

#include "Node.h"
#include "PuzzExcept.h"

size_t Node::side_		= DEFAULT_SIZE;
size_t Node::length_	= (DEFAULT_SIZE * DEFAULT_SIZE);

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
