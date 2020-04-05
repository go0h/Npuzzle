/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Npuzzle.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 19:51:21 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/05 17:25:05 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_H
# define NPUZZLE_H

#include <iostream>
#include <list>

using solution = std::list<MOVE>;
using move_func = bool (*)(Node &);


bool 		up(Node & puzzle);

bool 		down(Node & puzzle);

bool 		right(Node & puzzle);

bool 		left(Node & puzzle);

solution	Search(Node & src);

void		printMoves(Node src, solution & movSet);

#endif
