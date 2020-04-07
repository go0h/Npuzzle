/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Npuzzle.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 19:51:21 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/06 21:13:22 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_H
# define NPUZZLE_H

#include <iostream>
#include <unordered_set>
#include <list>
#include <set>

#include "Node.h"

using solution 			= std::list<t_move>;
using move_func 		= bool (*)(Node &);
using PriorityQueue		= std::set<Node>;
using HashTable			= std::unordered_set<Node, hashNode>;


bool 		up(Node & puzzle);

bool 		down(Node & puzzle);

bool 		right(Node & puzzle);

bool 		left(Node & puzzle);

solution	Search(Node & src);

void		printMoves(Node src, solution & movSet);

#endif
