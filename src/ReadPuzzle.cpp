/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadPuzzle.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 19:50:58 by astripeb          #+#    #+#             */
/*   Updated: 2020/06/02 14:20:23 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <exception>
#include <sstream>
#include <unordered_set>

#include "Node.h"
#include "PuzzExcept.h"

static void		skipComments(std::ifstream & puzzleFile, std::string & str)
{
	while (!puzzleFile.eof())
	{
		getline(puzzleFile, str, '\n');
		if (str[0] != '#')
			break ;
	}
}

static size_t	getFieldSize(std::ifstream & puzzleFile, std::string & str)
{
	size_t	size = 0;

	skipComments(puzzleFile, str);
	std::istringstream strStream(str);
	strStream >> size;
	if (strStream.fail() || (!strStream.eof() && (strStream >> str) && str[0] != '#'))
		return 0;
	skipComments(puzzleFile, str);
	return size;
}

static bool		fillField(std::ifstream & puzzleFile, std::string & str, \
					Node & puzzle, size_t side)
{
	std::unordered_set<t_tile> order;
	order.reserve(side * side);

	for (size_t i = 0; i != side && !puzzleFile.eof(); ++i)
	{
		std::istringstream strStream(str);
		for (size_t j = 0; j != side && !strStream.eof(); ++j)
		{
			strStream >> puzzle(i, j);
			if (strStream.fail())
				return false;
			order.insert(puzzle(i, j));
		}
		if (!strStream.eof() && (strStream >> str) && str[0] != '#')
			return false;
		getline(puzzleFile, str, '\n');
	}
	for (size_t i = 0; i != side * side; ++i)
	{
		if (order.find(i) == order.end())
			return false;
	}
	return order.size() == side * side;
}

size_t			readPuzzle(std::string & filename, Node & node)
{
	std::string		str;
	std::ifstream	puzzleFile(filename);
	size_t			side;

	if (!puzzleFile.is_open())
		throw PuzzExcept(E_OPEN_FILE);

	if ((side = getFieldSize(puzzleFile, str)) < 3)
		throw PuzzExcept(E_SIDE);

	if (Node::getSide() && Node::getSide() != side)
		throw PuzzExcept(E_SAME_SIDE);

	Node	temp(side);
	if (!fillField(puzzleFile, str, temp, side))
		throw PuzzExcept(E_FIELD_COM);
	skipComments(puzzleFile, str);

	if (!puzzleFile.eof())
		throw PuzzExcept(E_MAP);
	puzzleFile.close();
	node = temp;
	node.setZero();
	return side;
}
