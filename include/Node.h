/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:06:09 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/23 19:19:31 by astripeb         ###   ########.fr       */
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

class Node
{
public:
	t_tile *		field = nullptr;
	unsigned		score = 0;
	t_tile			zero = 0;
	t_move			move = NONE;
	Node(void);
	Node(t_tile side);								//constructor
	Node(Node const & src);							//copy constructor
	Node(Node && src);								//move constructor
	~Node();										//destructor
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

class hashNode {
public:
	size_t operator()(Node const & puzzle) const
	{
		return puzzle.getHash();
	}
};

class CompareNode
{
public:
    bool operator() (Node const & n1, Node const & n2) const
    {
		return n2 < n1;
    }
};

size_t		readPuzzle(std::string & filename, Node & node);

#endif
