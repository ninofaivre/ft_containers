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
# include "iterator.hpp"
# include <memory>
# include <cstddef>
# include <functional>
# include <limits>

//enum { RED, BLACK };
# define RED true
# define BLACK false

#include <iostream>

template<class Data, class Alloc, class Comp>
struct node
{

public:
	
	typedef Data	value_type;

private:

	Comp	_comp;
	bool	_color;


public:

	node	*_father;
	node	*_left;
	node	*_right;

private:

	Data	_data;

public:

	node(Data d, node *father, Comp comp)
	: _comp(comp), _color(RED), _father(father), _left(NULL), _right(NULL), _data(d) {}

	//voir si peut être remplacé par operator '='
	void	copy(node &otherInst, Alloc &alloc)
	{
		alloc.destroy(&_data);
		alloc.construct(&_data, Data(otherInst.getData()));
		_color = otherInst._color;
		_comp = otherInst._comp;
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

template<class Data, class Node>
class rbtIterator
{

public:

	typedef ft::bidirectional_iterator_tag	iterator_category;
	typedef typename Node::value_type		value_type;
	typedef ptrdiff_t						difference_type;
	typedef Data *							pointer;
	typedef Data &							reference;

private:

	typedef Node	node_type;

	node_type	*const*_root;
	node_type	*_ptr;
	node_type	*_lastValidPtr;
	bool		_end;


public:

	rbtIterator(node_type *const*root = NULL, node_type *ptr = NULL, bool end = false, node_type *lastValidPtr = NULL)
	: _root(root), _ptr(ptr), _lastValidPtr(lastValidPtr), _end(end) {}

	rbtIterator(const rbtIterator &cpy)
	: _root(cpy._root), _ptr(cpy._ptr), _lastValidPtr(cpy._lastValidPtr), _end(cpy._end) {}

	operator rbtIterator<const Data, Node> () const
	{ return (rbtIterator<const Data, Node> (_root, _ptr, _end, _lastValidPtr)); }
 
	bool	operator==(const rbtIterator &otherInst) const
	{
		if (_end && otherInst._end)
			return (true);
		return (_ptr == otherInst._ptr && _end == otherInst._end);
	}
	
	bool	operator!=(const rbtIterator &otherInst) const
	{
		if (_end && otherInst._end)
			return (false);
		return (_ptr != otherInst._ptr || _end != otherInst._end);
	}

	reference	operator*(void) const
	{ return (_ptr->getData()); }

	pointer	operator->() const
	{
		return (&_ptr->getData());
	}

	rbtIterator	&operator++(void)
	{
		node_type	*next = NULL;

		if (_lastValidPtr == _ptr)
			_lastValidPtr = NULL;
		if (!_lastValidPtr && !_end)
		{
			if (!_ptr)
				return (*this);
			next = _ptr->nextNode();
			if (!next)
			{
				_end = true;
				_lastValidPtr = _ptr;
				_ptr++;
			}
			else
				_ptr = next;
		}
		else
		{
			_end = false;
			_ptr++;
		}
		return (*this);
	}

	rbtIterator	operator++(int)
	{
		rbtIterator	tmp = *this;
		this->operator++();
		return (tmp);
	}

	void	endCase(void)
	{
		_ptr = *_root;
		while (_ptr && _ptr->_right)
			_ptr = _ptr->_right;
		_end = false;
	}

	rbtIterator	&operator--(void)
	{
		node_type	*prev = NULL;

		if (_end)
		{
			this->endCase();
			return (*this);
		}
		if (_lastValidPtr == _ptr)
		{
			_lastValidPtr = NULL;
			_end = true;
		}
		if (!_lastValidPtr && !_end)
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

	typedef Alloc									dataAllocator_type;
	typedef node<Data, dataAllocator_type, Comp>	node_type;


public:

	typedef Data		data_type;
	typedef std::size_t	size_type;
	typedef rbtIterator<Data, node_type>			iterator;
	typedef rbtIterator<const Data, node_type>		const_iterator;

	typedef typename Alloc::template rebind< node_type >::other	nodeAllocator_type;


private:

	node_type			*_root;
	dataAllocator_type	_dataAllocator;
	nodeAllocator_type	_nodeAllocator;
	Comp				_comp;
	size_type			_size;


public:

	rbt(const Comp &comp = Comp (), const dataAllocator_type &dataAllocator = dataAllocator_type ())
	: _root(NULL), _dataAllocator(dataAllocator), _nodeAllocator(dataAllocator), _comp(comp), _size(0) {}

	rbt(const dataAllocator_type &dataAllocator)
	: _root(NULL), _dataAllocator(dataAllocator), _nodeAllocator(dataAllocator), _comp(Comp ()), _size(0) {}

	rbt(const rbt &cpy)
	: _root(NULL), _dataAllocator(cpy._dataAllocator), _nodeAllocator(cpy._nodeAllocator), _comp(cpy._comp), _size(cpy._size)
	{ this->copy(cpy); }

	~rbt(void)
	{
		if (_root)
			destroySubTree(_root);
	}

	Comp	value_comp(void) const
	{ return (_comp); }

	size_type	max_size(void) const
	{ return (_nodeAllocator.max_size()); }

	void	deleteNode(node_type *nd)
	{
		_nodeAllocator.destroy(nd);
		_nodeAllocator.deallocate(nd, 1);
	}

	void	destroySubTree(node_type *nd)
	{
		if (!nd)
			return ;
		destroySubTree(nd->_left);
		destroySubTree(nd->_right);
		deleteNode(nd);
	}

	void	swap(rbt &swp)
	{
		{
			node_type	*tmp = _root;
			_root = swp._root;
			swp._root = tmp;
		}
		{
			dataAllocator_type	tmp = _dataAllocator;
			_dataAllocator = swp._dataAllocator;
			swp._dataAllocator = tmp;
		}
		{
			nodeAllocator_type	tmp = _nodeAllocator;
			_nodeAllocator = swp._nodeAllocator;
			swp._nodeAllocator = tmp;
		}
		{
			size_type	tmp = _size;
			_size = swp._size;
			swp._size = tmp;
		}
		{
			Comp	tmp = _comp;
			_comp = swp._comp;
			swp._comp = tmp;
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
		_nodeAllocator.construct(*child, node_type (d, parent, _comp)); 
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

	node_type	*search(Data d) const
	{
		node_type	*nd = _root;
		
		while (nd && !(!_comp(d, nd->getData()) && !_comp(nd->getData(), d)))
			nd = _comp(d, nd->getData()) ? nd->_left : nd->_right;
		return (nd);
	}

	std::size_t	count(Data d) const
	{
		size_t		n = 0;
		for (node_type	*nd = this->search(d); (nd && (!_comp(d, nd->getData()) && !_comp(nd->getData(), d))); nd = nd->_right)
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

	iterator	getEnd(void)
	{ return (iterator (&_root, NULL, true)); }

	const_iterator	getEnd(void) const
	{ return (iterator (&_root, NULL, true)); }

	iterator	getIt(node_type *nd)
	{ return (nd ? iterator (&_root, nd) : getEnd()); }

	const_iterator	getIt(node_type *nd) const
	{ return (nd ? const_iterator (&_root, nd) : getEnd()); }

	node_type	*upper_bound(Data d) const
	{
		node_type	*up = this->min();

		while (up && (_comp(up->getData(), d) || !_comp(d, up->getData())))
			up = up->nextNode();
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
		if (!(*nd))
		{
			*nd = _nodeAllocator.allocate(1);
			_nodeAllocator.construct(*nd, node_type (cpyNd->getData(), father, _comp));
		}
		(*nd)->copy(*cpyNd, _dataAllocator);
	}

	void	recCopy(node_type *father, node_type **nd, node_type *cpyNd)
	{
		if (!cpyNd && !*nd)
			return ;
		if (!cpyNd && *nd)
		{
			destroySubTree(*nd);
			*nd = NULL;
			return ;
		}
		copyOneNode(father, nd, cpyNd);
		recCopy(*nd, &(*nd)->_right, cpyNd->_right);
		recCopy(*nd, &(*nd)->_left, cpyNd->_left);
	}

	void	copy(const rbt &cpy)
	{
		_dataAllocator = cpy._dataAllocator;
		_nodeAllocator = cpy._nodeAllocator;
		_size = cpy._size;
		recCopy(NULL, &_root, cpy._root);
	}


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
		deleteNode(old);
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
