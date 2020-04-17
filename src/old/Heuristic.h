/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heuristic.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 21:38:16 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/17 20:22:01 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "Node.h"

class ManhattanNode
{
	static size_t side_;
	static size_t length_;


	int *	line = nullptr;		// количество конфликтов в ряду/колонке

	// номера рядов и колонок для текущего состояния пазла
	int *	rowCur = nullptr;	// номер ряда в котором должна быть ячейка
	int *	colCur = nullptr;	// номер колонки в которой должна быть ячейка

	// номера рядов и колонок для конечного состояния пазла
	int *	rowTrg = nullptr;	// номер ряда в котором должна быть ячейка
	int *	colTrg = nullptr;	// номер колонки в которой должна быть ячейка

	void		initialStates(CELL * field, int * col, int * row);
	unsigned 	linearConflict2(CELL * field);

public:
	ManhattanNode(void) { }
	~ManhattanNode();
	void init(size_t side);
	unsigned operator()(Node & src);
};

#endif
