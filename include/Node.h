/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:06:09 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/17 20:16:29 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H
#include <cstddef>

#define DEFAULT_SIZE 4
#define DEFAULT_LENGTH (DEFAULT_SIZE * DEFAULT_SIZE)

using CELL 		= unsigned;
using t_move 	= unsigned char;

enum {
	NONE,
	UP,
	DOWN,
	RIGHT,
	LEFT
};

class Node
{
public:
	unsigned		zero = 0;
	unsigned		score = 0;
	t_move			move = NONE;
	CELL *			field = nullptr;
	Node(void);
	Node(CELL side);								//constructor
	Node(Node const & src);							//copy constructor
	Node(Node && src);								//move constructor
	~Node();										//destructor
	Node &		operator=(Node const & src);
	Node &		operator=(Node && src);
	CELL &		operator()(size_t i, size_t j);
	CELL 		operator()(size_t i, size_t j) const;
	bool		operator==(Node const & n) const;
	bool		operator!=(Node const & n) const;
	bool		operator<(Node const & n) const;
	unsigned	getScore(bool again);
	void 		printNode(void) const;
	friend bool	up(Node & src);
	friend bool	down(Node & src);
	friend bool	left(Node & src);
	friend bool	right(Node & src);
private:
	friend class 	hashNode;
	static size_t	side_;
	static size_t	length_;
	void 			swap(Node & src);
	size_t			getHash(void) const;
};

using move_func = bool (*)(Node &);

class hashNode {
public:
	size_t operator()(Node const & puzzle) const
	{
		return puzzle.getHash();
	}
};

Node		readPuzzle(char * filename);

#endif
