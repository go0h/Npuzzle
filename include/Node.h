/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:06:09 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/02 18:15:12 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H
#include <cstddef>

# define CELL unsigned

struct Node
{
public:
	CELL side;
	CELL ** field;
	size_t zi;
	Node(void);
	Node(CELL size);
	explicit Node(char const **str, CELL side);		//constructor
	Node(Node const & src);							//copy constructor
	~Node();										//destructor
	Node & operator=(Node const & src);
	void printNode(void) noexcept;
	void validate(void);

private:
	void swap(Node & src);
};

Node readPuzzle(char * filename);

#endif
