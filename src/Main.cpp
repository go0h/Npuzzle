/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:37:29 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/17 13:05:59 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PuzzExcept.h"
#include "Npuzzle.h"

size_t g_length	= DEFAULT_LENGTH;
size_t g_side 	= DEFAULT_SIZE;

int main(int argc, char ** argv)
{
	Node			src;

	if (argc != 2)
	{
		std::cout << "Usage: ./Npuzzle filename\n";
		return EXIT_FAILURE;
	}

	try {
		g_side = readPuzzle(argv[1], src);
		g_length = g_side * g_side;
		src.printNode();
		Solution solution = ASearch(src);
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
