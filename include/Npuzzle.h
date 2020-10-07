/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Npuzzle.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 19:51:21 by astripeb          #+#    #+#             */
/*   Updated: 2020/05/31 23:55:46 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_H
# define NPUZZLE_H

#include <cstddef>
#include <chrono>
#include <iostream>
#include <list>
#include <memory>

#include "Node.h"
#include "Heuristic.h"

#define COST 1

struct optArgs
{
	std::string src_file;
	std::string trg_file;
	std::string	heuristic = "OPT";
	std::string	searchFunc = "A";
	bool		printPath = false;
};

/*
**	MARKS
**	timeComplexity - Total number of states ever selected in the "opened" set
**	sizeComplexity - Maximum number of states ever represented in memory
**	at the same time during the search
**
**	t1 - start time
**	t2 - end time
**
**	func - search func name
*/

struct marks
{
	size_t timeComplexity = 0;
	size_t sizeComplexity = 0;
	std::chrono::time_point<std::chrono::system_clock> t1;
	std::chrono::time_point<std::chrono::system_clock> t2;
	std::string func;
};

using HeurPtr			= std::shared_ptr<IHeuristic>;

using Solution			= std::list<unsigned>;
using SearchFunc		= Solution (*)(Node &, IHeuristic &, marks &);

void		options(int argc, char ** argv, optArgs * opts);

void		setOptions(optArgs * opts, HeurPtr & h, SearchFunc * f);

Solution	AStarSearch(Node & src, IHeuristic & h, marks & bench);

Solution	IDAStarSearch(Node & src, IHeuristic & h, marks & bench);

Solution	GreedySearch(Node & src, IHeuristic & h, marks & bench);

void		undo(Node & node, size_t i);

void 		printMoves(Node & src, Solution & movSet, bool printMove);

void 		printBenchmarks(marks & bench, IHeuristic & h, size_t moves);

void 		printOptions(optArgs * opts);

bool 		checkSolution(Node & src, Node & target, Solution & moves);

#endif
