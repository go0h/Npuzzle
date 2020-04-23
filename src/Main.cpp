/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:37:29 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/23 19:29:44 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PuzzExcept.h"
#include "Npuzzle.h"

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
		if (opts.trg_file != "")
			readPuzzle(opts.trg_file, trg);
		h->init(src, trg);
		src.printNode();
		// printf("size = %lu\n", sizeof(src));
		Solution solution = searchFunc(src, *h);
		// if (solution.empty())
		// 	std::cout << "Empty\n";
		if (trg && !checkSolution(src, trg, solution))
			std::cout << "Bad moves!" << std::endl;
		std::cout << "Moves: " << solution.size() << std::endl;
	} catch (PuzzExcept & err) {
		std::cerr << err.what() << std::endl;
	} catch (...) {
		std::cerr << "Something go wrong" << std::endl;
	}
	delete h;
	return EXIT_SUCCESS;
}
