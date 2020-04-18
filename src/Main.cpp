/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:37:29 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/18 20:14:30 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PuzzExcept.h"
#include "Npuzzle.h"

int main(int argc, char ** argv)
{
	Node			src;
	IHeuristic		* h = new OptimalH();

	if (argc != 2)
	{
		std::cout << "Usage: ./Npuzzle filename\n";
		return EXIT_FAILURE;
	}
	try {
		src = readPuzzle(argv[1]);
		h->init(Node::getSide(), 0);
		src.printNode();
		Solution solution = ASearch(src, h);
		if (solution.empty())
			std::cout << "Empty\n";
		std::cout << "Moves: " << solution.size() << std::endl;
	} catch (PuzzExcept & err) {
		std::cout << err.what() << std::endl;
	} catch (...) {
		std::cout << "Something go wrong" << std::endl;
	}
	delete h;
	return EXIT_SUCCESS;
}
