/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:17:23 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/05 17:33:11 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <iostream>

#include "Node.h"
#include "PuzzExcept.h"

extern size_t g_length;
extern size_t g_side;

Node::Node(void) { }

Node::Node(CELL size)
{
	field = new CELL[size * size];
}

Node::Node(Node const & src)
	: zero(src.zero),
	move(src.move),
	depth(src.depth)
{
	field = new CELL[g_length];
	memcpy(field, src.field, sizeof(CELL) * g_length);
}

Node::Node(Node && src)
{
	*this = std::move(src);
}

Node::~Node()
{
	delete [] field;
}
