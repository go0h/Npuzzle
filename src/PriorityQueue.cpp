/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PriorityQueue.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 22:33:14 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/06 08:42:08 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PriorityQueue.h"

void 		PriorityQueue::push(Node const & src)
{
	auto	it = queue.begin();
	size_t	score = src.getScore();
	for (; it != queue.end(); ++it)
	{
		if (score < (*it).getScore()) {
			queue.insert(it, src);
			return ;
		}
	}
	if (queue.empty() || it == queue.end())
		queue.push_back(src);
}


Node		PriorityQueue::pop(void)
{
	Node temp = *(queue.begin());
	queue.pop_front();
	return temp;
}

using iterator = std::list<Node>::iterator;

iterator 	PriorityQueue::find(Node const & src)
{
	for (auto it = queue.begin(); it != queue.end(); ++it)
	{
		if (src == *(it))
			return it;
	}
	return queue.end();
}

iterator	PriorityQueue::begin(void)
{
	return queue.begin();
}

iterator	PriorityQueue::end(void)
{
	return queue.end();
}

bool 		PriorityQueue::empty(void)
{
	return queue.empty();
}

void		PriorityQueue::remove(iterator & it)
{
	queue.erase(it);
}
