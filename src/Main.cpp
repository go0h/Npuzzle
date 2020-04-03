/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:37:29 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/03 12:00:39 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.h"
#include "PuzzExcept.h"
#include "Npuzzle.h"

int main(int argc, char ** argv)
{
	if (argc != 2) {
		std::cout << "Usage: ./Npuzzle filename\n";
		return EXIT_FAILURE;
	}
	std::cout << argv[1] << std::endl;
	try {
		Node node = readPuzzle(argv[1]);
		node.printNode();

		Node new_node = node;
		new_node.printNode();
		std::cout << std::boolalpha << (node == new_node) << std::endl;
		std::cout << std::boolalpha << (node != new_node) << std::endl;
	} catch (PuzzExcept & err) {
		std::cout << err.what() << std::endl;
	} catch (...) {
		std::cout << "Something go wrong" << std::endl;
	}
	return EXIT_SUCCESS;
}
