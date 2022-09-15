/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   map.hpp                                           :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: nfaivre <nfaivre@student.42.fr>           +#+  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2022/09/15 13:13:33 by nfaivre          #+#    #+#              */
/*   Updated: 2022/09/15 13:13:33 by nfaivre         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "rbt.hpp"
# include "utility.hpp"
# include <memory>

namespace ft
{
	template< class Key, class Value, class Allocator = std::allocator< ft::pair<Key, Value> > >
	class map
	{

	private:

		tree<Key, Value, Allocator>	_data;


	public:

		map(void) {};

		Value	&operator[](Key key)
		{
			if (!_data.search(key))
				_data.push(ft::make_pair<Key, Value>(key, Value ()));
			return ((_data.search(key))->getValueRef());
		}

	};
}
