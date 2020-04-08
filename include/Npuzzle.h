/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Npuzzle.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 19:51:21 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/07 21:30:39 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_H
# define NPUZZLE_H

#include <iostream>
#include <unordered_set>
#include <list>
#include <map>

#include "Node.h"

using solution 			= std::list<t_move>;
using move_func 		= bool (*)(Node &);
using PriorityQueue		= std::map<Node, unsigned>;
using HashTable			= std::unordered_set<Node, hashNode>;
using Desk				= std::pair<Node, unsigned>;

bool 		up(Node & puzzle);

bool 		down(Node & puzzle);

bool 		right(Node & puzzle);

bool 		left(Node & puzzle);

solution	Search(Node & src);

void		printMoves(Node src, solution & movSet);

#endif
