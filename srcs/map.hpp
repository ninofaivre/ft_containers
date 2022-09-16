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
# include <functional>

namespace ft
{
	template< class Key, class T, class Compare = std::less< Key >, class Allocator = std::allocator< ft::pair<const Key, T> > >
	class map
	{

	public:

		typedef Key			key_type;
		typedef T			mapped_type;
		typedef Compare		key_compare;
		typedef Allocator	allocator_type;

		typedef typename ft::pair<const key_type, mapped_type>	value_type;
		typedef typename allocator_type::size_type				size_type;
		typedef typename allocator_type::difference_type		difference_type;

		typedef value_type &	reference;
		typedef const reference	const_reference;

		typedef typename allocator_type::pointer	pointer;
		typedef const pointer						const_pointer;


	private:

		tree<value_type, key_compare, allocator_type>	_data;


	public:

		static int _bstMapComp(value_type a, value_type b)
		{
			key_compare	c;
			if (!c(a.first, b.first) && !c(b.first, a.first))
				return (0);
			else
				return (c(a.first, b.first) ? -1 : 1);
		}

		map(void)
		: _data(tree<value_type, key_compare, allocator_type> (&_bstMapComp)) {};

		mapped_type	&operator[](Key key)
		{
			if (!_data.search(ft::make_pair(key, mapped_type ())))
				_data.push(ft::make_pair(key, mapped_type ()));
			return ((_data.search(ft::make_pair(key, mapped_type ()))->getData()).second);
		}

	};

}
