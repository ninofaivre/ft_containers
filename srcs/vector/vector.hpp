/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+      */
/*   By: nfaivre <nfaivre@student.42.fr>           +#+  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2022/08/23 13:13:59 by nfaivre          #+#    #+#              */
/*   Updated: 2022/08/23 15:03:00 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <memory>
# include <iostream>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class	vector
	{

		typedef	Alloc	allocator_type;
		
		private:

			Alloc		allocator;
			T			*data;
			std::size_t	size;
			std::size_t	capacity;


		public:

			explicit vector(const allocator_type	&alloc = allocator_type ())
			: allocator(alloc), size(0), capacity(0)
			{
				data = this->allocator.allocate(0);
			}

			~vector(void)
			{
				this->allocator.deallocate(data, capacity);
			}

			void	push_back(T val)
			{
				if (!(this->capacity - this->size))
				{
					T	*newData = this->allocator.allocate((capacity) ? capacity * 2 : 1);
					for (std::size_t i = 0; i < this->size; i++)
						newData[i] = data[i];
					this->allocator.deallocate(data, capacity);
					this->data = newData;
					this->capacity = (capacity) ? capacity * 2 : 1;
				}
				this->data[size] = val;
				this->size++;
			}

			void	print(void) const
			{
				if (!this->size)
				{
					std::cout << "(null)" << std::endl;
					return ;
				}
				std::cout << '|';
				for (std::size_t i = 0; i < this->size; i++)
					std::cout << this->data[i] << '|';
				std::cout << std::endl;
			}

	};
}
