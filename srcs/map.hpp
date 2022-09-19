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
# include "iterator.hpp"
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
		
		typedef rbtIterator<value_type, key_compare, allocator_type>	iterator;
		typedef rbtIterator<const value_type, key_compare, allocator_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>	reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;


	private:

		rbt<value_type, key_compare, allocator_type>	_data;

		static bool	_rbtMapComp(value_type a, value_type b, const key_compare &c)
		{ return (c(a.first, b.first)); }
		
		value_type	_keyToPair(const Key &key)
		{ return (ft::make_pair(key, mapped_type ())); }


	public:
		
		map(const key_compare &comp = key_compare ())
		: _data(rbt<value_type, key_compare, allocator_type> (_rbtMapComp, comp)) {};

		mapped_type	&operator[](const Key &key)
		{
			if (!_data.search(ft::make_pair(key, mapped_type ())))
				_data.push(ft::make_pair(key, mapped_type ()));
			return ((_data.search(ft::make_pair(key, mapped_type ()))->getData()).second);
		}

		size_type	size(void) const
		{ return (_data.getSize()); }

		iterator	find(const key_type &key)
		{ return (_data.getIt(_data.search(key))); }

		const_iterator	find(const key_type &key) const
		{ return (_data.getIt(_data.search(_keyToPair(key)))); }

		size_type	count(const key_type &key) const
		{ return (_data.count(_keyToPair(key)))}

		bool	empty(void) const
		{ return (!this->size()); }

		iterator	upper_bound(const key_type &key)
		{ return (_data.getIt(_data.upper_bound(_keyToPair(key)))); }

		const_iterator	upper_bound(const key_type &key) const
		{ return (_data.getIt(_data.upper_bound(_keyToPair(key)))); }

		iterator	lower_bound(const key_type &key)
		{ return (_data.getIt(_data.lower_bound(_keyToPair(key)))); }

		const_iterator	lower_bound(const key_type &key) const
		{ return (_data.getIt(_data.lower_bound(_keyToPair(key)))); }

		ft::pair<iterator, iterator>	equal_range(const key_type &key)
		{ return (ft::make_pair(this->lower_bound(), this->upper_bound())); }

		ft::pair<const_iterator, const_iterator>	equal_range(const key_type &key) const
		{ return (ft::make_pair(this->lower_bound(), this->upper_bound())); }

		iterator	begin(void)
		{ return (_data.getIt(_data.min())); }

		iterator	end(void)
		{ return (++(_data.getIt(_data.max()))); }

	};

}
