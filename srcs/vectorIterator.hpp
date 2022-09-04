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

# include "iterator.hpp"

template<class T>
class vectorIterator : public ft::iterator_traits<T *>
{

public:

	typedef typename ft::iterator_traits<T *>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<T *>::value_type		value_type;
	typedef typename ft::iterator_traits<T *>::difference_type	difference_type;
	typedef typename ft::iterator_traits<T *>::pointer			pointer;
	typedef typename ft::iterator_traits<T *>::reference		reference;

private:

	pointer	_ptr;


public:

	vectorIterator(pointer ptr = NULL)
	: _ptr(ptr) {}

	vectorIterator(const vectorIterator &cpy)
	: _ptr(cpy._ptr) {}

	operator	vectorIterator<const T>() const
	{ return (vectorIterator<const T>(_ptr)); }

	reference	operator*(void) const
	{ return (*_ptr); }

	pointer		operator->(void) const
	{ return (_ptr); }

	vectorIterator	operator++(void)
	{
		_ptr++;
		return (*this);
	}

	vectorIterator	operator++(int)
	{
		vectorIterator tmp = *this;
		++_ptr;
		return (tmp);
	}

	vectorIterator	&operator--(void)
	{
		_ptr--;
		return (*this);
	}

	vectorIterator	operator--(int)
	{
		vectorIterator tmp = *this;
		--_ptr;
		return (tmp);
	}

	vectorIterator	&operator+=(const int n)
	{
		_ptr += n;
		return (*this);
	}

	vectorIterator	&operator-=(const int n)
	{
		_ptr -= n;
		return (*this);
	}

	reference				operator[](std::size_t index) const
	{ return (_ptr[index]); }

};

typedef std::ptrdiff_t	difference_type;

template<class Iterator>
static typename Iterator::pointer	getPtr(Iterator it)
{ return (it.operator->()); }

template<class T>
bool	operator==(const vectorIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return (getPtr(lhs) == getPtr(rhs)); }

template<class L, class R>
bool	operator==(const vectorIterator<L> &lhs, const vectorIterator<R> &rhs)
{ return (getPtr(lhs) == getPtr(rhs)); }

template<class T>
bool	operator!=(const vectorIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return (getPtr(lhs) != getPtr(rhs)); }

template<class L, class R>
bool	operator!=(const vectorIterator<L> &lhs, const vectorIterator<R> &rhs)
{ return (getPtr(lhs) != getPtr(rhs)); }

template<class T>
bool	operator<(const vectorIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return (getPtr(lhs) < getPtr(rhs)); }

template<class L, class R>
bool	operator<(const vectorIterator<L> &lhs, const vectorIterator<R> &rhs)
{ return (getPtr(lhs) < getPtr(rhs)); }

template<class T>
bool	operator<=(const vectorIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return (getPtr(lhs) <= getPtr(rhs)); }

template<class L, class R>
bool	operator<=(const vectorIterator<L> &lhs, const vectorIterator<R> &rhs)
{ return (getPtr(lhs) <= getPtr(rhs)); }

template<class T>
bool	operator>(const vectorIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return (getPtr(lhs) > getPtr(rhs)); }

template<class L, class R>
bool	operator>(const vectorIterator<L> &lhs, const vectorIterator<R> &rhs)
{ return (getPtr(lhs) > getPtr(rhs)); }

template<class T>
bool	operator>=(const vectorIterator<T> &lhs, const vectorIterator<T> &rhs)
{ return (getPtr(lhs) >= getPtr(rhs)); }

template<class L, class R>
bool	operator>=(const vectorIterator<L> &lhs, const vectorIterator<R> &rhs)
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

template<class L, class R>
difference_type	operator+(const vectorIterator<L> &lhs, const vectorIterator<R> &rhs)
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

template<class L, class R>
difference_type	operator-(const vectorIterator<L> &lhs, const vectorIterator<R> &rhs)
{ return(getPtr(lhs) - getPtr(rhs)); }
