/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:06:09 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/03 21:48:24 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H
#include <cstddef>

# define CELL unsigned

struct Node
{
public:
	CELL	side;
	CELL	length;
	CELL	zero;
	CELL *	field;
	Node(void);
	Node(CELL side);
	explicit Node(char const **str, CELL side);		//constructor
	Node(Node const & src);							//copy constructor
	Node(Node && src);								//move constructor
	~Node();										//destructor
	Node &	operator=(Node const & src);
	Node &	operator=(Node && src);
	CELL & operator()(size_t i, size_t j);
	CELL operator()(size_t i, size_t j) const;
	void 	printNode(void) noexcept;
	void 	validate(void);

private:
	void swap(Node & src);
};

bool		operator==(Node const & n1, Node const & n2);

bool		operator!=(Node const & n1, Node const & n2);

bool		operator<(Node const & n1, Node const & n2);

Node 		readPuzzle(char * filename);

CELL		manhattanScore(Node const & src);

bool 		up(Node & puzzle);

bool 		down(Node & puzzle);

bool 		right(Node & puzzle);

bool 		left(Node & puzzle);


#endif
