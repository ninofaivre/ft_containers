/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+      */
/*   By: nfaivre <nfaivre@student.42.fr>           +#+  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2022/08/23 13:13:59 by nfaivre          #+#    #+#              */
/*   Updated: 2022/08/25 23:45:24 by nfaivre          ###   ########.fr       */
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

			~vector(void)
			{
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(_data + i);
				_allocator.deallocate(_data, _capacity);
			}

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
			{ return (std::numeric_limits<difference_type>::max()); }

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

	};
}
