#include <memory>
#include <iostream>

#define BLACK false
#define RED true

struct node
{

private:

	std::allocator<node>	_allocator;
	bool					_color;


public:

	int						_key;
	node					*_father;
	node					*_left;
	node					*_right;

	node(int key, node *father, std::allocator<node> alloc)
	: _key(key), _father(father), _allocator(alloc), _color(RED), _left(NULL), _right(NULL) {}

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

};

struct tree
{

public:

	node	*_root;
	std::allocator<node>	_allocator;


public:

	tree(void)
	: _root(NULL), _allocator(std::allocator<node> ()) {}

	~tree(void)
	{
		if (_root)
		{
			_allocator.destroy(_root);
			_allocator.deallocate(_root, 1);
		}
	}

	void	insert(int key)
	{
		node *parent = NULL;
		node **child = &_root;

		while (*child)
		{
			parent = *child;
			child = key < (*child)->_key ? &(*child)->_left : &(*child)->_right;
		}
		*child = _allocator.allocate(1);
		_allocator.construct(*child, node (key, parent, _allocator)); 
		fixTreeInsertion(*child);
	}

	node	*search(int key) const
	{
		node	*nd = _root;
		while (nd && nd->_key != key)
			nd = nd->_key < key ? nd->_right : nd->_left;
		return (nd);
	}

