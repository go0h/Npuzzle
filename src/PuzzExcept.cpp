/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PuzzExcept.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 18:03:13 by astripeb          #+#    #+#             */
/*   Updated: 2020/04/02 20:21:30 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PuzzExcept.h"

PuzzExcept::PuzzExcept(const std::string & err)
{
	error_ = "Error: " + err;
}

std::string PuzzExcept::what() noexcept {
	return error_;
}
