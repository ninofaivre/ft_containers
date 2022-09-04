/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   std.hpp                                           :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: nfaivre <nfaivre@student.42.fr>           +#+  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2022/09/02 13:13:08 by nfaivre          #+#    #+#              */
/*   Updated: 2022/09/02 13:13:08 by nfaivre         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iterator>

namespace ft
{
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
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1,
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
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1,
									InputIt2 first2, InputIt2 last2,
									Compare comp)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (comp(*first1, *first2))
				return (true);
			if (comp(*first2++, *first1++))
				return (false);
		}
		return(first1 == last1 && first2 != last2);
	}

	template<class T>
	void	swap(T &a, T &b)
	{
		T	tmp = a;
		a = b;
		b = tmp;
	}

	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template<class Iter>
	struct iterator_traits;

	template<class InputIt>
	typename ft::iterator_traits<InputIt>::difference_type	distance(InputIt first,
																	 InputIt last)
	{
		typename ft::iterator_traits<InputIt>::difference_type	diff = 0;
		while (first++ != last)
			diff++;
		return (diff);
	}

	template<class T, T v>
	struct integral_constant
	{
		typedef T						value_type;
		typedef integral_constant<T, v>	type;
		static const value_type	value = v;
		operator T() { return (v); }
	};

	typedef integral_constant<bool, false>	false_type;
	typedef integral_constant<bool, true>	true_type;

	template<class T> struct is_integral : false_type {};
	template<class T> struct is_integral<const T> : is_integral<T> {};
	template<class T> struct is_integral<volatile T> : is_integral<T> {};
	template<class T> struct is_integral<const volatile T> : is_integral<T> {};

	template<> struct is_integral<bool> : true_type {};
	template<> struct is_integral<short int> : true_type {};
	template<> struct is_integral<unsigned short int> : true_type {};
	template<> struct is_integral<int> : true_type {};
	template<> struct is_integral<unsigned int> : true_type {};
	template<> struct is_integral<long int> : true_type {};
	template<> struct is_integral<unsigned long int> : true_type {};
	template<> struct is_integral<long long int> : true_type {};
	template<> struct is_integral<unsigned long long int> : true_type {};
	template<> struct is_integral<char> : true_type {};
	template<> struct is_integral<wchar_t> : true_type {};
	template<> struct is_integral<signed char> : true_type {};
	template<> struct is_integral<unsigned char> : true_type {};

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
		typedef T*				pointer;
		typedef T&				reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template<class T>
	struct iterator_traits<const T *> : iterator_traits<T *> {};
}
