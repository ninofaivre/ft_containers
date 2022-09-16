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
		
		typedef rbtIterator<value_type, allocator_type>	iterator;


	private:

		rbt<value_type, key_compare, allocator_type>	_data;

		static bool	_rbtMapComp(value_type a, value_type b)
		{
			key_compare	c;
			return (c(a.first, b.first));
		}


	public:
		
		map(void)
		: _data(rbt<value_type, key_compare, allocator_type> (_rbtMapComp)) {};

		mapped_type	&operator[](const Key &key)
		{
			if (!_data.search(ft::make_pair(key, mapped_type ())))
				_data.push(ft::make_pair(key, mapped_type ()));
			return ((_data.search(ft::make_pair(key, mapped_type ()))->getData()).second);
		}

		size_type	size(void) const
		{ return (_data.getSize()); }

		bool	empty(void) const
		{ return (!this->size()); }

		iterator	begin(void)
		{ return (_data.getIterator(_data.min())); }

	};

}