	node	*replace(node *old, node *nd)
	{
		if (nd)
		{
			//nd->_setColor(old->_getColor());
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

	void	remove(int key)
	{
		node	*ndToDelete = search(key);
		bool	originalColor = _getColor(ndToDelete);
		if (!ndToDelete)
			return ;
		node	*y = ndToDelete->_left;
		if (ndToDelete->_left && ndToDelete->_right)
		{
			while (y->_right)
				y = y->_right;
			originalColor = _getColor(y);
			if (y != ndToDelete->_left)
			{
				y->_getParentSidePtr() = y->_left;
				if (y->_left)
				{
					y->_left->_father = y->_father;
					y->_left= NULL;
				}
			}
			fixTreeRemove(originalColor, replace(ndToDelete, y), y->_left);
		}
		else
		{
			node *parent = ndToDelete->_father;
			fixTreeRemove(originalColor, parent, replace(ndToDelete, _getOnlyChild(ndToDelete)));
		}
	}

	void	case1(node *parent, node *child, node *sibling)
	{
		std::cout << "case 1" << std::endl;
		_setColor(sibling, RED);
		if (_getColor(parent) == RED)
			_setColor(parent, BLACK);
		else
			fixTreeRemove(BLACK, parent->_father, parent);
	}

	void	swapColor(node	*lhs, node *rhs)
	{
		bool	tmp = _getColor(rhs);
		_setColor(rhs, _getColor(lhs));
		_setColor(lhs, tmp);
	}

	void	case2(node *parent, node *child, node *sibling)
	{
		std::cout << "case 2" << std::endl;
		swapColor(sibling, parent);
		rotate(sibling, parent);
		std::cout << "fix tree again" << std::endl;
		fixTreeRemove(BLACK, parent, child);
	}

	void	case3(node *parent, node *child, node *sibling)
	{
		std::cout << "case 3" << std::endl;
		swapColor(_getNearChild(parent, child, sibling), sibling);
		rotate(_getNearChild(parent, child, sibling), sibling);
		case4(sibling->_father->_father, sibling->_father->_getBrother(), sibling->_father);
	}

	void	case4(node *parent, node *child, node *sibling)
	{
		std::cout << "case 4" << std::endl;
		swapColor(sibling, parent);
		_setColor(_getFarChild(parent, child, sibling), BLACK);
		rotate(sibling, parent);
	}

	void	fixTreeRemove(bool originalColor, node *parent, node *child) // originColor fatherOfDB DBside
	{
		if (!parent)
		{
			_setColor(child, BLACK);
			return ;
		}
		node *sibling = (!child) ? _getOnlyChild(parent) : child->_getBrother();
		if (originalColor == RED)
		{
			std::cout << "no need for a fix" << std::endl;
			return ;
		}
		std::cout << "need a fix" << std::endl;
		if (_getColor(child) == BLACK)
			std::cout << "DB" << std::endl;
		else
		{
			_setColor(child, BLACK);
			std::cout << "PAS DE DOUBLE BLACK (simple recolo de child)" << std::endl;
			return ;
		}
		if (_getColor(sibling) == BLACK && _getColor(sibling->_left) == BLACK && _getColor(sibling->_right) == BLACK)
			case1(parent, child, sibling);
		else if (_getColor(sibling) == RED)
			case2(parent, child, sibling);
		else if (_getColor(sibling) == BLACK && _getColor(_getFarChild(parent, child, sibling)) == BLACK &&
				 _getColor(_getNearChild(parent, child, sibling)) == RED)
			case3(parent, child, sibling);
		else if (_getColor(sibling) == BLACK && _getColor(_getFarChild(parent, child, sibling)) == RED &&
				 _getColor(_getNearChild(parent, child, sibling)) == BLACK)
			case4(parent, child, sibling);
	}

	void	fixTreeInsertion(node *Z)
	{
		if (!Z->_father)
			_setColor(Z, BLACK);
		else if (_getColor(Z) != RED || _getColor(Z->_father) != RED)
			return ;
		else if (_getColor(Z->_getUncle()) == RED)
		{
			recolor(Z);
			fixTreeInsertion(Z->_getGrandFather());
		}
		else if (Z->isLeft() != Z->_father->isLeft())
			fixTreeInsertion(rotate(Z, Z->_father));
		else if (Z->isLeft() == Z->_father->isLeft())
		{
			recolor(Z);
			fixTreeInsertion(rotate(Z->_father, Z->_getGrandFather()));
		}
	}

	void	recolor(node *nd)
	{
		_setColor(nd->_father, BLACK);
		_setColor(nd->_getUncle(), BLACK);
		_setColor(nd->_getGrandFather(), RED);
	}

	node	*rotate(node *child, node *parent)
	{
		node	**childRoChild = child->isLeft() ? &child->_right : &child->_left;
		node	**parentRoChild = child->isLeft() ? &parent->_left : &parent->_right;
		child->_father = parent->_father;
		if (parent->_father)
		{
			if (parent->isLeft())
				parent->_father->_left = child;
			else
				parent->_father->_right = child;
		}
		else
			this->_root = child;
		parent->_father = child;
		*parentRoChild = *childRoChild;
		if (*childRoChild)
			(*childRoChild)->_father = parent;
		*childRoChild = parent;
		return (parent);
	}

	bool	_getColor(node *nd) const
	{ return (nd ? nd->_getColor() : BLACK); }

	node	*_getOnlyChild(node *nd) const
	{
		if (!nd->_left)
			return (nd->_right);
		else if (!nd->_right)
			return (nd->_left);
		return (NULL);
	}

	node	*_getFarChild(node *parent, node *child, node *sibling) const
	{
		if (parent->_left == child)
			return (sibling->_right);
		else
			return (sibling->_left);
	}

	node *_getNearChild(node *parent, node *child, node *sibling) const
	{
		if (parent->_left == child)
			return (sibling->_left);
		else
			return (sibling->_right);
	}

	void	_setColor(node *nd, bool c) const
	{ if (nd) nd->_setColor(c); }
	// TESTING

	void	print(void)
	{ this->printLevelOrder(_root); }

	int		height(node *_root)
	{
		if (!_root)
			return 0;
		int leftHeight = height(_root->_left);
		int rightHeight = height(_root->_right);
		return (leftHeight < rightHeight ? rightHeight + 1 : leftHeight + 1);
	}

	void	printLevelOrder(node *_root)
	{
		for (int i = 1; i <= this->height(_root); i++)
		{
			this->printGivenLevel(_root, i);
			std::cout << std::endl;
		}
	}

	void	printGivenLevel(node *_root, int floor)
	{
		if (!_root)
			return ;
		if (floor == 1)
			std::cout << _root->_key << " " << ((_getColor(_root) == BLACK) ? "black" : "red..") << "|  ";
		else if (floor > 1)
		{
			printGivenLevel(_root->_left, floor - 1);
			printGivenLevel(_root->_right, floor - 1);
		}
	}

};

int	main(void)
{
	tree	test;
	test.insert(12);
	test.insert(50);
	test.insert(2);
	test.insert(8);
	test.insert(49);
	test.insert(17);
	test.insert(13);
	test.insert(39);
	test.print();
	std::cout << "--------------------------------" << std::endl;
	std::cout << "delete 49" << std::endl;
	test.remove(49);
	test.print();
	std::cout << "--------------------------------" << std::endl;
	std::cout << "delete 2" << std::endl;
	test.remove(2);
	test.print();
	std::cout << "--------------------------------" << std::endl;
	std::cout << "delete 8" << std::endl;
	test.remove(8);
	test.print();
	std::cout << "--------------------------------" << std::endl;
	std::cout << "delete 12" << std::endl;
	test.remove(12);
	test.print();
	std::cout << "--------------------------------" << std::endl;
	std::cout << "delete 13" << std::endl;
	test.remove(13);
	test.print();
	std::cout << "--------------------------------" << std::endl;
	std::cout << "delete 39" << std::endl;
	test.remove(39);
	test.print();
	std::cout << "--------------------------------" << std::endl;
	std::cout << "delete 17" << std::endl;
	test.remove(17);
	test.print();
	std::cout << "--------------------------------" << std::endl;
	std::cout << "delete 50" << std::endl;
	test.remove(50);
	test.print();
}
