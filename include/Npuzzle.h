/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Npuzzle.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 19:51:21 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/17 13:05:47 by astripeb         ###   ########.fr       */
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

using Desk				= std::pair< unsigned, Node >;
using PriorityQueue		= std::map< unsigned, std::set< Node > >;
using HashTable			= std::unordered_map< Node, unsigned, hashNode >;
using ItOpen 			= std::pair< typename PriorityQueue::iterator, \
									typename std::set< Node >::iterator >;
using Solution			= std::list<unsigned>;

Solution	ASearch(Node & src);

#endif
