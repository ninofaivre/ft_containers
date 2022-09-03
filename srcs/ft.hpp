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

	template<class InputIt>
	typename std::iterator_traits<InputIt>::difference_type	distance(InputIt first,
																	 InputIt last)
	{
		typename std::iterator_traits<InputIt>::difference_type	diff = 0;
		while (first++ != last)
			diff++;
		return (diff);
	}

	template<class T>
	struct is_integral{ static const bool	value = false; };

	template<>
	struct is_integral<bool>{ static const bool	value = true; };

	template<>
	struct is_integral<int>{ static const bool	value = true; };

	template<>
	struct is_integral<long int>{ static const bool	value = true; };

	template<>
	struct is_integral<unsigned int>{ static const bool	value = true; };

	template<>
	struct is_integral<unsigned long int>{ static const bool	value = true; };
}
