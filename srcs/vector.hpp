/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+      */
/*   By: nfaivre <nfaivre@student.42.fr>           +#+  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2022/08/23 13:13:59 by nfaivre          #+#    #+#              */
/*   Updated: 2022/08/26 15:28:03 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "utils.hpp"

# include <memory>
# include <iostream>
# include <limits>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class	vector
	{

	public:

		typedef	T				value_type;
		typedef	Alloc			allocator_type;
		typedef std::size_t		size_type;
		typedef std::ptrdiff_t	difference_type;

		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef ft::iterator<value_type>				iterator;
		typedef ft::const_iterator<value_type>			const_iterator;
		typedef std::reverse_iterator<iterator>			reverse_iterator;
		typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
	

	private:

		allocator_type	_allocator;
		value_type		*_data;
		size_type		_size;
		size_type		_capacity;


	public:

		// Member Functions
		explicit vector(const allocator_type	&alloc = allocator_type ())
		: _allocator(alloc), _data(NULL), _size(0), _capacity(0) {}

		explicit vector(size_type n, const value_type &val = value_type (), const allocator_type &alloc = allocator_type ())
		: _allocator(alloc), _size(n), _capacity(n)
		{
			_data = n ? _allocator.allocate(n) : NULL;
			for (size_type i = 0; i < n; i++)
				_allocator.construct(_data + i, val);
		}

		vector(const vector &cpy)
		: _allocator(cpy._allocator), _data(NULL), _size(0), _capacity(0)
		{
			this->reserve(cpy._capacity);
			for (size_type i = 0; i < cpy._size; i++)
				this->push_back(cpy[i]);
		}

		~vector(void)
		{
			for (size_type i = 0; i < _size; i++)
				_allocator.destroy(_data + i);
			_allocator.deallocate(_data, _capacity);
		}

		// Operators
		bool	operator==(const vector &otherInst) const
		{
			if (_size != otherInst._size)
				return (false);
			return (ft::equal(this->begin(), this->end(), otherInst.begin()));
		}

		bool	operator!=(const vector &otherInst) const
		{ return (!(*this == otherInst)); }

		bool	operator<(const vector &otherInst) const
		{ return (ft::lexicographical_compare(this->begin(), this->end(),
											  otherInst.begin(), otherInst.end())); }

		bool	operator<=(const vector &otherInst) const
		{ return (*this == otherInst || *this < otherInst); }

		bool	operator>(const vector &otherInst) const
		{ return (!(*this <= otherInst)); }

		bool	operator>=(const vector &otherInst) const
		{ return (!(*this < otherInst)); }

		allocator_type	get_allocator(void) const
		{ return (_allocator); }
		
		// Element access
		reference	at(size_type pos)
		{
			if (!(pos < _size))
				throw std::out_of_range(std::string("vector::_M_range_check: __n (which is ") + std::to_string(pos) + std::string(") >= this->size() (which is 0)"));	
			return (_data[pos]);
		}

		const_reference	at(size_type pos) const
		{
			if (!(pos < _size))
				throw std::out_of_range(std::string("vector::_M_range_check: __n (which is ") + std::to_string(pos) + std::string(") >= this->size() (which is 0)"));	
			return (_data[pos]);
		}

		reference	operator[](size_type pos)
		{ return (_data[pos]); }

		const_reference	operator[](size_type pos) const
		{ return (_data[pos]); }

		reference	front(void)
		{ return (_data[0]); }

		const_reference	front(void) const
		{ return (_data[0]); }

		reference	back(void)
		{ return (_data[_size - 1]); }

		const_reference	back(void) const
		{ return (_data[_size - 1]); }

		value_type	*data(void)
		{ return (_data); }

		const value_type	*data(void) const
		{ return (_data); }

		// Capacity
		bool	empty(void) const
		{ return (_size != 0); }

		size_type	size(void) const
		{ return (_size); }

		size_type	max_size(void) const
		{ return (_allocator.max_size()); }

		void	reserve(size_type new_cap)
		{
			if (new_cap < _capacity)
				return ;
			value_type	*newData = _allocator.allocate(new_cap);
			for (size_type i = 0; i < _size; i++)
			{
				newData[i] = _data[i];
				_allocator.destroy(_data + i);
			}
			_allocator.deallocate(_data, _capacity);
			_data = newData;
			_capacity = new_cap;
		}

		size_type	capacity(void) const
		{ return (_capacity); }

		// Modifiers
		void	push_back(value_type val)
		{
			if (!(_capacity - _size))
				reserve((_capacity) ? _capacity * 2 : 1);
			_data[_size] = val;
			_size++;
		}

		void	pop_back(void)
		{
			_size--;
			_allocator.destroy(_data + _size);
		}

		// iterators
		iterator		begin(void)
		{ return (iterator (_data)); }

		const_iterator	begin(void) const
		{ return (const_iterator (_data)); }

		iterator		end(void)
		{ return (iterator (&_data[_size])); }

		const_iterator	end(void) const
		{ return (const_iterator (&_data[_size])); }

		reverse_iterator	rbegin(void)
		{ return (reverse_iterator (&_data[_size - 1])); }

		const_reverse_iterator	rbegin(void) const
		{ return (const_reverse_iterator (&_data[_size - 1])); }

		reverse_iterator	rend(void)
		{ return  (reverse_iterator (&_data[-1])); }

		const_reverse_iterator	rend(void) const
		{ return  (const_reverse_iterator (&_data[-1])); }

	};
}
