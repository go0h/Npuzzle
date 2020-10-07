/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heuristic.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 21:38:16 by astripeb          #+#    #+#             */
/*   Updated: 2020/05/31 20:36:31 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "Node.h"

/*
** BASE CLASS FOR ALL HEURISTICS
**
**	side if puzzle board
**	length = side * side
**	operator "()" return the score of heuristic
*/

class IHeuristic
{
protected:
	size_t side_	= 0;
	size_t length_	= 0;
public:
	IHeuristic() = default;
	virtual ~IHeuristic() = default;
	virtual void		init(Node & src, Node & trg) = 0;
	virtual unsigned	operator()(Node & src) = 0;
};

/*
**	MANHATTAN
**	count manhattan distance for each tile
**
**	rowCur[i] - tile's row in current state
**	rowCur[i] - tile's column in current state
**
**	target - target board
**	rowTrg[i] - tile's row in target state
**	rowTrg[i] - tile's column in target state
*/

class Manhattan : public IHeuristic
{
protected:
	unsigned *	rowCur = nullptr;
	unsigned *	colCur = nullptr;
	t_tile *	target = nullptr;
	unsigned *	rowTrg = nullptr;
	unsigned *	colTrg = nullptr;

	virtual	void		initialStates(t_tile * field, unsigned * columnFields, unsigned * rowFields);
public:
	Manhattan() = default;
	~Manhattan() override;
	void		init(Node & src, Node & trg) override;
	unsigned	operator()(Node & src) override;
};

/*
**	LINEAR CONFLICT HEURISTIC addition to Manhattan heuristic
**	count each pair in row or column, who stands in their row or column,
**	but not in his position
**
**	line - conflicts in row/column
*/

class LinearConflict : public Manhattan
{
protected:
	unsigned *	line_ = nullptr;	// количество конфликтов в ряду/колонке
	unsigned			rowConflicts(const t_tile * field);
	unsigned			colConflicts(const t_tile * field);
public:
	LinearConflict() = default;;
	~LinearConflict() override;
	void		init(Node & src, Node & trg) override;
	unsigned	operator()(Node & src) override;
};

/*
**	OPTIMAL HEURISTIC
**	Include linear conflict, Manhattan distance,
**	and two new heuristics:
**	CORNERS CONFLICT HEURISTIC and LAST MOVE
*/

class OptimalH : public LinearConflict
{
public:
	OptimalH() = default;;
	~OptimalH() override = default;;
	void		init(Node & src, Node & trg) override;
	unsigned	operator()(Node & src) override;
};

#endif
