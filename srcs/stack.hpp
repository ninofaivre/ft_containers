/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   stack.hpp                                         :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: nfaivre <nfaivre@student.42.fr>           +#+  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2022/09/06 12:12:49 by nfaivre          #+#    #+#              */
/*   Updated: 2022/09/06 12:12:49 by nfaivre         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "vector.hpp"

namespace ft
{
	template< class T, class Container = ft::vector<T> >
	class stack
	{

	public:

		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;
	

	protected:
	
		container_type	c;


	public:

		stack( const container_type	&cont = container_type ())
		: c(cont) {}

		stack(const stack &cpy)
		: c(cpy.c) {}

		stack	&operator=(const stack &cpy)
		{
			c = cpy.c;
			return (*this);
		}

		reference	top(void)
		{ return (c.back()); }

		bool	empty(void) const
		{ return (c.empty()); }

		size_type	size(void) const
		{ return (c.size()); }
		
		void	push(const_reference value)
		{ c.push_back(value); }

		void	pop(void)
		{ c.pop_back(); }


	private:

		friend bool	operator==(const stack &lhs, const stack &rhs)
		{ return (lhs.c == rhs.c); }

		friend bool	operator<(const stack &lhs, const stack &rhs)
		{ return (lhs.c < rhs.c); }

	};

	template<class T, class Container>
	bool	operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{ return (lhs == rhs); }

	template<class T, class Container>
	bool	operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{ return (!(lhs == rhs)); }

	template<class T, class Container>
	bool	operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{ return (lhs < rhs); }

	template<class T, class Container>
	bool	operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{ return (lhs == rhs || lhs < rhs); }

	template<class T, class Container>
	bool	operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{ return (!(lhs <= rhs)); }

	template<class T, class Container>
	bool	operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{ return (!(lhs < rhs)); }
}
