/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heuristic.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 21:38:16 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/23 19:37:09 by astripeb         ###   ########.fr       */
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
	size_t side_	= 0;
	size_t length_	= 0;
public:
	IHeuristic() {};
	virtual ~IHeuristic() {};
	virtual void		init(Node & src, Node & trg) = 0;
	virtual unsigned	operator()(Node & src) = 0;
};

class Manhattan : public IHeuristic
{
protected:
	// номера рядов и колонок для текущего состояния пазла
	unsigned *	rowCur = nullptr;	// номер ряда в котором должна быть ячейка
	unsigned *	colCur = nullptr;	// номер колонки в которой должна быть ячейка

	//конечное состояние
	t_tile *	target = nullptr;
	// номера рядов и колонок для конечного состояния пазла
	unsigned *	rowTrg = nullptr;	// номер ряда в котором должна быть ячейка
	unsigned *	colTrg = nullptr;	// номер колонки в которой должна быть ячейка

	virtual	void		initialStates(t_tile * field, unsigned * col, unsigned * row);
public:
	Manhattan(void) { }
	virtual ~Manhattan();
	virtual void		init(Node & src, Node & trg);
	virtual unsigned	operator()(Node & src);
};


class LinearConflict : public Manhattan
{
protected:
	unsigned *	line_ = nullptr;		// количество конфликтов в ряду/колонке
public:
	LinearConflict(void) { };
	~LinearConflict(void);
	virtual void		init(Node & src, Node & trg);
	virtual unsigned	operator()(Node & src);
	unsigned				rowConflicts(t_tile * field);
	unsigned				colConflicts(t_tile * field);
};

class OptimalH : public LinearConflict
{
public:
	OptimalH(void) { };
	virtual ~OptimalH() { };
	virtual void		init(Node & src, Node & trg);
	virtual unsigned	operator()(Node & src);
};

#endif
