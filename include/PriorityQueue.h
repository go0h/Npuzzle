/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PriorityQueue.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 22:14:02 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/05 22:56:55 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.h"
#include <list>
#include <iterator>

class PriorityQueue
{
	std::list<Node> queue;
	using iterator = std::list<Node>::iterator;

	PriorityQueue(PriorityQueue const & src);
	PriorityQueue(PriorityQueue && src);
	bool operator=(PriorityQueue const & src);
	bool operator==(PriorityQueue && src);
public:
	PriorityQueue(void) = default;
	~PriorityQueue(void) { };
	void 		push(Node const & src);
	Node		pop(void);
	iterator	find(Node const & src);
	bool 		empty(void);
	iterator	begin(void);
	iterator	end(void);
	void		remove(iterator & it);
};
