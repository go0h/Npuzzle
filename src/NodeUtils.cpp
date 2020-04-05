/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeUtils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 18:27:54 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/05 12:36:18 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <set>
#include <iostream>

#include "Node.h"
#include "PuzzExcept.h"

extern size_t g_side;

void Node::swap(Node & src)
{
	std::swap(zero, src.zero);
	std::swap(score, src.score);
	std::swap(field, src.field);
}

void Node::printNode(void) noexcept
{
	for (size_t i = 0; i != g_side; ++i) {
		for (size_t j = 0; j != g_side; ++j)
			printf("%-3u ", (*this)(i, j));
		std::cout << '\n';
	}
	std::cout << '\n';
}
