/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Npuzzle.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 19:51:21 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/23 21:51:17 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_H
# define NPUZZLE_H

#include <cstddef>
#include <iostream>
#include <list>

#include "Node.h"
#include "Heuristic.h"

#define COST 1

using Solution			= std::list<unsigned>;
using SearchFunc		= Solution (*)(Node &, IHeuristic &);

struct optArgs
{
	std::string src_file;
	std::string trg_file;
	std::string	heuristic;
	std::string	searchfunc;
};

void		options(int argc, char ** argv, optArgs * opts);

void		setOptions(optArgs * opts, IHeuristic ** h, SearchFunc * f);

Solution	ASearch(Node & src, IHeuristic & h);

Solution	IDASearch(Node & root, IHeuristic & h);

Solution	GreedySearch(Node & src, IHeuristic & getScore);

void		undo(Node & node, size_t i);

void 		printOptions(optArgs * opts);

bool 		checkSolution(Node & src, Node & target, Solution & moves);

#endif
