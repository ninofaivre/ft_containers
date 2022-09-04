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

# include "vectorIterator.hpp"
# include "utils.hpp"
# include "type_traits.hpp"
# include "algorithm.hpp"

# include <memory>
# include <iostream>
# include <limits>

# define VIterator typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type

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

		typedef vectorIterator<value_type>				iterator;
		typedef vectorIterator<const value_type>		const_iterator;
		typedef std::reverse_iterator<iterator>			reverse_iterator;
		typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
	

	private:

		allocator_type	_allocator;
		pointer			_data;
		size_type		_size;
		size_type		_capacity;


	public:

		// Member Functions
		explicit vector(const allocator_type	&alloc = allocator_type ())
		: _allocator(alloc), _data(NULL), _size(0), _capacity(0) {}

		explicit vector(size_type n, const_reference val = value_type (),
						const allocator_type &alloc = allocator_type ())
		: _allocator(alloc), _size(n), _capacity(n)
		{
			_data = _size ? _allocator.allocate(_size) : NULL;
			for (size_type i = 0; i < _size; i++)
				_allocator.construct(_data + i, val);
		}

		template<class InputIt>
		vector(VIterator first, InputIt last,
			   const allocator_type &alloc = allocator_type ())
		: _allocator(alloc), _size(ft::distance(first, last)),
		  _capacity(ft::distance(first, last))
		{
			_data = _size ? _allocator.allocate(_size) : NULL;
			for (size_type i = 0; i < _size; i++, first++)
				_allocator.construct(_data + i, *first);
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

		void	assign(size_type count, const_reference value)
		{
			this->clear();
			this->reserve(count);
			for (size_type i = 0; i < count; i++)
				_allocator.construct(_data + i, value);
			_size = count;
		}

		template <class InputIt>
		void	assign(VIterator first, InputIt last)
		{
			this->clear();
			this->reserve(ft::distance(first, last));
			_size = ft::distance(first, last);
			for (size_type i = 0; first != last; i++, first++)
				_allocator.construct(_data + i, *first);
		}

		// Operators
		vector	&operator=(const vector &cpy)
		{
			this->assign(cpy.begin(), cpy.end());
			return (*this);
		}

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
				throw std::out_of_range(std::string("vector::_M_range_check: __n (which is ") + to_string(pos) + std::string(") >= this->size() (which is " + to_string(pos) + ")"));
			return (_data[pos]);
		}

		const_reference	at(size_type pos) const
		{
			if (!(pos < _size))
				throw std::out_of_range(std::string("vector::_M_range_check: __n (which is ") + to_string(pos) + std::string(") >= this->size() (which is " + to_string(pos) + ")"));	
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

		pointer	data(void)
		{ return (_data); }

		const pointer	data(void) const
		{ return (_data); }

		// Capacity
		bool	empty(void) const
		{ return (_size == 0); }

		size_type	size(void) const
		{ return (_size); }

		size_type	max_size(void) const
		{ return (_allocator.max_size()); }

		void	reserve(size_type new_cap)
		{
			if (new_cap < _capacity)
				return ;
			if (new_cap > this->max_size())
				throw std::length_error("vector::reserve");
			pointer	newData = _allocator.allocate(new_cap);
			for (size_type i = 0; i < _size; i++)
			{
				_allocator.construct(newData + i, _data[i]);
				_allocator.destroy(_data + i);
			}
			_allocator.deallocate(_data, _capacity);
			_data = newData;
			_capacity = new_cap;
		}

		size_type	capacity(void) const
		{ return (_capacity); }

		// Modifiers

		void	swap(vector &otherInst)
		{
			ft::swap<allocator_type>(_allocator, otherInst._allocator);
			ft::swap<pointer>(_data, otherInst._data);
			ft::swap<size_type>(_size, otherInst._size);
			ft::swap<size_type>(_capacity, otherInst._capacity);
		}

		void	clear(void)
		{ this->erase(this->begin(), this->end()); }

		iterator		erase(iterator pos)
		{
			if (!_size || pos >= this->end())
				return (this->end());
			_allocator.destroy(pos.operator->());
			for (iterator cpyPos = pos + 1; cpyPos != this->end(); cpyPos++)
				*(cpyPos - 1) = *cpyPos;
			_size--;
			return (pos);
		}

		iterator	erase(iterator first, iterator last)
		{
			if (!_size || first >= this->end() || first >= last)
				return (this->end());
			iterator oldEnd = this->end();
			for (iterator cpyFirst = first; cpyFirst != last && cpyFirst != oldEnd;
				 _size--, cpyFirst++)
				_allocator.destroy(cpyFirst.operator->());
			for (iterator cpyFirst = first; last < oldEnd; cpyFirst++, last++)
				 *cpyFirst = *last;
			return (first);
		}

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

		void	resize(size_type count, const_reference value = value_type ())
		{
			if (count < _size)
				this->erase((this->begin() + count), this->end());
			else if (count > _size)
			{
				this->reserve(count);
				for (size_type i = 0; i < (count - _size); i++)
					_allocator.construct((this->end() + i).operator->(), value);
				_size = count;
			}
		}

		iterator	insert(iterator pos, const_reference value)
		{
			size_type	ipos = pos - this->begin();
			if (!(_capacity - _size))
				reserve(_capacity ? _capacity * 2 : 1);
			pos = this->begin() + ipos;
			for (iterator end = this->end(); end != pos; end--)
				*end = *(end - 1);
			_allocator.construct(pos.operator->(), value);
			_size++;
			return (pos);
		}

		void	insert(iterator pos, size_type count, const_reference value)
		{
			size_type	ipos = pos - this->begin();
			if (_capacity < _size + count)
			{
				if (_capacity * 2 > _size + count)
					reserve(_capacity * 2);
				else
					reserve(_size + count);
			}
			pos = this->begin() + ipos;
			for (iterator end = this->end(); end != pos; end--)
				*(end + count - 1) = *(end - 1);
			_size += count;
			while (count--)
				_allocator.construct(pos.operator->() + count, value);
		}

		template<class InputIt>
		void	insert(iterator pos, VIterator first, InputIt last)
		{
			size_type	ipos = pos - this->begin();
			if (_capacity < _size + ft::distance(first, last))
			{
				if (_capacity * 2 > _size + ft::distance(first, last))
					reserve(_capacity * 2);
				else
					reserve(_size + ft::distance(first, last));
			}
			pos = this->begin() + ipos;
			for (iterator end = this->end(); end != pos; end--)
				*(end + ft::distance(first, last) - 1) = *(end - 1);
			_size += ft::distance(first, last);
			for (; first != last; first++, pos++)
				_allocator.construct(pos.operator->(), *first);
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
		{ return (reverse_iterator (this->end())); }

		const_reverse_iterator	rbegin(void) const
		{ return (const_reverse_iterator (this->end())); }

		reverse_iterator	rend(void)
		{ return  (reverse_iterator (this->begin())); }

		const_reverse_iterator	rend(void) const
		{ return  (const_reverse_iterator (this->begin())); }

	};

	template<class T, class Alloc>
	void	swap(vector<T, Alloc> &a, vector<T, Alloc> &b)
	{ a.swap(b); }
}
