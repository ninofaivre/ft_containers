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
class vectorIterator
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

	pointer		base(void) const
	{ return (_ptr); }

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

template<class L, class R>
bool	operator==(const vectorIterator<L> &lhs, const vectorIterator<R> &rhs)
{ return (lhs.base() == rhs.base()); }

template<class L, class R>
bool	operator!=(const vectorIterator<L> &lhs, const vectorIterator<R> &rhs)
{ return (lhs.base() != rhs.base()); }

template<class L, class R>
bool	operator<(const vectorIterator<L> &lhs, const vectorIterator<R> &rhs)
{ return (lhs.base() < rhs.base()); }

template<class L, class R>
bool	operator<=(const vectorIterator<L> &lhs, const vectorIterator<R> &rhs)
{ return (lhs.base() <= rhs.base()); }

template<class L, class R>
bool	operator>(const vectorIterator<L> &lhs, const vectorIterator<R> &rhs)
{ return (lhs.base() > rhs.base()); }

template<class L, class R>
bool	operator>=(const vectorIterator<L> &lhs, const vectorIterator<R> &rhs)
{ return (lhs.base() >= rhs.base()); }

template<class T>
vectorIterator<T>	operator+(const difference_type lhs, const vectorIterator<T> &rhs)
{ return (vectorIterator<T> (lhs + rhs.base())); }

template<class T>
vectorIterator<T>	operator+(const vectorIterator<T> &lhs, const difference_type rhs)
{ return (vectorIterator<T> (lhs.base() + rhs)); }

template<class T>
vectorIterator<T>	operator-(const vectorIterator<T> &lhs, const difference_type rhs)
{ return (vectorIterator<T> (lhs.base() - rhs)); }

template<class L, class R>
difference_type	operator-(const vectorIterator<L> &lhs, const vectorIterator<R> &rhs)
{ return(lhs.base() - rhs.base()); }
