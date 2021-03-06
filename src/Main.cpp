/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:37:29 by astripeb          #+#    #+#             */
/*   Updated: 2020/06/02 10:51:46 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PuzzExcept.h"
#include "Npuzzle.h"

int main(int argc, char ** argv)
{
	optArgs			opts;
	marks			bench;
	Node			src, trg;
	HeurPtr			h;
	SearchFunc		searchFunc = nullptr;

	try {
		options(argc, argv, &opts);
		setOptions(&opts, h, &searchFunc);

		if (!opts.src_file.empty())
			readPuzzle(opts.src_file, src);
		if (!opts.trg_file.empty())
			readPuzzle(opts.trg_file, trg);

		h->init(src, trg);
		bench.t1 = std::chrono::system_clock::now();
		Solution solution = searchFunc(src, *h, bench);

		printMoves(src, solution, opts.printPath);
		printBenchmarks(bench, *h, solution.size());
	} catch (PuzzExcept & err) {
		std::cerr << err.what() << std::endl;
	} catch (...) {
		std::cerr << "Something go wrong" << std::endl;
	}
	return EXIT_SUCCESS;
}
