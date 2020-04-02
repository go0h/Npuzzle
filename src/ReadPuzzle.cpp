/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadPuzzle.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 19:50:58 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/02 20:16:57 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <exception>
#include <sstream>
#include <unordered_set>

#include "Node.h"
#include "PuzzExcept.h"

static void	skipComments(std::ifstream & pfile, std::string & str)
{
	while (!pfile.eof()) {
		getline(pfile, str, '\n');
		if (str[0] != '#')
			break ;
	}
}

static CELL	getFieldSize(std::ifstream & pfile, std::string & str)
{
	CELL		size = 0;

	skipComments(pfile, str);
	std::istringstream strStream(str);
	strStream >> size;
	if (strStream.fail() || (!strStream.eof() && (strStream >> str) && str[0] != '#'))
		return 0;
	skipComments(pfile, str);
	return size;
}

static bool fillField(std::ifstream & pfile, std::string & str, Node & puzzle)
{
	size_t	num = puzzle.side * puzzle.side;
	std::unordered_set<CELL> order;
	order.reserve(num);

	for (size_t i = 0; i != puzzle.side && !pfile.eof(); ++i) {
		std::istringstream strStream(str);
		for (size_t j = 0; j != puzzle.side && !strStream.eof(); ++j) {
			strStream >> puzzle.field[i][j];
			if (strStream.fail())
				return false;
			order.insert(puzzle.field[i][j]);
		}
		if (!strStream.eof() && (strStream >> str) && str[0] != '#')
			return false;
		getline(pfile, str, '\n');
	}
	for (size_t i = 0; i != num; ++i) {
		if (order.find(i) == order.end())
			return false;
	}
	return order.size() == num;
}

Node		readPuzzle(char * filename)
{
	std::string		str;
	std::ifstream	pfile(filename);
	CELL			side;

	if (!pfile.is_open())
		throw PuzzExcept(E_OPEN_FILE);

	if (!(side = getFieldSize(pfile, str)))
		throw PuzzExcept(E_SIDE);

	Node			puzzle(side);
	if (!fillField(pfile, str, puzzle))
		throw PuzzExcept(E_FIELD_COM);
	skipComments(pfile, str);

	if (!pfile.eof())
		throw PuzzExcept(E_MAP);
	pfile.close();
	return puzzle;
}
