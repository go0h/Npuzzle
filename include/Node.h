/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:06:09 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/10 21:04:08 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H
#include <cstddef>

# define DEFAULT_SIDE	4

using CELL =			unsigned;
using t_move = 			unsigned char;

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
	unsigned short		zero = 0;
	t_move				move = NONE;
	unsigned			score = 0;
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
	unsigned	getScore(void);
	void 		printNode(void) noexcept;
	void 		validate(void);

private:
	void swap(Node & src);
};

class hashNode {
public:
	size_t operator()(Node const & puzzle) const;
};

bool		operator==(Node const & n1, Node const & n2);

bool		operator!=(Node const & n1, Node const & n2);

bool		operator<(Node const & n1, Node const & n2);

Node 		readPuzzle(char * filename);

#endif
