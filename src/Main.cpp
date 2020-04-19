/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:37:29 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/19 22:24:43 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PuzzExcept.h"
#include "Npuzzle.h"
#include <getopt.h>


int main(int argc, char ** argv)
{
	optArgs			opts;
	Node			src, trg;
	IHeuristic * 	h = nullptr;
	SearchFunc		searchFunc = nullptr;

	try {
		options(argc, argv, &opts);
		// printOptions(&opts);
		setOptions(&opts, &h, &searchFunc);

		readPuzzle(opts.src_file, src);
		if (trg)
			readPuzzle(opts.trg_file, trg);
		h->init(src, trg);
		src.printNode();
		Solution solution = searchFunc(src, h);
		if (solution.empty())
			std::cout << "Empty\n";
		std::cout << "Moves: " << solution.size() << std::endl;
	} catch (PuzzExcept & err) {
		std::cout << err.what() << std::endl;
	} catch (...) {
		std::cout << "Something go wrong" << std::endl;
	}
	return EXIT_SUCCESS;
}
