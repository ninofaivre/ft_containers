/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+      */
/*   By: nfaivre <nfaivre@student.42.fr>           +#+  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2022/08/25 12:12:15 by nfaivre          #+#    #+#              */
/*   Updated: 2022/08/25 12:58:46 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <sstream>

template <typename T>
std::string	to_string(T value)
{
	std::ostringstream	stream;

	stream << value;
	return (stream.str());
}

