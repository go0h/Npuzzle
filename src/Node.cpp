/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:17:23 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/03 12:03:33 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <iostream>

#include "Node.h"
#include "PuzzExcept.h"

Node::Node(void) : side(0), field(nullptr) { }

Node::Node(CELL size) : side(size), zx(0), zy(0)
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
	for (size_t i = 0; i != side; ++i) {
		for (size_t j = 0; j != side; ++j) {
			if (field[i][j] == 0) {
				zx = j;
				zy = i;
			}
		}
	}
}

Node::Node(Node const & src) : side(src.side), zx(src.zx), zy(src.zy)
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

bool operator==(Node const & n1, Node const & n2)
{
	if (n1.side != n2.side || n1.zx != n2.zx || n1.zy != n2.zy)
		return false;

	for (size_t i = 0; i != n1.side; ++i) {
		for (size_t j = 0; j != n1.side; ++j) {
			if (n1.field[i][j] != n2.field[i][j])
				return false;
		}
	}
	return true;
}

bool operator!=(Node const & n1, Node const & n2) {
	return !(n1 == n2);
}

CELL & Node::operator()(size_t i, size_t j) {
	if (i < side && j < side)
		return field[i][j];
	else
		throw PuzzExcept(E_INDEX);
}

CELL Node::operator()(size_t i, size_t j) const {
	if (i < side && j < side)
		return field[i][j];
	else
		throw PuzzExcept(E_INDEX);
}
