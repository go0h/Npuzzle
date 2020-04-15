/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Npuzzle.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 19:51:21 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/13 09:23:51 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_H
# define NPUZZLE_H

#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <list>
#include <map>
#include <set>

#include "Node.h"
#include "Heuristic.h"

using Desk				= std::pair< unsigned, Node >;
using PriorityQueue		= std::map< unsigned, std::set< Node > >;
using HashTable			= std::unordered_map< Node, unsigned, hashNode >;
using ItOpen 			= std::pair< typename PriorityQueue::iterator, \
									typename std::set< Node >::iterator >;
using Solution			= std::list<unsigned>;

Solution	ASearch(Node & src, ManhattanNode & hev);

#endif
