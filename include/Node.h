/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:06:09 by astripeb          #+#    #+#             */
/*   Updated: 2020/10/07 22:38:43 by aks              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

#include <string>
#include <cstddef>

using t_tile	= unsigned short;
using t_move	= unsigned char;

class Manhattan;
class LinearConflict;
class OptimalH;

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
**	In success return true, else false
**
*/

class Node
{
private:
	t_tile *		field = nullptr;
	unsigned		score = 0;
	t_tile			zero = 0;
	t_move			move = NONE;
	static size_t	side_;
	static size_t	length_;
public:
	/*
	** CONSTRUCTORS AND DESTRUCTORS
	*/
	Node() = default;
	explicit Node(t_tile side);
	Node(Node const & src);
	Node(Node && src) noexcept ;
	~Node();

	/*
	** OPERATORS
	*/
	Node &			operator=(Node const & src);
	Node &			operator=(Node && src) noexcept ;
	t_tile &		operator()(size_t i, size_t j);
	t_tile 			operator()(size_t i, size_t j) const;
	bool			operator==(Node const & n) const;
	bool			operator!=(Node const & n) const;
	bool			operator<(Node const & n) const;
	explicit		operator bool();

	/*
	** SETTERS AND GETTERS
	*/
	unsigned		getScore() const;
	t_tile			getZero() const;
	t_move			getMove() const;
	t_move &		getMove();
	t_tile *		getField() const;
	static unsigned	getSide() { return side_; };
	void			setZero();
	void 			printNode() const;
	size_t			getHash() const;
private:
	friend class	Manhattan;
	friend class	LinearConflict;
	friend class	OptimalH;
	friend bool		up(Node & src);
	friend bool		down(Node & src);
	friend bool		left(Node & src);
	friend bool		right(Node & src);
	void 			swap(Node & src);
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
**	On success return side of Puzzle
**	On error throw Exception
*/

size_t		readPuzzle(std::string & filename, Node & node);

#endif
