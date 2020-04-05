/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:17:23 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/05 14:39:57 by astripeb         ###   ########.fr       */
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

Node::Node(char const **str, size_t size)
{
	field = new CELL[size * size];
	for (size_t i = 0, j = 0; i != size; ++i, j += size) {
		memcpy(&field[j], str[i], sizeof(CELL) * size);
	}
	for (size_t i = 0; i != size * size; ++i) {
		if (field[i] == 0)
			zero = i;
	}
}

Node::Node(Node const & src)
	: zero(src.zero),
	score(src.score),
	move(src.move)
{
	field = new CELL[g_length];
	memcpy(field, src.field, sizeof(CELL) * g_length);
}

Node::Node(Node && src) {
	*this = std::move(src);
}

Node::~Node()
{
	delete [] field;
}
