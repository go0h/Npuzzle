/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PuzzExcept.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 17:57:14 by astripeb          #+#    #+#             */
/*   Updated: 2020/05/29 17:55:20 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUZZEXCEPT_H
# define PUZZEXCEPT_H

#define USAGE		"Usage: ./Npuzzle puzzle_file [OPTION]... [FILE]..."
#define E_OPEN_FILE	"Can't open file"
#define E_MAP		"Wrong map"
#define E_SIDE		"Maybe you forget side of map"
#define E_FIELD_COM	"Incorrect field or comment in map"
#define E_SFIELDS	"Same fields on map"
#define E_ORDER		"Wrong map order"
#define E_INDEX		"Incorrect indexes"
#define E_UNSOLVBL	"Unsolvable puzzle"
#define E_SAME_SIDE	"Sides should be the same"

#include <exception>
#include <string>

class PuzzExcept : public std::exception
{
private:
	std::string error_;
public:
	PuzzExcept(int usage);
	PuzzExcept(const std::string & err);
	std::string what() noexcept;
};

#endif
