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

	template<class InputIt>
	typename ft::iterator_traits<InputIt>::difference_type	distance(InputIt first,
																	 InputIt last)
	{
		typename ft::iterator_traits<InputIt>::difference_type	diff = 0;
		while (first++ != last)
			diff++;
		return (diff);
	}
}
