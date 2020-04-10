/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:37:29 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/10 20:22:16 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.h"
#include "PuzzExcept.h"
#include "Npuzzle.h"

int main(int argc, char ** argv)
{
	Node node;

	if (argc != 2)
	{
		std::cout << "Usage: ./Npuzzle filename\n";
		return EXIT_FAILURE;
	}
	try {
		node = readPuzzle(argv[1]);
		node.printNode();
		solution Solution = Search(node);
		if (Solution.empty())
		{
			std::cout << "Empty\n";
		}
		// else
		// {
		// 	printMoves(node, Solution);
		// }
		std::cout << "Moves: " << Solution.size() << std::endl;
	} catch (PuzzExcept & err) {
		std::cout << err.what() << std::endl;
	} catch (...) {
		std::cout << "Something go wrong" << std::endl;
	}
	return EXIT_SUCCESS;
}
