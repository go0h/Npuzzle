/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:37:29 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/03 21:24:28 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.h"
#include "PuzzExcept.h"
#include "Npuzzle.h"

int main(int argc, char ** argv)
{
	Node node;

	if (argc != 2) {
		std::cout << "Usage: ./Npuzzle filename\n";
		return EXIT_FAILURE;
	}
	try {
		node = readPuzzle(argv[1]);
		node.printNode();
		std::list<int> Solution = Search(node);
		if (Solution.empty())
			std::cout << "Empty\n";
	} catch (PuzzExcept & err) {
		std::cout << err.what() << std::endl;
	} catch (...) {
		std::cout << "Something go wrong" << std::endl;
	}
	return EXIT_SUCCESS;
}
