#include<iostream>
#include<stdio.h>
#include<assert.h>
using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	K _key;
	V _value;
	int _bf;
	AVLTreeNode(const K& key, const V& value)
		:_left(NULL),
		_right(NULL),
		_parent(NULL),
		_key(key),
		_value(value),
		_bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	bool Insert(K key, V value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return false;
		}
		cur = new Node(key, value);
		if (parent->_key < key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		//更新平衡因子
		while (parent)
		{
			if (parent->_right == cur)
				parent->_bf++;
			else
				parent->_bf--;

			if (parent->_bf == 0)//没增加高度，补齐了空缺，还是AVL
			{
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)//增加了高度，但是没达到旋转的要求，继续向上更新平衡因子
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)//需要旋转
			{
				if (parent->_bf == 2)//右子树高
				{
					if (parent->_right->_bf == 1)
						RotateL(parent);//左旋
					else if (parent->_right->_bf == -1)//往右孩子的左子树增加了结点
						RotateRL(parent);//右左旋
					break;
				}
				else if (parent->_bf == -2)//左子树高
				{
					if (parent->_left->_bf == -1)
						RotateR(parent);//右旋
					else if ((parent->_left)->_bf == 1)//往左孩子的右子树增加了结点
						RotateLR(parent);//左右旋
					break;
				}
			}
			else
				assert(false);
		}
		return true;
	}
	//左旋
	void RotateL(Node* parent)
	{
		Node* chR = parent->_right;
		Node* chRL = chR->_left;

		parent->_right = chRL;
		parent->_bf = 0;
		if (chRL)
		{
			chRL->_parent = parent;
		}

		chR->_left = parent;
		chR->_bf = 0;

		Node* PPNode = parent->_parent;
		parent->_parent = chR;

		if (PPNode == NULL)
			_root = chR;
		else
		{
			if (PPNode->_left == parent)
				PPNode->_left = chR;
			else
				PPNode->_right = chR;
		}
	}

	//右旋(左树高)
	void RotateR(Node* parent)
	{
		Node* chL = parent->_left;
		Node* chLR = chL->_right;

		parent->_left = chLR;
		parent->_bf = 0;
		if (chLR)
			chLR->_parent = parent;

		chL->_right = parent;
		chL->_bf = 0;
		Node* PPNode = parent->_parent;
		parent->_parent = chL;

		if (PPNode == NULL)
			_root = chL;
		else
		{
			if (PPNode->_left == parent)
				PPNode->_left = chL;
			else
				PPNode->_right = chL;
		}
	}
	//右左旋(往右孩子的左子树擦入结点)
	void RotateRL(Node* parent)
	{
		assert(parent != NULL);
		Node* chR = parent->_right;
		Node* chRL = chR->_left;
		int bf = chRL->_bf;
		RotateR(parent->_right);
		RotateL(parent);
		if (bf == 1)
		{
			chR->_bf = 0;
			parent->_bf = -1;
		}
		else
		{
			chR->_bf = 1;
			parent->_bf = 0;
		}

	}

	//左右旋(往左孩子的右子树插入节点)
	void RotateLR(Node* parent)
	{
		assert(parent != NULL);
		Node* chL = parent->_left;
		Node* chLR = chL->_right;
		int bf = chLR->_bf;
		RotateL(parent->_left);
		RotateR(parent);
		if (bf == 1)
		{
			chL->_bf = -1;
			parent->_bf = 0;
		}
		else
		{
			chL->_bf = 0;
			parent->_bf = 1;
		}
	}

	void InOrder()
	{
		_InOrder(_root);
        cout<<endl;
	}

    void IsBalance()
    {
        _IsBalance(_root);
    }
    bool _IsBalance(Node* root)
    {
        size_t chLHeight = Height(root->_left);
        size_t chRHeight = Height(root->_right);
        int sub = chLHeight - chRHeight;
        if(sub > 1 || sub <-1)
        {
            cout<<"false"<<endl;
            return false;
        }
        else
        {
            cout<<"true"<<endl;
            return true;
        }
    }
    
    size_t Height(Node* root)
    {
        if(root == NULL)
            return 0;
        else
            return 1+(Height(root->_left) > Height(root->_right) ? Height(root->_left) : Height(root->_right));

    }
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;

		_InOrder(root->_left);
        cout<<root->_key<<" ";
		_InOrder(root->_right);
	};

private:
	Node* _root;
};

void TestAVL()
{
	AVLTree<int, int> avl;
	/* avl.Insert(0, 0); */
	/* avl.Insert(1, 1); */
	/* avl.Insert(2, 2); */
	/* avl.Insert(3, 3); */
	/* avl.Insert(4, 4); */
	/* avl.Insert(5, 5); */
	/* avl.Insert(6, 6); */

    avl.Insert(4,4);
    avl.Insert(2,2);
    avl.Insert(6,6);
    avl.Insert(1,1);
    avl.Insert(3,3);
    avl.Insert(5,5);
    avl.Insert(15,15);
    avl.Insert(7,7);
    avl.Insert(16,16);
    avl.Insert(14,14);

	avl.InOrder();
    avl.IsBalance();
};

