/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Npuzzle.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 19:51:21 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/10 21:02:37 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_H
# define NPUZZLE_H

#include <iostream>
#include <unordered_map>
#include <list>
#include <map>

#include "Node.h"

using solution 			= std::list<t_move>;
using move_func 		= bool (*)(Node &);
using Desk				= std::pair<Node, unsigned>;
using PriorityQueue		= std::map<Node, unsigned>;
using HashTable			= std::unordered_map<Node, unsigned, hashNode>;

bool 		up(Node & puzzle);

bool 		down(Node & puzzle);

bool 		right(Node & puzzle);

bool 		left(Node & puzzle);

solution	Search(Node & src);

void		printMoves(Node src, solution & movSet);

#endif
