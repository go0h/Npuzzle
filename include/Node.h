/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:06:09 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/05 22:14:28 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H
#include <cstddef>

# define CELL			unsigned
# define DEFAULT_SIDE	4

typedef	enum {
	NONE,
	UP,
	DOWN,
	RIGHT,
	LEFT
} MOVE;

class Node
{
public:
	CELL		zero = 0;
	MOVE		move = NONE;
	unsigned	depth = 0;
	CELL *		field = nullptr;
	Node(void);
	Node(CELL side);								//constructor
	Node(Node const & src);							//copy constructor
	Node(Node && src);								//move constructor
	~Node();										//destructor
	Node &	operator=(Node const & src);
	Node &	operator=(Node && src);
	CELL & operator()(size_t i, size_t j);
	CELL operator()(size_t i, size_t j) const;
	size_t	getScore(void) const;
	void 	printNode(void) noexcept;
	void 	validate(void);

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
