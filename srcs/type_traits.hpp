/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   type_traits.hpp                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: nfaivre <nfaivre@student.42.fr>           +#+  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2022/09/04 18:18:27 by nfaivre          #+#    #+#              */
/*   Updated: 2022/09/04 18:18:27 by nfaivre         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

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
}
