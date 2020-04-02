/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:17:23 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/02 20:21:41 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <iostream>

#include "Node.h"

Node::Node(void) : side(0), field(nullptr) { }

Node::Node(CELL size) : side(size)
{
	side = size;
	field = new CELL * [side];
	CELL *temp = new CELL[side * side];

	field[0] = temp;
	for (size_t i = 1, j = side; i != side; ++i, j += side)
		field[i] = &temp[j];
}

Node::Node(char const **str, CELL size) : side(size)
{
	field = new CELL * [side];
	CELL *temp = new CELL[side * side];

	field[0] = temp;
	memcpy(field[0], str[0], sizeof(CELL) * side);
	for (size_t i = 1, j = side; i != side; ++i, j += side) {
		field[i] = &temp[j];
		memcpy(field[i], str[i], sizeof(CELL) * side);
	}
}

Node::Node(Node const & src) : side(src.side)
{
	field = new CELL * [side];
	CELL *temp = new CELL[side * side];

	field[0] = temp;
	memcpy(field[0], src.field[0], sizeof(CELL) * side);
	for (size_t i = 1, j = side; i != side; ++i, j += side) {
		field[i] = &temp[j];
		memcpy(field[i], src.field[i], sizeof(CELL) * side);
	}
}

Node::~Node()
{
	if (field)
		delete [] field[0];
	delete [] field;
}

Node & Node::operator=(Node const & src)
{
	if (this == &src)
		return *this;
	Node temp(src);
	temp.swap(*this);
	return *this;
}
