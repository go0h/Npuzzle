/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeUtils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 18:27:54 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/03 17:39:11 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <set>
#include <iostream>

#include "Node.h"
#include "PuzzExcept.h"

void Node::swap(Node & src)
{
	std::swap(side, src.side);
	std::swap(length, src.length);
	std::swap(zero, src.zero);
	std::swap(field, src.field);
}

void Node::printNode(void) noexcept
{
	for (size_t i = 0; i != side; ++i) {
		for (size_t j = 0; j != side; ++j)
			printf("%-3u ", (*this)(i, j));
		std::cout << '\n';
	}
	std::cout << '\n';
}
