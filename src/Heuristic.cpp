/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heuristic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 22:19:56 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/15 20:32:54 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Heuristic.h"

CELL * genSample(size_t side)
{
	CELL * field = new CELL[side * side];

	for (CELL i = 0; i != (side * side) - 1; ++i)
	{
		field[i] = i + 1;
	}
	return field;
}

void		ManhattanNode::initialStates(CELL * field, int * col, int * row)
{
	for (size_t i = 0; i != g_length; ++i)
	{
		if (field[i])
		{
			row[i] = (field[i] - 1) / g_side;
			col[i] = (field[i] - 1) % g_side;
		}
		else
		{
			row[i] = field[i];
			col[i] = field[i];
		}
	}
}

// #include <iostream>

// void		printField(int * field, size_t side)
// {
// 	for (size_t i = 0; i != side; ++i)
// 	{
// 		for (size_t j = 0; j != side; ++j)
// 			printf("%-3u ", field[i * side + j]);
// 		printf("\n");
// 	}
// 	printf("\n");
// }

void ManhattanNode::init(size_t side)
{
	g_side = side;
	g_length = side * side;

	rowCur = new int[g_length];
	colCur = new int[g_length];
	rowTrg = new int[g_length];
	colTrg = new int[g_length];
	line = new int[g_side];

	CELL * sample = genSample(g_side);

	initialStates(sample, colTrg, rowTrg);
	delete [] sample;
}

ManhattanNode::~ManhattanNode()
{
	delete [] line;
	delete [] rowCur;
	delete [] colCur;
	delete [] rowTrg;
	delete [] colTrg;
}
