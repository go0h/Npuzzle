/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 14:02:22 by astripeb          #+#    #+#             */
/*   Updated: 2020/06/01 22:59:19 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <getopt.h>
#include <cstring>
#include <typeinfo>
#include <unordered_map>

#include "Npuzzle.h"
#include "PuzzExcept.h"

extern move_func	g_move[];

using	std::cout;
using	std::endl;

void	options(int argc, char ** argv, optArgs * opts)
{
	char shortOpt[] = "a:hpt:H:";
	struct option longOpt[] = {
		{"help", 0, 0, 'h'},
		{"target", 1, 0, 't'},
		{"heurisctic", 1, 0, 'H'},
		{"algo", 1, 0, 'a'},
		{"print", 0, 0, 'p'},
		{0, 0, 0, 0}
	};
	int optidx, c = 0;

	if (argc == 1)
		throw PuzzExcept(USAGE);

	opts->src_file = argv[1];
	while(true)
	{
		if ((c = getopt_long(argc, argv, shortOpt, longOpt, &optidx)) == -1)
			break ;
		if (c == 'h')
			throw PuzzExcept(true);
		else if (c == 't')
			opts->trg_file = optarg;
		else if (c == 'H')
		{
			opts->heuristic = optarg;
			if (opts->heuristic != "M" && opts->heuristic != "LC" \
			&& opts->heuristic != "OPT")
				throw PuzzExcept(true);
		}
		else if (c == 'a')
			opts->searchfunc = optarg;
		else if (c == 'p')
			opts->printpath = true;
		else
			throw PuzzExcept(USAGE);
	}
}

void	setOptions(optArgs * opts, HeurPtr & h, SearchFunc * f)
{
	std::unordered_map<std::string, SearchFunc> funcMap = {
		{"A", &AStarSearch},
		{"IDA", &IDAStarSearch},
		{"G", &GreedySearch}
	};
	std::unordered_map< std::string, HeurPtr > heurMap =
	{
		{"M", std::shared_ptr<IHeuristic>(new Manhattan())},
		{"LC", std::shared_ptr<IHeuristic>(new LinearConflict())},
		{"OPT", std::shared_ptr<IHeuristic>(new OptimalH())}
	};

	if (heurMap.find(opts->heuristic) != heurMap.end())
		h = heurMap[opts->heuristic];
	else
		throw PuzzExcept(USAGE);

	if (funcMap.find(opts->searchfunc) != funcMap.end())
		*f = funcMap[opts->searchfunc];
	else
		throw PuzzExcept(USAGE);
}

void 	printMoves(Node & src, Solution & movSet, bool printmoves)
{
	unsigned i = 1;

	cout << "Start state:" << endl;
	src.printNode();
	for (auto it = movSet.begin(); it != std::prev(movSet.end()); ++i, ++it)
	{
		g_move[*it](src);
		if (printmoves)
		{
			cout << "Step #" << i << endl;
			src.printNode();
		}
	}
	if (movSet.size())
		g_move[*std::prev(movSet.end())](src);
	cout << "Final state:" << endl;
	src.printNode();
}

void	printBenchmarks(marks & bench, IHeuristic & h, size_t moves)
{
	cout.setf(std::ios::fixed);
	cout.precision(5);
	double seconds = std::chrono::duration_cast<std::chrono::milliseconds>
		(bench.t2 - bench.t1).count() / 1000.0;

	cout << "Heuristic:       " << typeid(h).name() << endl;
	cout << "Search function: " << bench.func << std::endl;
	cout << "Time:            " << seconds << " sec" <<  endl;
	cout << "Time per node:   " << seconds / bench.compl_size << " sec" << endl;
	cout << "Time complexity: " << bench.compl_time << endl;
	cout << "Size complexity: " << bench.compl_size << endl;
	cout << "Moves:           " << moves << endl;
}
