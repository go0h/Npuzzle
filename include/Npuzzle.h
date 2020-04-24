/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Npuzzle.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 19:51:21 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/24 11:50:39 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_H
# define NPUZZLE_H

#include <cstddef>
#include <chrono>
#include <iostream>
#include <list>

#include "Node.h"
#include "Heuristic.h"

#define COST 1

struct optArgs
{
	std::string src_file;
	std::string trg_file;
	std::string	heuristic = "OPT";
	std::string	searchfunc = "A";
	bool		printpath = false;
};

struct marks
{
	// Total number of states ever selected in the "opened" set
	size_t compl_time = 0;

	// Maximum number of states ever represented in memory
	// at the same timeduring the search
	size_t compl_size = 0;

	// start time
	std::chrono::time_point<std::chrono::system_clock> t1;

	// end time
	std::chrono::time_point<std::chrono::system_clock> t2;

	// search func name
	std::string func;
};

using Solution			= std::list<unsigned>;
using SearchFunc		= Solution (*)(Node &, IHeuristic &, marks &);

void		options(int argc, char ** argv, optArgs * opts);

void		setOptions(optArgs * opts, IHeuristic ** h, SearchFunc * f);

Solution	AStarSearch(Node & src, IHeuristic & h, marks & bench);

Solution	IDAStarSearch(Node & src, IHeuristic & h, marks & bench);

Solution	GreedySearch(Node & src, IHeuristic & h, marks & bench);

void		undo(Node & node, size_t i);

void 		printMoves(Node & src, Solution & movSet, bool printmoves);

void 		printBenchmarks(marks & bench, IHeuristic & h, size_t moves);

void 		printOptions(optArgs * opts);

bool 		checkSolution(Node & src, Node & target, Solution & moves);

#endif
