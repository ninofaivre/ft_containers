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
# include "algorithm.hpp"
# include <memory>
# include <functional>
# include <iostream>

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
		typedef const value_type	&const_reference;

		typedef typename allocator_type::pointer	pointer;
		typedef const pointer						const_pointer;


	private:

		class value_compare// public binary_function<value_type, value_type, bool>
		{
			friend class map;
		protected:
			key_compare comp;
			value_compare(key_compare c) : comp(c) {};
		public:
			bool	operator() (const value_type &a, const value_type &b) const
			{ return (comp(a.first, b.first)); }
		};

		typedef rbt<value_type, allocator_type, value_compare>	rbt_type;


	public:
				
		typedef typename rbt_type::iterator				iterator;
		typedef typename rbt_type::const_iterator		const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;


	private:

		rbt_type	_data;

		value_type	_keyToPair(const Key &key) const
		{ return (ft::make_pair(key, mapped_type ())); }


	public:

		explicit map(const key_compare &comp = key_compare (), const allocator_type &alloc = allocator_type ())
		: _data(rbt_type (value_compare (comp), alloc)) {}

		template <class InputIt>
		map(InputIt first, InputIt last, const key_compare &comp = key_compare (), const allocator_type &alloc = allocator_type ())
		: _data(rbt_type (value_compare (comp), alloc))
		{ this->insert(first, last); }

		map(const map &cpy)
		: _data(rbt_type (cpy._data)) {}

		map	&operator=(const map &cpy)
		{
			_data.copy(cpy._data);
			return (*this);
		}

		value_compare	value_comp(void) const
		{ return (_data.value_comp()); }

		void	swap(map &swp)
		{ this->_data.swap(swp._data); }

		size_type	max_size(void) const
		{ return (_data.max_size()); }

		key_compare	key_comp(void) const
		{ return (_data.value_comp().comp); }

		mapped_type	&operator[](const Key &key)
		{ return ((this->insert(_keyToPair(key)).first)->second); }

		mapped_type	&at(const key_type &key)
		{ return (((_data.search(_keyToPair(key)))->getData()).second); }

		const mapped_type	&at(const key_type &key) const
		{ return (((_data.search(_keyToPair(key)))->getData()).second); }

		size_type	size(void) const
		{ return (_data.getSize()); }

		iterator	find(const key_type &key)
		{ return (_data.getIt(_data.search(_keyToPair(key)))); }

		const_iterator	find(const key_type &key) const
		{ return (_data.getIt(_data.search(_keyToPair(key)))); }

		size_type	count(const key_type &key) const
		{ return (_data.count(_keyToPair(key))); }

		bool	empty(void) const
		{ return (!this->size()); }

		ft::pair<iterator, bool> insert(const value_type &value)
		{
			iterator it = _data.getIt(_data.search(value));
			if (it == this->end())
				return (ft::make_pair(_data.getIt(_data.push(value)), true));
			return (ft::make_pair(it, false));
		}

		iterator	insert(iterator hint, const value_type &value)
		{ static_cast<void> (hint); return (insert(value).first); }

		iterator	erase(iterator pos)
		{
			iterator it = pos;
			it++;
			_data.pop(*pos);
			return (it);
		}

		iterator	erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
			return (last);
		}

		size_type	erase(const key_type &key)
		{ return (_data.pop(_keyToPair(key))); }

		void	clear(void)
		{ erase(this->begin(), this->end()); }

		template<class InputIt>
		void	insert(InputIt first, InputIt last)
		{
			while (first != last)
			{
				this->insert(*first);
				first++;
			}
		}

		iterator	upper_bound(const key_type &key)
		{ return (_data.getIt(_data.upper_bound(_keyToPair(key)))); }

		const_iterator	upper_bound(const key_type &key) const
		{ return (_data.getIt(_data.upper_bound(_keyToPair(key)))); }

		iterator	lower_bound(const key_type &key)
		{ return (_data.getIt(_data.lower_bound(_keyToPair(key)))); }

		const_iterator	lower_bound(const key_type &key) const
		{ return (_data.getIt(_data.lower_bound(_keyToPair(key)))); }

		ft::pair<iterator, iterator>	equal_range(const key_type &key)
		{ return (ft::make_pair(this->lower_bound(key), this->upper_bound(key))); }

		ft::pair<const_iterator, const_iterator>	equal_range(const key_type &key) const
		{ return (ft::make_pair(this->lower_bound(key), this->upper_bound(key))); }

		iterator	begin(void)
		{ return (_data.getIt(_data.min())); }

		const_iterator	begin(void) const
		{ return (_data.getIt(_data.min())); }

		iterator	end(void)
		{ return (_data.getEnd()); }

		const_iterator	end(void) const
		{ return (_data.getEnd()); }

		reverse_iterator	rbegin(void)
		{ return (_data.getEnd()); }

		const_reverse_iterator	rbegin(void) const
		{ return (_data.getEnd()); }

		reverse_iterator	rend(void)
		{ return (_data.getIt(_data.min())); }

		const_reverse_iterator	rend(void) const
		{ return (_data.getIt(_data.min())); }

	};

	template<class Key, class T>
	bool	operator==(const map<Key, T> &lhs, const map<Key, T> &rhs)
	{ return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }

	template<class Key, class T>
	bool	operator!=(const map<Key, T> &lhs, const map<Key, T> &rhs)
	{ return (!(lhs == rhs)); }

	template<class Key, class T>
	bool	operator<(const map<Key, T> &lhs, const map<Key, T> &rhs)
	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
										  rhs.begin(), rhs.end())); }

	template<class Key, class T>
	bool	operator<=(const map<Key, T> &lhs, const map<Key, T> &rhs)
	{ return (lhs == rhs ||lhs < rhs); }

	template<class Key, class T>
	bool	operator>(const map<Key, T> &lhs, const map<Key, T> &rhs)
	{ return (!(lhs <= rhs)); }

	template<class Key, class T>
	bool	operator>=(const map<Key, T> &lhs, const map<Key, T> &rhs)
	{ return (!(lhs < rhs)); }

	template<class Key, class T>
	void	swap(map<Key, T> &lhs, map<Key, T> &rhs)
	{ lhs.swap(rhs); }

}
