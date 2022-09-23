/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   iterator.hpp                                      :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: nfaivre <nfaivre@student.42.fr>           +#+  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2022/09/04 18:18:44 by nfaivre          #+#    #+#              */
/*   Updated: 2022/09/04 18:18:44 by nfaivre         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : input_iterator_tag {};
	struct bidirectional_iterator_tag : forward_iterator_tag {};
	struct random_access_iterator_tag : bidirectional_iterator_tag {};

	template<class Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template<class T>
	struct iterator_traits<T *>
	{
		typedef std::ptrdiff_t	difference_type;
		typedef T				value_type;
		typedef value_type*		pointer;
		typedef value_type&		reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template<class T>
	struct iterator_traits<const T *>
	{
		typedef std::ptrdiff_t	difference_type;
		typedef T				value_type;
		typedef const T*		pointer;
		typedef const T&		reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef Distance	difference_type;
		typedef T			value_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template<class Iter>
	class reverse_iterator : public ft::iterator<typename ft::iterator_traits<Iter>::iterator_category,
												 typename ft::iterator_traits<Iter>::value_type,
												 typename ft::iterator_traits<Iter>::difference_type,
												 typename ft::iterator_traits<Iter>::pointer,
												 typename ft::iterator_traits<Iter>::reference>
	{

		public:

		typedef Iter	iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference			reference;


		private:

		iterator_type	_current;


		public:

		reverse_iterator(iterator_type it = iterator_type ())
		: _current(it) {}

		template<class T>
		reverse_iterator(const reverse_iterator<T> &cpy)
		: _current(cpy.base()) {}

		iterator_type	base(void) const
		{ return (_current); }

		template<class T>
		reverse_iterator	&operator=(const reverse_iterator<T> &cpy)
		{
			_current = cpy.base();
			return (*this);
		}

		reference	operator*(void) const
		{
			iterator_type	tmp = _current;
			return (*(--tmp));
		}

		pointer		operator->(void) const
		{ return (&(this->operator*())); }

		reverse_iterator	&operator++(void)
		{
			--_current;
			return (*this);
		}

		reverse_iterator	operator++(int)
		{
			reverse_iterator	tmp = *this;
			_current--;
			return (tmp);
		}

		reverse_iterator	&operator+=(const difference_type n)
		{
			_current -= n;
			return (*this);
		}

		reverse_iterator	&operator--(void)
		{
			++_current;
			return (*this);
		}

		reverse_iterator	operator--(int)
		{
			reverse_iterator	tmp = *this;
			_current++;
			return (tmp);
		}

		reverse_iterator	&operator-=(const difference_type n)
		{
			_current += n;
			return (*this);
		}

		reference	operator[](const difference_type n) const
		{ return (*(_current.base() - n - 1)); }

	};
}

typedef std::ptrdiff_t	difference_type;

namespace ft
{
	template<class L, class R>
	bool	operator==(const ft::reverse_iterator<L> &lhs,
					   const ft::reverse_iterator<R> &rhs)
	{ return (lhs.base() == rhs.base()); }

	template<class L, class R>
	bool	operator!=(const ft::reverse_iterator<L> &lhs,
					   const ft::reverse_iterator<R> &rhs)
	{ return (lhs.base() != rhs.base()); }

	template<class L, class R>
	bool	operator<(const ft::reverse_iterator<L> &lhs,
					  const ft::reverse_iterator<R> &rhs)
	{ return (rhs.base() < lhs.base()); }

	template<class L, class R>
	bool	operator<=(const ft::reverse_iterator<L> &lhs,
					   const ft::reverse_iterator<R> &rhs)
	{ return (rhs.base() <= lhs.base()); }

	template<class L, class R>
	bool	operator>(const ft::reverse_iterator<L> &lhs,
					  const ft::reverse_iterator<R> &rhs)
	{ return (rhs.base() > lhs.base()); }

	template<class L, class R>
	bool	operator>=(const ft::reverse_iterator<L> &lhs,
					   const ft::reverse_iterator<R> &rhs)
	{ return (rhs.base() >= lhs.base()); }

	template<class T>
	reverse_iterator<T>	operator+(const reverse_iterator<T> &it, const difference_type n)
	{ return (reverse_iterator<T> (it.base() - n)); }

	template<class T>
	reverse_iterator<T>	operator+(const difference_type n, const reverse_iterator<T> &it)
	{ return (reverse_iterator<T> (it.base() - n)); }

	template<class T>
	reverse_iterator<T>	operator-(const reverse_iterator<T> &it, const difference_type n)
	{ return (reverse_iterator<T> (it.base() + n)); }

	template<class L, class R>
	difference_type	operator-(const reverse_iterator<L> &lhs,
							  const reverse_iterator<R> &rhs)
	{ return (rhs.base() - lhs.base()); }

	template<class InputIt>
	difference_type	distance(InputIt first, InputIt last)
	{
		typename ft::iterator_traits<InputIt>::difference_type	diff = 0;
		while (first++ != last)
			diff++;
		return (diff);
	}
}
