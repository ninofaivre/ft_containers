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

namespace std
{
	template <typename T>
	std::string	to_string(T value)
	{
		std::ostringstream	stream;

		stream << value;
		return (stream.str());
	}
}

namespace ft
{
	template<typename T>
	class iterator
	{

	public:

		typedef std::random_access_iterator_tag	iterator_category;

		typedef	T				value_type;
		typedef std::ptrdiff_t	difference_type;
		typedef value_type*		pointer;
		typedef value_type&		reference;
	
	private:

		pointer	_ptr;
	

	public:
	
		iterator<value_type>(pointer ptr)
		: _ptr(ptr) {}

		iterator<value_type>(const iterator<value_type> &cpy)
		: _ptr(cpy._ptr) {}

		bool		operator==(const iterator<value_type> &otherInst) const
		{ return (_ptr == otherInst._ptr); }

		bool		operator!=(const iterator<value_type> &otherInst) const
		{ return (_ptr != otherInst._ptr); }

		reference	operator*(void) const
		{ return (*_ptr); }

		pointer		operator->(void) const
		{ return (_ptr); }

		iterator<value_type>	&operator++(void)
		{
			_ptr++;
			return (*this);
		}

		iterator<value_type>	operator++(int)
		{
			iterator<value_type> tmp = *this;
			++_ptr;
			return (tmp);
		}

		iterator<value_type>	&operator--(void)
		{
			_ptr--;
			return (*this);
		}

		iterator<value_type>	operator--(int)
		{
			iterator<value_type> tmp = *this;
			--_ptr;
			return (tmp);
		}

		iterator<value_type>	operator+(const int n) const
		{ return (iterator<value_type> (_ptr + n)); }

		iterator<value_type>	operator-(const int n) const
		{ return (iterator<value_type> (_ptr - n)); }

		bool					operator<(const iterator<value_type> &otherInst) const
		{ return (_ptr < otherInst._ptr); }

		bool					operator>(const iterator<value_type> &otherInst) const
		{ return (_ptr > otherInst._ptr); }

		bool					operator<=(const iterator<value_type> &otherInst) const
		{ return (_ptr <= otherInst._ptr); }

		bool					operator>=(const iterator<value_type> &otherInst) const
		{ return (_ptr >= otherInst._ptr); }

		iterator<value_type>	&operator+=(const int n) const
		{
			_ptr += n;
			return (*this);
		}

		iterator<value_type>	&operator-=(const int n) const
		{
			_ptr -= n;
			return (*this);
		}

		reference				operator[](std::size_t index)
		{ return (_ptr[index]); }

	};

	template<typename T>
	class const_iterator
	{

	public:

		typedef std::random_access_iterator_tag	iterator_category;

		typedef	const T			value_type;
		typedef std::ptrdiff_t	difference_type;
		typedef value_type*		pointer;
		typedef value_type&		reference;
	
	private:

		pointer	_ptr;
	

	public:
	
		const_iterator<T>(pointer ptr)
		: _ptr(ptr) {}

		const_iterator<T>(const const_iterator<T> &cpy)
		: _ptr(cpy._ptr) {}

		const_iterator<T>(const iterator<T> &cpy)
		: _ptr(&(*cpy)) {}

		bool		operator==(const const_iterator<T> &otherInst) const
		{ return (_ptr == otherInst._ptr); }

		bool		operator!=(const const_iterator<T> &otherInst) const
		{ return (_ptr != otherInst._ptr); }

		reference	operator*(void) const
		{ return (*_ptr); }

		pointer		operator->(void) const
		{ return (_ptr); }

		const_iterator<T>	&operator++(void)
		{
			_ptr++;
			return (*this);
		}

		const_iterator<T>	operator++(int)
		{
			const_iterator<T> tmp = *this;
			++_ptr;
			return (tmp);
		}

		const_iterator<T>	&operator--(void)
		{
			_ptr--;
			return (*this);
		}

		const_iterator<T>	operator--(int)
		{
			const_iterator<T> tmp = *this;
			--_ptr;
			return (tmp);
		}

		const_iterator<T>	operator+(const int n) const
		{ return (const_iterator<T> (_ptr + n)); }

		const_iterator<T>	operator-(const int n) const
		{ return (const_iterator<T> (_ptr - n)); }

		bool					operator<(const const_iterator<T> &otherInst) const
		{ return (_ptr < otherInst._ptr); }

		bool					operator>(const const_iterator<T> &otherInst) const
		{ return (_ptr > otherInst._ptr); }

		bool					operator<=(const const_iterator<T> &otherInst) const
		{ return (_ptr <= otherInst._ptr); }

		bool					operator>=(const const_iterator<T> &otherInst) const
		{ return (_ptr >= otherInst._ptr); }

		const_iterator<T>	&operator+=(const int n) const
		{
			_ptr += n;
			return (*this);
		}

		const_iterator<T>	&operator-=(const int n) const
		{
			_ptr -= n;
			return (*this);
		}

		reference				operator[](std::size_t index)
		{ return (_ptr[index]); }

	};

	template<class InputIt1, class InputIt2>
	bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		while (first1 != last1)
		{
			if (*first1++ != *first2++)
				return (false);
		}
		return (true);
	}

	template<class InputIt1, class InputIt2, class BinaryPredicate>
	bool	equal(InputIt1 first1, InputIt1 last1,
				  InputIt2 first2, BinaryPredicate p)
	{
		while (first1 != last1)
		{
			if (!p(*first1++, *first2++))
				return (false);
		}
		return (true);
	}

	template<class InputIt1, class InputIt2>
	bool	lexicographical_compare (InputIt1 first1, InputIt1 last1,
									 InputIt2 first2, InputIt2 last2)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
				return (true);
			if (*first1++ > *first2++)
				return (false);
		}
		return(first1 == last1 && first2 != last2);
	}

	template<class InputIt1, class InputIt2, class Compare>
	bool	lexicographical_compare (InputIt1 first1, InputIt1 last1,
									 InputIt2 first2, InputIt2 last2,
									 Compare comp)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (com(*first1, *first2))
				return (true);
			if (comp(*first2++, *first1++))
				return (false);
		}
		return(first1 == last1 && first2 != last2);
	}
}
