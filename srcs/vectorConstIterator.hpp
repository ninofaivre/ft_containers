/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   vectorIterator.hpp                           :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: nfaivre <nfaivre@student.42.fr>           +#+  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2022/09/02 13:13:10 by nfaivre          #+#    #+#              */
/*   Updated: 2022/09/02 13:13:10 by nfaivre         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "vectorIterator.hpp"
# include "utils.hpp"

template<class T>
class vectorIterator;

template<class T>
class vectorConstIterator
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

	vectorConstIterator<T>(pointer ptr = NULL)
	: _ptr(ptr) {}

	vectorConstIterator<T>(const vectorConstIterator<T> &cpy)
	: _ptr(cpy._ptr) {}

	vectorConstIterator<T>(const vectorIterator<T> &cpy)
	: _ptr(getPtr(cpy)) {}

	reference	operator*(void) const
	{ return (*_ptr); }

	pointer		operator->(void) const
	{ return (_ptr); }

	vectorConstIterator<T>	operator++(void)
	{
		_ptr++;
		return (*this);
	}

	vectorConstIterator<T>	operator++(int)
	{
		vectorConstIterator<T> tmp = *this;
		++_ptr;
		return (tmp);
	}

	vectorConstIterator<T>	&operator--(void)
	{
		_ptr--;
		return (*this);
	}

	vectorConstIterator<T>	operator--(int)
	{
		vectorConstIterator<T> vectorIterator = *this;
		--_ptr;
		return (vectorIterator);
	}

	vectorConstIterator<T>	&operator+=(const int n)
	{
		_ptr += n;
		return (*this);
	}

	vectorConstIterator<T>	&operator-=(const int n)
	{
		_ptr -= n;
		return (*this);
	}

	reference				operator[](std::size_t index)
	{ return (_ptr[index]); }

};

typedef std::ptrdiff_t	difference_type;

template<class T>
bool	operator==(const vectorConstIterator<T> &lhs, const vectorConstIterator<T> &rhs)
{ return (getPtr(lhs) == getPtr(rhs)); }

template<class T>
bool	operator==(const vectorConstIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return (getPtr(lhs) == getPtr(rhs)); }

template<class T>
bool	operator!=(const vectorConstIterator<T> &lhs, const vectorConstIterator<T> &rhs)
{ return (getPtr(lhs) != getPtr(rhs)); }

template<class T>
bool	operator!=(const vectorConstIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return (getPtr(lhs) != getPtr(rhs)); }

template<class T>
bool	operator<(const vectorConstIterator<T> &lhs, const vectorConstIterator<T> &rhs)
{ return (getPtr(lhs) < getPtr(rhs)); }

template<class T>
bool	operator<(const vectorConstIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return (getPtr(lhs) < getPtr(rhs)); }

template<class T>
bool	operator<=(const vectorConstIterator<T> &lhs, const vectorConstIterator<T> &rhs)
{ return (getPtr(lhs) <= getPtr(rhs)); }

template<class T>
bool	operator<=(const vectorConstIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return (getPtr(lhs) <= getPtr(rhs)); }

template<class T>
bool	operator>(const vectorConstIterator<T> &lhs, const vectorConstIterator<T> &rhs)
{ return (getPtr(lhs) > getPtr(rhs)); }

template<class T>
bool	operator>(const vectorConstIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return (getPtr(lhs) > getPtr(rhs)); }

template<class T>
bool	operator>=(const vectorConstIterator<T> &lhs, const vectorConstIterator<T> &rhs)
{ return (getPtr(lhs) >= getPtr(rhs)); }

template<class T>
bool	operator>=(const vectorConstIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return (getPtr(lhs) >= getPtr(rhs)); }

template<class T>
vectorConstIterator<T>	operator+(const int lhs, const vectorConstIterator<T> &rhs)
{ return (vectorConstIterator<T> (lhs + getPtr(rhs))); }

template<class T>
vectorConstIterator<T>	operator+(const vectorConstIterator<T> &lhs, const int rhs)
{ return (vectorConstIterator<T> (getPtr(lhs) + rhs)); }

template<class T>
difference_type	operator+(const vectorConstIterator<T> &lhs,
						  const vectorConstIterator<T> &rhs)
{ return(getPtr(lhs) + getPtr(rhs)); }

template<class T>
difference_type	operator+(const vectorConstIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return(getPtr(lhs) + getPtr(rhs)); }

template<class T>
vectorConstIterator<T>	operator-(const int lhs, const vectorConstIterator<T> &rhs)
{ return (vectorConstIterator<T> (lhs - getPtr(rhs))); }

template<class T>
vectorConstIterator<T>	operator-(const vectorConstIterator<T> &lhs, const int rhs)
{ return (vectorConstIterator<T> (getPtr(lhs) - rhs)); }

template<class T>
difference_type	operator-(const vectorConstIterator<T> &lhs,
						  const vectorConstIterator<T> &rhs)
{ return(getPtr(lhs) - getPtr(rhs)); }

template<class T>
difference_type	operator-(const vectorConstIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return(getPtr(lhs) - getPtr(rhs)); }
