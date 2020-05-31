/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:06:09 by astripeb          #+#    #+#             */
/*   Updated: 2020/06/01 00:02:37 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

#include <string>
#include <cstddef>

using t_tile	= unsigned short;
using t_move	= unsigned char;

enum {
	NONE,
	UP,
	DOWN,
	RIGHT,
	LEFT
};

/*
**	NODE
**
**	field - board state
**	(1D array, use as 2D array Node(i,j) == field(i * side + j)
**
**	score - heuristic score
**	zero - position of empty tile in board state
**	move - last move applied to the board
**
**	up, down, left, right - moves tile in pos zero
**	In success returt true, else false
**
*/

class Node
{
public:
	t_tile *		field = nullptr;
	unsigned		score = 0;
	t_tile			zero = 0;
	t_move			move = NONE;
	Node(void);
	Node(t_tile side);
	Node(Node const & src);
	Node(Node && src);
	~Node();
	Node &			operator=(Node const & src);
	Node &			operator=(Node && src);
	t_tile &		operator()(size_t i, size_t j);
	t_tile 			operator()(size_t i, size_t j) const;
	bool			operator==(Node const & n) const;
	bool			operator!=(Node const & n) const;
	bool			operator<(Node const & n) const;
	explicit		operator bool(void);
	static unsigned	getSide(void) { return side_; };
	unsigned		getScore(void) const;
	void 			printNode(void) const;
	friend bool		up(Node & src);
	friend bool		down(Node & src);
	friend bool		left(Node & src);
	friend bool		right(Node & src);
private:
	friend class 	hashNode;
	static size_t	side_;
	static size_t	length_;
	void 			swap(Node & src);
	size_t			getHash(void) const;
};

using move_func = bool (*)(Node &);

/*
**	HASHNODE
**	for STL's unordered_map/unordered_set
*/

class hashNode {
public:
	size_t operator()(Node const & puzzle) const
	{
		return puzzle.getHash();
	}
};

/*
**	Read puzzle from filename to Node
**	On succes return side of Puzzle
**	On error throw Exception
*/

size_t		readPuzzle(std::string & filename, Node & node);

/*
**	Generate snail board state. Example for side == 3:
**		1 2 3
**		8 0	4
**		7 6 5
*/

Node		snail(int side);

/*
**	Checks if it possible solve the puzzle
**	from source board state to target
*/

bool 		solvable(Node & src, Node & trg);

#endif
