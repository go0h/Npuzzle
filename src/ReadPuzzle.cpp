/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadPuzzle.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 19:50:58 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/05 12:33:26 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <exception>
#include <sstream>
#include <unordered_set>

#include "Node.h"
#include "PuzzExcept.h"

size_t	g_side = DEFAULT_SIDE;
size_t	g_length = (DEFAULT_SIDE * DEFAULT_SIDE);

static bool solvable(Node const & puzzle)
{
	size_t	sum = 0;

	for (size_t i = 0; i != g_length; ++i) {
		for (size_t j = i + 1; j != g_length; ++j) {
			if (puzzle.field[i] && puzzle.field[j]) {
				if (puzzle.field[i] > puzzle.field[j])
					sum++;
			}
		}
	}
	return (sum + ((puzzle.zero / g_side) + 1)) % 2 == 0;
}

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
	std::unordered_set<CELL> order;
	order.reserve(g_length);

	for (size_t i = 0; i != g_side && !pfile.eof(); ++i) {
		std::istringstream strStream(str);
		for (size_t j = 0; j != g_side && !strStream.eof(); ++j) {
			strStream >> puzzle(i, j);
			if (strStream.fail())
				return false;
			if (puzzle(i, j) == 0)
				puzzle.zero = i * g_side + j;
			order.insert(puzzle(i, j));
		}
		if (!strStream.eof() && (strStream >> str) && str[0] != '#')
			return false;
		getline(pfile, str, '\n');
	}
	for (size_t i = 0; i != g_length; ++i) {
		if (order.find(i) == order.end())
			return false;
	}
	return order.size() == g_length;
}

Node		readPuzzle(char * filename)
{
	std::string		str;
	std::ifstream	pfile(filename);

	if (!pfile.is_open())
		throw PuzzExcept(E_OPEN_FILE);

	if (!(g_side = getFieldSize(pfile, str)))
		throw PuzzExcept(E_SIDE);
	g_length = g_side * g_side;

	Node			puzzle(g_side);
	if (!fillField(pfile, str, puzzle))
		throw PuzzExcept(E_FIELD_COM);
	skipComments(pfile, str);

	if (!pfile.eof())
		throw PuzzExcept(E_MAP);
	pfile.close();
	if (!solvable(puzzle))
		throw PuzzExcept(E_UNSOLVBL);
	return puzzle;
}
