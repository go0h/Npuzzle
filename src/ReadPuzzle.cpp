/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadPuzzle.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 19:50:58 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/22 17:22:40 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <exception>
#include <sstream>
#include <unordered_set>

#include "Node.h"
#include "PuzzExcept.h"

static bool 	solvable(Node const & puzzle, size_t side, size_t length)
{
	size_t	sum = 0;

	for (size_t i = 0; i != length; ++i)
	{
		for (size_t j = i + 1; j != length; ++j)
		{
			if (puzzle.field[i] && puzzle.field[j])
			{
				if (puzzle.field[i] > puzzle.field[j])
					sum++;
			}
		}
	}
	return (sum + ((puzzle.zero / side) + 1)) % 2 == 0;
}

static void		skipComments(std::ifstream & pfile, std::string & str)
{
	while (!pfile.eof())
	{
		getline(pfile, str, '\n');
		if (str[0] != '#')
			break ;
	}
}

static size_t	getFieldSize(std::ifstream & pfile, std::string & str)
{
	size_t	size = 0;

	skipComments(pfile, str);
	std::istringstream strStream(str);
	strStream >> size;
	if (strStream.fail() || (!strStream.eof() && (strStream >> str) && str[0] != '#'))
		return 0;
	skipComments(pfile, str);
	return size;
}

static bool		fillField(std::ifstream & pfile, std::string & str, \
					Node & puzzle, size_t side)
{
	std::unordered_set<t_tile> order;
	order.reserve(side * side);
	int n;

	for (size_t i = 0; i != side && !pfile.eof(); ++i)
	{
		std::istringstream strStream(str);
		for (size_t j = 0; j != side && !strStream.eof(); ++j)
		{
			strStream >> n;
			puzzle(i, j) = n;
			if (strStream.fail())
				return false;
			if (puzzle(i, j) == 0)
				puzzle.zero = i * side + j;
			order.insert(puzzle(i, j));
		}
		if (!strStream.eof() && (strStream >> str) && str[0] != '#')
			return false;
		getline(pfile, str, '\n');
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
	std::ifstream	pfile(filename);
	size_t			side = 0;

	if (!pfile.is_open())
		throw PuzzExcept(E_OPEN_FILE);

	if (!(side = getFieldSize(pfile, str)))
		throw PuzzExcept(E_SIDE);

	if (node.getSide() && node.getSide() != side)
		throw PuzzExcept(E_SAME_SIDE);

	Node	temp(side);
	if (!fillField(pfile, str, temp, side))
		throw PuzzExcept(E_FIELD_COM);
	skipComments(pfile, str);

	if (!pfile.eof())
		throw PuzzExcept(E_MAP);
	pfile.close();
	if (!solvable(temp, side, side * side))
		throw PuzzExcept(E_UNSOLVBL);
	node = temp;
	return side;
}
