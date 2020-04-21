/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 14:02:22 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/20 19:49:01 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <getopt.h>
#include <cstring>

#include "Npuzzle.h"
#include "PuzzExcept.h"

void options(int argc, char ** argv, optArgs * opts)
{
	char shortOpt[] = "h:t:H:a";
	static struct option longOpt[] = {
		{"help", 0, 0, 'h'},
		{"target", 1, 0, 't'},
		{"heurisctic", 1, 0, 'H'},
		{"algo", 1, 0, 'a'},
		{0, 0, 0, 0}
	};
	int optidx, c = 0;

	if (argc == 1)
		throw PuzzExcept(USAGE);

	opts->src_file = argv[1];
	opts->searchfunc = "A";
	opts->heuristic = "OPT";
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
			if (opts->heuristic != "M" && opts->heuristic != "LC"
			&& opts->heuristic != "OPT")
				throw PuzzExcept(true);
		}
		else if (c == 'a')
			opts->searchfunc = optarg;
	}
}


void	setOptions(optArgs * opts, IHeuristic ** h, SearchFunc * f)
{
	if (opts->heuristic == "M")
		*h = new Manhattan();
	else if (opts->heuristic == "LC")
		*h = new LinearConflict();
	else if (opts->heuristic == "OPT")
		*h = new OptimalH();

	if (opts->searchfunc == "A")
		*f = &ASearch;
	else if (opts->searchfunc == "IDA")
		*f = &ASearch; // because it is not made
}

void printOptions(optArgs * opts)
{
	std::cout << "Src_file:		" << opts->src_file << std::endl;
	if (opts->trg_file != "")
		std::cout << "Trg_file:		" << opts->trg_file << std::endl;
	std::cout << "Heuristic:	" << opts->heuristic << std::endl;
	std::cout << "Search func:	" << opts->searchfunc << std::endl;
}
