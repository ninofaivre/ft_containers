/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   rbt.hpp                                           :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: nfaivre <nfaivre@student.42.fr>           +#+  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2022/09/17 14:14:01 by nfaivre          #+#    #+#              */
/*   Updated: 2022/09/17 14:14:32 by nfaivre         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "utility.hpp"
# include "type_traits.hpp"
# include <memory>
# include <cstddef>
# include <functional>

//enum { RED, BLACK };
# define RED true
# define BLACK false

template<class Data, class Alloc, class Comp>
struct node
{

public:

	typedef Alloc	dataAllocator_type;
	typedef typename Alloc::template rebind<node>::other	nodeAllocator_type;


private:

	Data			_data;
	dataAllocator_type	&_dataAllocator;
	nodeAllocator_type	&_nodeAllocator;
	bool	_color;
	Comp	&_comp;


public:

	node					*_father;
	node					*_left;
	node					*_right;

	node(Data d, node *father, dataAllocator_type &dataAllocator, nodeAllocator_type &nodeAllocator, Comp &comp)
	: _data(d), _dataAllocator(dataAllocator), _nodeAllocator(nodeAllocator), _color(RED), _comp(comp), _father(father), _left(NULL), _right(NULL) {}

	~node(void)
	{
		if (_left)
		{
			_nodeAllocator.destroy(_left);
			_nodeAllocator.deallocate(_left, 1);
		}
		if (_right)
		{
			_nodeAllocator.destroy(_right);
			_nodeAllocator.deallocate(_right, 1);
		}
	}

	node	operator=(node &otherInst)
	{
		_dataAllocator.destroy(&_data);
		_dataAllocator.construct(&_data, otherInst._data);
		_color = otherInst._color;
		_nodeAllocator = otherInst._nodeAllocator;
		_dataAllocator = otherInst._dataAllocator;
		_comp = otherInst._comp;
		return (*this);
	}

	bool	operator==(node &otherInst)
	{ return (!_comp(_data, otherInst._data) && !_comp(otherInst._data, _data)); }

	bool	operator<(node &otherInst)
	{ return (_comp(_data, otherInst._data)); }

	bool	operator<=(node &otherInst)
	{ return (!_comp(otherInst._data, _data)); }
	
	bool	operator>(node &otherInst)
	{ return (_comp(otherInst._data, _data)); }

	bool	operator>=(node &otherInst)
	{ return (!_comp(_data, otherInst._data)); }

	node	*_getGrandFather(void) const
	{ return (_father->_father); }

	bool	isLeft(void) const
	{ return (this == _father->_left); }

	node	*nextNode(void)
	{
		node	*next = NULL;

		for (node *nd = _father; nd != NULL; nd = nd->_father)
		{
			if ((*nd > *this) && (!next || *nd < *next))
				next = nd;
		}
		for (node *nd = _right; nd != NULL; nd = nd->_left)
		{
			if ((*nd > *this) && (!next || *nd < *next))
				next = nd;
		}
		return (next);
	}

	node	*prevNode(void)
	{
		node	*prev = NULL;

		for(node *nd = this->_father; nd != NULL; nd = nd->_father)
		{
			if ((*nd < *this) && (!prev || *nd > *prev))
				prev = nd;
		}
		for(node *nd = this->_left; nd != NULL; nd = nd->_right)
		{
			if ((*nd < *this) && (!prev || *nd > *prev))
				prev = nd;
		}
		return (prev);
	}

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

	void	setData(const Data &d)
	{ _data = d; }

};

template<class Data, class Alloc, class Comp>
class rbtIterator
{

private:

	typedef typename ft::remove_cv<Data>::type	non_const_Data;
	typedef node< non_const_Data, Alloc, Comp>	node_type;

	node_type	*_ptr;
	node_type	*_lastValidPtr;


public:

	rbtIterator(node_type *ptr = NULL, node_type *lastValidPtr = NULL)
	: _ptr(ptr), _lastValidPtr(lastValidPtr) {}

	rbtIterator(const rbtIterator &cpy)
	: _ptr(cpy._ptr), _lastValidPtr(cpy._lastValidPtr) {}

	operator rbtIterator<const Data, Alloc, Comp> () const
	{ return (rbtIterator<const Data, Alloc, Comp> (_ptr, _lastValidPtr)); }

	bool	operator==(const rbtIterator &otherInst)
	{ return (_ptr == otherInst._ptr); }
	
	bool	operator!=(const rbtIterator &otherInst)
	{ return (_ptr != otherInst._ptr); }

	Data	operator*(void)
	{ return (_ptr->getData()); }

	Data	*operator->()
	{ return (&_ptr->getData()); }

	rbtIterator	operator++(void)
	{
		node_type	*next = NULL;

		if (_lastValidPtr == _ptr)
			_lastValidPtr = NULL;
		if (!_lastValidPtr)
		{
			if (!_ptr)
				return (*this);
			next = _ptr->nextNode();	
			if (!next)
			{
				_lastValidPtr = _ptr;
				_ptr++;
			}
			else
				_ptr = next;
		}
		else
			_ptr++;
		return (*this);
	}

	rbtIterator	operator++(int)
	{
		rbtIterator	tmp = *this;
		this->operator++();
		return (tmp);
	}

	rbtIterator	operator--(void)
	{
		node_type	*prev = NULL;

		if (_lastValidPtr == _ptr)
			_lastValidPtr = NULL;
		if (!_lastValidPtr)
		{
			if (!_ptr)
				return (*this);
			prev = _ptr->prevNode();
			if (!prev)
			{
				_lastValidPtr = _ptr;
				_ptr--;
			}
			else
				_ptr = prev;
		}
		else
			_ptr--;
		return (*this);
	}

	rbtIterator	operator--(int)
	{
		rbtIterator	tmp = *this;
		this->operator--();
		return (tmp);
	}

};

template< class Data, class Alloc = std::allocator< Data > , class Comp = std::less< Data > >
struct rbt
{

private:

	typedef node<Data, Alloc, Comp>	node_type;
	typedef rbtIterator<Data, Alloc, Comp> iterator;
	typedef rbtIterator<const Data, Alloc, Comp> const_iterator;


public:

	typedef Data		data_type;
	typedef std::size_t	size_type;

	typedef typename node_type::nodeAllocator_type	nodeAllocator_type;
	typedef typename node_type::dataAllocator_type	dataAllocator_type;


private:

	node_type	*_root;
	dataAllocator_type	_dataAllocator;
	nodeAllocator_type	_nodeAllocator;
	Comp	&_comp;
	size_type	_size;


public:

	rbt(Comp &comp = Comp (), dataAllocator_type dataAllocator = dataAllocator_type ())
	: _root(NULL), _dataAllocator(dataAllocator), _nodeAllocator(dataAllocator), _comp(comp), _size(0) {}

	rbt(dataAllocator_type dataAllocator)
	: _root(NULL), _dataAllocator(dataAllocator), _nodeAllocator(dataAllocator), _comp(Comp ()), _size(0) {}

	rbt(const rbt &cpy)
	: _dataAllocator(cpy._dataAllocator), _nodeAllocator(cpy._nodeAllocator), _comp(cpy._comp), _size(cpy._size)
	{ this->copy(cpy); }

	~rbt(void)
	{
		if (_root)
		{
			_nodeAllocator.destroy(_root);
			_nodeAllocator.deallocate(_root, 1);
		}
	}

	node_type	*push(Data d)
	{
		_size++;
		node_type *parent = NULL;
		node_type **child = &_root;

		while (*child)
		{
			parent = *child;
			child = _comp(d, (*child)->getData()) ? &(*child)->_left : &(*child)->_right;
		}
		*child = _nodeAllocator.allocate(1);
		_nodeAllocator.construct(*child, node_type (d, parent, _dataAllocator, _nodeAllocator, _comp)); 
		fixPush(*child);
		return (*child);
	}

	bool	pop(Data d)
	{
		node_type	*parent, *child;
		node_type	*ndToDelete = search(d);
		bool	originalColor = _getColor(ndToDelete);

		if (!ndToDelete)
			return (false);
		_size--;
		node_type	*y = ndToDelete->_left;
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
		fixPop(originalColor, parent, child);
		return (true);
	}

	node_type	*search(Data d)
	{
		node_type	*nd = _root;
		
		while (nd && !(!_comp(d, nd->getData()) && !_comp(nd->getData(), d)))
			nd = _comp(d, nd->getData()) ? nd->_left : nd->_right;
		return (nd);
	}

	std::size_t	count(Data d)
	{
		size_t		n = 0;
		for (node_type	*nd = this->search(d); (nd && (!_comp(d, nd->getData()) && !(nd->getData(), d))); nd = nd->_right)
			n++;
		return (n);
	}

	size_type	getSize(void) const
	{ return (_size); }

	node_type	*min(void) const
	{
		node_type	*nd = _root;
		
		while (nd && nd->_left)
			nd = nd->_left;
		return (nd);
	}

	node_type	*max(void) const
	{
		node_type	*nd = _root;

		while( nd && nd->_right)
			nd = nd->_right;
		return (nd);
	}

	iterator	getIt(node_type *nd)
	{ return (nd ? iterator (nd) : ++(iterator (this->max()))); }

	const_iterator	getIt(node_type *nd) const
	{ return (nd ? const_iterator (nd) : ++(const_iterator (this->max()))); }

	node_type	*upper_bound(Data d) const
	{
		node_type	*up = this->min();

		while (up && (_comp(up->getData(), d) || !_comp(d, up->get_Data())))
			up = up->nextNode;
		return (up);
	}

	node_type	*lower_bound(Data d) const
	{
		node_type	*low = this->min();

		while (low && _comp(low->getData(), d))
			low = low->nextNode();
		return (low);
	}

	void	copyOneNode(node_type *father, node_type **nd, node_type *cpyNd)
	{
		if (!*nd)
		{
			*nd = _nodeAllocator.allocate(1);
			_nodeAllocator.construct(*nd, node_type (cpyNd->getData(), father, _dataAllocator, _nodeAllocator, _comp));
		}
		**nd = *cpyNd;
	}

	void	recCopy(node_type *father, node_type **nd, node_type *cpyNd)
	{
		if (!cpyNd && !*nd)
			return ;
		else if (!cpyNd && *nd)
		{
			if (father)
				(*nd)->_getParentSidePtr() = NULL;
			_nodeAllocator.destroy(*nd);
			_nodeAllocator.deallocate(*nd, 1);
			return ;
		}
		copyOneNode(father, nd, cpyNd);
		recCopy(*nd, &(*nd)->_right, cpyNd->_right);
		recCopy(*nd, &(*nd)->_left, cpyNd->_left);
	}

	void	copy(const rbt &cpy)
	{ recCopy(NULL, &_root, cpy._root); }


private:

	node_type	*_replace(node_type *old, node_type *nd)
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
		_nodeAllocator.destroy(old);
		_nodeAllocator.deallocate(old, 1);
		return (nd);
	}

	void	_swapColor(node_type	*lhs, node_type *rhs)
	{
		bool	tmp = _getColor(rhs);

		_setColor(rhs, _getColor(lhs));
		_setColor(lhs, tmp);
	}

	void	siblingBlackNephewsBlack(node_type *parent, node_type *sibling)
	{
		_setColor(sibling, RED);
		if (_getColor(parent) == RED)
			_setColor(parent, BLACK);
		else
			fixPop(BLACK, parent->_father, parent);
	}

	void	siblingBlackNearNephewRed(node_type *parent, node_type *child, node_type *sibling)
	{
		_swapColor(_getNearNephew(parent, child, sibling), sibling);
		rotate(_getNearNephew(parent, child, sibling), sibling);
		// child : sibling->_father->_getBrother()
		//siblingBlackFarNephewRed(sibling->_father->_father, sibling->_father, _getFarNephew(sibling->_father->_father, sibling->_father->_getBrother(), sibling->_father));
		siblingBlackFarNephewRed(parent, sibling->_father, _getFarNephew(parent, child, sibling->_father)); // doute tester si fonctionnel
	}

	void	siblingBlackFarNephewRed(node_type *parent, node_type *sibling, node_type *farNephew)
	{
		_swapColor(sibling, parent);
		_setColor(farNephew, BLACK);
		rotate(sibling, parent);
	}

	void	fixPop(bool originalColor, node_type *parent, node_type *child)
	{
		if (!parent)
		{
			_setColor(child, BLACK);
			return ;
		}
		node_type *sibling = (!child) ? _getOnlyChild(parent) : child->_getBrother();
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
			fixPop(BLACK, parent, child);
		}
		else if (_getColor(sibling->_left) == BLACK && _getColor(sibling->_right) == BLACK)
			siblingBlackNephewsBlack(parent, sibling);
		else if (_getColor(_getNearNephew(parent, child, sibling)) == RED)
			siblingBlackNearNephewRed(parent, child, sibling);
		else if (_getColor(_getFarNephew(parent, child, sibling)) == RED)
			siblingBlackFarNephewRed(parent, sibling, _getFarNephew(parent, child, sibling));
	}

	void	fixPush(node_type *Z)
	{
		if (!Z->_father)
			_setColor(Z, BLACK);
		else if (_getColor(Z) != RED || _getColor(Z->_father) != RED)
			return ;
		else if (_getColor(Z->_getUncle()) == RED)
		{
			recolor(Z);
			fixPush(Z->_getGrandFather());
		}
		else if (Z->isLeft() != Z->_father->isLeft())
			fixPush(rotate(Z, Z->_father));
		else if (Z->isLeft() == Z->_father->isLeft())
		{
			recolor(Z);
			fixPush(rotate(Z->_father, Z->_getGrandFather()));
		}
	}

	void	recolor(node_type *nd)
	{
		_setColor(nd->_father, BLACK);
		_setColor(nd->_getUncle(), BLACK);
		_setColor(nd->_getGrandFather(), RED);
	}

	node_type	*rotate(node_type *child, node_type *parent)
	{
		node_type	**childRoChild = child->isLeft() ? &child->_right : &child->_left;
		node_type	**parentRoChild = child->isLeft() ? &parent->_left : &parent->_right;
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

	bool	_getColor(node_type *nd) const
	{ return (nd ? nd->_getColor() : BLACK); }

	node_type	*_getOnlyChild(node_type *nd) const
	{ return (!nd->_left ? nd->_right : nd->_left); }

	node_type	*_getFarNephew(node_type *parent, node_type *child, node_type *sibling) const
	{ return (parent->_left == child ? sibling->_right : sibling->_left); }

	node_type *_getNearNephew(node_type *parent, node_type *child, node_type *sibling) const
	{ return (parent->_left == child ? sibling->_left : sibling->_right); }

	void	_setColor(node_type *nd, bool c) const
	{ if (nd) nd->_setColor(c); }

};
