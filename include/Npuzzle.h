/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Npuzzle.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 19:51:21 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/19 22:22:26 by astripeb         ###   ########.fr       */
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

#include "Heuristic.h"
#include "Node.h"

using Desk				= std::pair< unsigned, Node >;
using PriorityQueue		= std::map< unsigned, std::set< Node > >;
using HashTable			= std::unordered_map< Node, unsigned, hashNode >;
using ItOpen 			= std::pair< typename PriorityQueue::iterator, \
									typename std::set< Node >::iterator >;
using Solution			= std::list<unsigned>;

using SearchFunc		= Solution (*)(Node &, IHeuristic *);

struct optArgs
{
	std::string src_file;
	std::string trg_file;
	std::string	heuristic;
	std::string	searchfunc;
};

void		options(int argc, char ** argv, optArgs * opts);

void		setOptions(optArgs * opts, IHeuristic ** h, SearchFunc * f);

void 		printOptions(optArgs * opts);

Solution	ASearch(Node & src, IHeuristic * h);

#endif
