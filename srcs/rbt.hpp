/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   redBlackTree.hpp                                  :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: nfaivre <nfaivre@student.42.fr>           +#+  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2022/09/15 13:13:31 by nfaivre          #+#    #+#              */
/*   Updated: 2022/09/15 13:13:31 by nfaivre         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "utility.hpp"
# include <memory>
# include <cstddef>
# include <functional>

//enum { RED, BLACK };
# define RED true
# define BLACK false

template<class Data, class Alloc>
struct node
{

public:

	typedef typename Alloc::rebind<node>::other			allocator_type;


private:

	Data			_data;
	allocator_type	_allocator;
	bool	_color;


public:

	node					*_father;
	node					*_left;
	node					*_right;

	node(Data d, node *father, allocator_type allocator)
	: _data(d), _allocator(allocator), _color(RED), _father(father), _left(NULL), _right(NULL) {}

	~node(void)
	{
		if (_left)
		{
			_allocator.destroy(_left);
			_allocator.deallocate(_left, 1);
		}
		if (_right)
		{
			_allocator.destroy(_right);
			_allocator.deallocate(_right, 1);
		}
	}

	node	*_getGrandFather(void) const
	{ return (_father->_father); }

	bool	isLeft(void) const
	{ return (this == _father->_left); }

	node	*_getBrother(void) const
	{ return  (isLeft() ? _father->_right : _father->_left); }

	node	*_getUncle(void) const
	{ return (_father->_getBrother()); }

	bool	_getColor(void) const
	{ return (_color); }

	node	*&_getParentSidePtr(void)
	{ return (isLeft() ? _father->_left : _father->_right); }
	
	void	_setColor(bool	c)
	{ _color = c; }

	Data	&getData(void)
	{ return (_data); }

};

template< class Data, class Compare, class Alloc, class Comp = int(*)(Data, Data)>
struct tree
{

public:

	typedef Data		data_type;
	typedef std::size_t	size_type;

	typedef typename Alloc::rebind< node<Data, Alloc> >::other	allocator_type;


private:

	node<Data, Alloc>	*_root;
	allocator_type				_allocator;
	Comp	_comp;
	size_type	_size;

	int	_defaultComp(Data a, Data b)
	{
		Compare c;
		if (!c(a, b) && !c(b, a))
			return (0);
		else
			return (c(a, b) ? -1 : 1);
	}

public:

	tree(Comp comp, allocator_type allocator = allocator_type ())
	: _root(NULL), _allocator(allocator), _comp(comp), _size(0) {}

	tree(allocator_type allocator = allocator_type ())
	: _root(NULL), _allocator(allocator), _comp(_defaultComp), _size(0) {}

	~tree(void)
	{
		if (_root)
		{
			_allocator.destroy(_root);
			_allocator.deallocate(_root, 1);
		}
	}

	void	push(Data d)
	{
		_size++;
		node<Data, Alloc> *parent = NULL;
		node<Data, Alloc> **child = &_root;

		while (*child)
		{
			parent = *child;
			child = (_comp(d, (*child)->getData()) < 0) ? &(*child)->_left : &(*child)->_right;
		}
		*child = _allocator.allocate(1);
		_allocator.construct(*child, node<Data, Alloc>(d, parent, _allocator)); 
		fixTreePush(*child);
	}

	void	pop(Data d)
	{
		node<Data, Alloc>	*parent, *child;
		node<Data, Alloc>	*ndToDelete = search(d);
		bool	originalColor = _getColor(ndToDelete);

		if (!ndToDelete)
			return ;
		node<Data, Alloc>	*y = ndToDelete->_left;
		if (ndToDelete->_left && ndToDelete->_right)
		{
			while (y->_right)
				y = y->_right;
			originalColor = _getColor(y);
			child = y->_left;
			if (y != ndToDelete->_left)
			{
				y->_getParentSidePtr() = y->_left;
				parent = y->_father;
				if (y->_left)
				{
					y->_left->_father = y->_father;
					y->_left = NULL;
				}
			}
			else
				parent = y;
			_replace(ndToDelete, y);
		}
		else
		{
			parent = ndToDelete->_father;
			child = _getOnlyChild(ndToDelete);
			if (child)
				originalColor = _getColor(child);
			_replace(ndToDelete, _getOnlyChild(ndToDelete));
		}
		fixTreePop(originalColor, parent, child);
	}

	node<Data, Alloc>	*search(Data d)
	{
		node<Data, Alloc>	*nd = _root;
		
		while (nd && _comp(d, nd->getData()))
			nd = (_comp(d, nd->getData()) < 0) ? nd->_left : nd->_right;
		return (nd);
	}

	size_type	getSize(void) const
	{ return (_size); }


private:

	node<Data, Alloc>	*_replace(node<Data, Alloc> *old, node<Data, Alloc> *nd)
	{
		if (nd)
		{
			_setColor(nd, _getColor(old));
			if (old->_left && old->_left != nd && !nd->_left)
			{
				nd->_left = old->_left;
				nd->_left->_father = nd;
			}
			if (old->_right && old->_right != nd && !nd->_right)
			{
				nd->_right = old->_right;
				nd->_right->_father = nd;
			}
			nd->_father = old->_father;
		}
		if (old->_father)
			old->_getParentSidePtr() = nd;
		else
			_root = nd;
		old->_left = NULL;
		old->_right = NULL;
		_allocator.destroy(old);
		_allocator.deallocate(old, 1);
		return (nd);
	}

	void	_swapColor(node<Data, Alloc>	*lhs, node<Data, Alloc> *rhs)
	{
		bool	tmp = _getColor(rhs);

		_setColor(rhs, _getColor(lhs));
		_setColor(lhs, tmp);
	}

	//siblingBlackNephewsBlack
	void	siblingBlackNephewsBlack(node<Data, Alloc> *parent, node<Data, Alloc> *sibling)
	{
		_setColor(sibling, RED);
		if (_getColor(parent) == RED)
			_setColor(parent, BLACK);
		else
			fixTreePop(BLACK, parent->_father, parent);
	}

	//siblingBlackNearNephewRed parent , chlild , sibling
	void	siblingBlackNearNephewRed(node<Data, Alloc> *parent, node<Data, Alloc> *child, node<Data, Alloc> *sibling)
	{
		_swapColor(_getNearNephew(parent, child, sibling), sibling);
		rotate(_getNearNephew(parent, child, sibling), sibling);
		// child : sibling->_father->_getBrother()
		//siblingBlackFarNephewRed(sibling->_father->_father, sibling->_father, _getFarNephew(sibling->_father->_father, sibling->_father->_getBrother(), sibling->_father));
		siblingBlackFarNephewRed(parent, sibling->_father, _getFarNephew(parent, child, sibling->_father)); // doute tester si fonctionnel
	}

	void	siblingBlackFarNephewRed(node<Data, Alloc> *parent, node<Data, Alloc> *sibling, node<Data, Alloc> *farNephew)
	{
		_swapColor(sibling, parent);
		_setColor(farNephew, BLACK);
		rotate(sibling, parent);
	}

	void	fixTreePop(bool originalColor, node<Data, Alloc> *parent, node<Data, Alloc> *child) // originColor fatherOfDB DBside
	{
		if (!parent)
		{
			_setColor(child, BLACK);
			return ;
		}
		node<Data, Alloc> *sibling = (!child) ? _getOnlyChild(parent) : child->_getBrother();
		if (originalColor == RED)
			return ;
		if (_getColor(child) == RED)
		{
			_setColor(child, BLACK);
			return ;
		}
		if (_getColor(sibling) == RED)
		{
			_swapColor(sibling, parent);
			rotate(sibling, parent);
			fixTreePop(BLACK, parent, child);
		}
		else if (_getColor(sibling->_left) == BLACK && _getColor(sibling->_right) == BLACK)
			siblingBlackNephewsBlack(parent, sibling);
		else if (_getColor(_getNearNephew(parent, child, sibling)) == RED)
			siblingBlackNearNephewRed(parent, child, sibling);
		else if (_getColor(_getFarNephew(parent, child, sibling)) == RED)
			siblingBlackFarNephewRed(parent, sibling, _getFarNephew(parent, child, sibling));
	}

	void	fixTreePush(node<Data, Alloc> *Z)
	{
		if (!Z->_father)
			_setColor(Z, BLACK);
		else if (_getColor(Z) != RED || _getColor(Z->_father) != RED)
			return ;
		else if (_getColor(Z->_getUncle()) == RED)
		{
			recolor(Z);
			fixTreePush(Z->_getGrandFather());
		}
		else if (Z->isLeft() != Z->_father->isLeft())
			fixTreePush(rotate(Z, Z->_father));
		else if (Z->isLeft() == Z->_father->isLeft())
		{
			recolor(Z);
			fixTreePush(rotate(Z->_father, Z->_getGrandFather()));
		}
	}

	void	recolor(node<Data, Alloc> *nd)
	{
		_setColor(nd->_father, BLACK);
		_setColor(nd->_getUncle(), BLACK);
		_setColor(nd->_getGrandFather(), RED);
	}

	node<Data, Alloc>	*rotate(node<Data, Alloc> *child, node<Data, Alloc> *parent)
	{
		node<Data, Alloc>	**childRoChild = child->isLeft() ? &child->_right : &child->_left;
		node<Data, Alloc>	**parentRoChild = child->isLeft() ? &parent->_left : &parent->_right;
		child->_father = parent->_father;
		if (parent->_father)
			parent->_getParentSidePtr() = child;
		else
			this->_root = child;
		parent->_father = child;
		*parentRoChild = *childRoChild;
		if (*childRoChild)
			(*childRoChild)->_father = parent;
		*childRoChild = parent;
		return (parent);
	}

	bool	_getColor(node<Data, Alloc> *nd) const
	{ return (nd ? nd->_getColor() : BLACK); }

	node<Data, Alloc>	*_getOnlyChild(node<Data, Alloc> *nd) const
	{ return (!nd->_left ? nd->_right : nd->_left); }

	node<Data, Alloc>	*_getFarNephew(node<Data, Alloc> *parent, node<Data, Alloc> *child, node<Data, Alloc> *sibling) const
	{ return (parent->_left == child ? sibling->_right : sibling->_left); }

	node<Data, Alloc> *_getNearNephew(node<Data, Alloc> *parent, node<Data, Alloc> *child, node<Data, Alloc> *sibling) const
	{ return (parent->_left == child ? sibling->_left : sibling->_right); }

	void	_setColor(node<Data, Alloc> *nd, bool c) const
	{ if (nd) nd->_setColor(c); }

};
