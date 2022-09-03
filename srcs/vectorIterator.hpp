/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   vectorIterator.hpp                                :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: nfaivre <nfaivre@student.42.fr>           +#+  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2022/09/02 12:12:41 by nfaivre          #+#    #+#              */
/*   Updated: 2022/09/02 12:12:41 by nfaivre         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "vectorConstIterator.hpp"
# include "utils.hpp"

template<class T>
class vectorConstIterator;

template<class T>
class vectorIterator
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

	vectorIterator<value_type>(pointer ptr = NULL)
	: _ptr(ptr) {}

	vectorIterator<value_type>(const vectorIterator<value_type> &cpy)
	: _ptr(cpy._ptr) {}

	reference	operator*(void) const
	{ return (*_ptr); }

	pointer		operator->(void) const
	{ return (_ptr); }

	vectorIterator<value_type>	&operator++(void)
	{
		_ptr++;
		return (*this);
	}

	vectorIterator<value_type>	operator++(int)
	{
		vectorIterator<value_type> tmp = *this;
		++_ptr;
		return (tmp);
	}

	vectorIterator<value_type>	&operator--(void)
	{
		_ptr--;
		return (*this);
	}

	vectorIterator<value_type>	operator--(int)
	{
		vectorIterator<value_type> tmp = *this;
		--_ptr;
		return (tmp);
	}

	vectorIterator<value_type>	&operator+=(const int n)
	{
		_ptr += n;
		return (*this);
	}

	vectorIterator<value_type>	&operator-=(const int n)
	{
		_ptr -= n;
		return (*this);
	}

	reference				operator[](std::size_t index)
	{ return (_ptr[index]); }

};

typedef std::ptrdiff_t	difference_type;

template<class T>
bool	operator==(const vectorIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return (getPtr(lhs) == getPtr(rhs)); }

template<class T>
bool	operator==(const vectorIterator<T> &lhs, const vectorConstIterator<T> &rhs)
{ return (getPtr(lhs) == getPtr(rhs)); }

template<class T>
bool	operator!=(const vectorIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return (getPtr(lhs) != getPtr(rhs)); }

template<class T>
bool	operator!=(const vectorIterator<T> &lhs, const vectorConstIterator<T> &rhs)
{ return (getPtr(lhs) != getPtr(rhs)); }

template<class T>
bool	operator<(const vectorIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return (getPtr(lhs) < getPtr(rhs)); }

template<class T>
bool	operator<(const vectorIterator<T> &lhs, const vectorConstIterator<T> &rhs)
{ return (getPtr(lhs) < getPtr(rhs)); }

template<class T>
bool	operator<=(const vectorIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return (getPtr(lhs) <= getPtr(rhs)); }

template<class T>
bool	operator<=(const vectorIterator<T> &lhs, const vectorConstIterator<T> &rhs)
{ return (getPtr(lhs) <= getPtr(rhs)); }

template<class T>
bool	operator>(const vectorIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return (getPtr(lhs) > getPtr(rhs)); }

template<class T>
bool	operator>(const vectorIterator<T> &lhs, const vectorConstIterator<T> &rhs)
{ return (getPtr(lhs) > getPtr(rhs)); }

template<class T>
bool	operator>=(const vectorIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return (getPtr(lhs) >= getPtr(rhs)); }

template<class T>
bool	operator>=(const vectorIterator<T> &lhs, const vectorConstIterator<T> &rhs)
{ return (getPtr(lhs) >= getPtr(rhs)); }

template<class T>
vectorIterator<T>	operator+(const int lhs, const vectorIterator<T> &rhs)
{ return (vectorIterator<T> (lhs + getPtr(rhs))); }

template<class T>
vectorIterator<T>	operator+(const vectorIterator<T> &lhs, const int rhs)
{ return (vectorIterator<T> (getPtr(lhs) + rhs)); }

template<class T>
difference_type	operator+(const vectorIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return(getPtr(lhs) + getPtr(rhs)); }

template<class T>
difference_type	operator+(const vectorIterator<T> &lhs, const vectorConstIterator<T> &rhs)
{ return(getPtr(lhs) + getPtr(rhs)); }

template<class T>
vectorIterator<T>	operator-(const int lhs, const vectorIterator<T> &rhs)
{ return (vectorIterator<T> (lhs - getPtr(rhs))); }

template<class T>
vectorIterator<T>	operator-(const vectorIterator<T> &lhs, const int rhs)
{ return (vectorIterator<T> (getPtr(lhs) - rhs)); }

template<class T>
difference_type	operator-(const vectorIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return(getPtr(lhs) - getPtr(rhs)); }

template<class T>
difference_type	operator-(const vectorIterator<T> &lhs, const vectorConstIterator<T> &rhs)
{ return(getPtr(lhs) - getPtr(rhs)); }
