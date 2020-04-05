/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:37:29 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/05 11:29:22 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.h"
#include "PuzzExcept.h"
#include "Npuzzle.h"
#include <cstring>


int main(int argc, char ** argv)
{
	Node node;

	if (argc != 2) {
		std::cout << "Usage: ./Npuzzle filename\n" << argv[0];
		return EXIT_FAILURE;
	}
	try {
		node = readPuzzle(argv[1]);
		node.printNode();

		// std::cout << "Score: " << node.getScore(true) << std::endl;
		std::list<int> Solution = Search(node);
		if (Solution.empty())
			std::cout << "Empty\n";
		std::cout << "Moves: " << Solution.size() << std::endl;
	} catch (PuzzExcept & err) {
		std::cout << err.what() << std::endl;
	} catch (...) {
		std::cout << "Something go wrong" << std::endl;
	}
	return EXIT_SUCCESS;
}
