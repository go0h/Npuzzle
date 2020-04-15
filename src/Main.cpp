/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:37:29 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/15 20:22:53 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PuzzExcept.h"
#include "Npuzzle.h"

size_t g_length	= DEFAULT_LENGTH;
size_t g_side 	= DEFAULT_SIZE;

int main(int argc, char ** argv)
{
	Node			src;
	ManhattanNode 	heuristic;

	if (argc != 2)
	{
		std::cout << "Usage: ./Npuzzle filename\n";
		return EXIT_FAILURE;
	}

	try {
		g_side = readPuzzle(argv[1], src);
		src.printNode();
		heuristic.init(g_side);
		Solution solution = ASearch(src, heuristic);
		if (solution.empty())
		{
			std::cout << "Empty\n";
		}
		std::cout << "Moves: " << solution.size() << std::endl;
	} catch (PuzzExcept & err) {
		std::cout << err.what() << std::endl;
	} catch (...) {
		std::cout << "Something go wrong" << std::endl;
	}
	return EXIT_SUCCESS;
}
