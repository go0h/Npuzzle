/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:17:23 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/03 21:48:01 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <iostream>

#include "Node.h"
#include "PuzzExcept.h"

Node::Node(void) : side(0), field(nullptr) { }

Node::Node(CELL size) : side(size), length(size * size), zero(0)
{
	field = new CELL[side * side];
}

Node::Node(char const **str, CELL size) : side(size), length(size * size)
{
	field = new CELL[length];
	for (size_t i = 0, j = 0; i != side; ++i, j += side) {
		memcpy(&field[j], str[i], sizeof(CELL) * side);
	}
	for (size_t i = 0; i != length; ++i) {
		if (field[i] == 0)
			zero = i;
	}
}

Node::Node(Node const & src) : side(src.side), length(side * side), zero(src.zero)
{
	field = new CELL[length];
	memcpy(field, src.field, sizeof(CELL) * length);
}

Node::Node(Node && src) {
	*this = std::move(src);
}

Node::~Node()
{
	delete [] field;
}
