/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:06:09 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/15 18:06:24 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H
#include <cstddef>

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
	unsigned			zero = 0;
	unsigned			score = 0;
	t_move				move = NONE;
	CELL *				field = nullptr;
	Node(void);
	Node(CELL side);								//constructor
	Node(Node const & src);							//copy constructor
	Node(Node && src);								//move constructor
	~Node();										//destructor
	Node &		operator=(Node const & src);
	Node &		operator=(Node && src);
	CELL &		operator()(size_t i, size_t j);
	CELL 		operator()(size_t i, size_t j) const;
	void		createField(size_t side);
	// unsigned	getScore(bool again);
	void 		printNode(void) const;
	void 		validate(void);

private:
	void swap(Node & src);
};

using move_func = bool (*)(Node &);

class hashNode {
public:
	size_t operator()(Node const & puzzle) const;
};

bool		operator==(Node const & n1, Node const & n2);

bool		operator!=(Node const & n1, Node const & n2);

bool		operator<(Node const & n1, Node const & n2);

size_t 		readPuzzle(char * filename, Node & node);

bool 		up(Node & puzzle);

bool 		down(Node & puzzle);

bool 		right(Node & puzzle);

bool 		left(Node & puzzle);

#endif
