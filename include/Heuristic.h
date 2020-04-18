/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heuristic.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 21:38:16 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/18 20:28:13 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "Node.h"

/*
** BASE CLASS FOR ALL HEURISTICS
*/

class IHeuristic
{
protected:
	size_t side_	= DEFAULT_SIZE;
	size_t length_	= (DEFAULT_SIZE * DEFAULT_SIZE);


	// unsigned	linearConflict2(CELL * field);

public:
	virtual ~IHeuristic() {};
	virtual void init(size_t side, char order) = 0;
	virtual unsigned operator()(Node & src) = 0;
};

class Manhattan : public IHeuristic
{
protected:
	// номера рядов и колонок для текущего состояния пазла
	int *	rowCur = nullptr;	// номер ряда в котором должна быть ячейка
	int *	colCur = nullptr;	// номер колонки в которой должна быть ячейка

	//конечное состояние
	CELL *	target = nullptr;
	// номера рядов и колонок для конечного состояния пазла
	int *	rowTrg = nullptr;	// номер ряда в котором должна быть ячейка
	int *	colTrg = nullptr;	// номер колонки в которой должна быть ячейка

	virtual	void		initialStates(CELL * field, int * col, int * row);
public:
	Manhattan(void) { }
	virtual ~Manhattan();
	virtual void 		init(size_t side, char order = 0);
	virtual unsigned	operator()(Node & src);
};


class LinearConflict : public Manhattan
{
protected:
	int *	line = nullptr;		// количество конфликтов в ряду/колонке
public:
	LinearConflict(void) { };
	~LinearConflict(void);
	virtual void 		init(size_t side, char order = 0);
	virtual unsigned	operator()(Node & src);
	void				countRowConflict(CELL * field, int row);
	void				countColConflict(CELL * field, int row);
};

class OptimalH : public LinearConflict
{
public:
	OptimalH(void) { };
	virtual ~OptimalH() { };
	virtual void 		init(size_t side, char order = 0);
	virtual unsigned	operator()(Node & src);
};

#endif
