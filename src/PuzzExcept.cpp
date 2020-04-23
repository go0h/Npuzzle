/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PuzzExcept.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 18:03:13 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/23 21:42:18 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PuzzExcept.h"

PuzzExcept::PuzzExcept(const std::string & err)
{
	error_ = "Error: " + err;
}

PuzzExcept::PuzzExcept(int usage)
{
	if (usage)
	{
		error_ += "Usage: ./Npuzzle puzzle_file [OPTION]... [FILE]...\n\n";
		error_ += "\t-h, --help\t\t\tdisplay this help and exit\n\n";
		error_ += "\t-t, --target <target_file>\tfinal state of puzzle\n\n";
		error_ += "\t-H, --heuristic heuristic_method:\n";
		error_ += "\t   [M]   - only Manhattan distance between t_tiles\n";
		error_ += "\t   [LC]  - Manhattan distance and Linear conflicts\n";
		error_ += "\t   [OPT] - Optimal (M + LC + Corners + Last move)\n\n";
		error_ += "\t-a, --algo algorithm:\n";
		error_ += "\t   [A]   - for A* algorithm\n";
		error_ += "\t   [IDA] - for Iterative A* algorithm\n";
		error_ += "\t   [G]   - for Greedy algorithm\n";
	}
}


std::string PuzzExcept::what() noexcept
{
	return error_;
}
