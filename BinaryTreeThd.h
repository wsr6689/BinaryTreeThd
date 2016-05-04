#pragma once
#include <iostream>
using namespace std;

enum PointerTag
{
	THREAD,//线索化
	LINK,  //节点
};

template <class T>
struct BinaryTreeNode//节点
{
	BinaryTreeNode(const T& data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
		,_leftTag(LINK)
		,_rightTag(LINK)
	{}
	T _data;   //数据
	BinaryTreeNode* _left; //左孩子
	BinaryTreeNode* _right;//右孩子
	PointerTag _leftTag;//左孩子线索标志
	PointerTag _rightTag;//右孩子线索标志
};

template <class T>
class BinaryTreeThd
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTreeThd()  //无参构造函数
		:_root(NULL)
	{}
	BinaryTreeThd(const T* a,size_t size,const T& invalue) //有参构造函数
	{ 
		size_t index = 0;
		_root = _BinaryTreeThd(a,size,index,invalue);
	}
	void InOrderThreading()//中序线索化
	{
		Node* prev = NULL;
		_InOrderThreading(_root,prev);	
	}
	void PrevOrderThreading()//先序线索化
	{
		Node* prev = NULL;
		_PrevOrderThreading(_root,prev);
	}
	void PostOrderThreading()//后序线索化
	{
		Node* prev = NULL;
		_PostOrderThreading(_root,prev);
	}
	void InOrderThd()//中序遍历
	{
		cout<<"中序遍历:"<<endl;
		Node* cur = _root;
		while(cur)
		{
			while(cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			cout<<cur->_data<<" ";
			while(cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout<<cur->_data<<" ";
			}
			cur = cur->_right;
		}
	}

	void PrevOrderThd()//先序遍历
	{
		cout<<"先序遍历:"<<endl;
		Node* cur = _root;
		while(cur)
		{
			while(cur->_leftTag == LINK)
			{
				cout<<cur->_data<<" ";
				cur = cur->_left;
			}
			cout<<cur->_data<<" ";
			cur = cur->_right;
		}
	}

	//void PostOrderThd()//后序遍历
	//{
	//	cout<<"后序遍历:"<<endl;
	//	Node* cur = _root;
	//	
	//}
public:
	Node* _BinaryTreeThd(const T* a,size_t size,size_t& index,const T& invalue)//创建树
	{
		Node* root = NULL;
		if(index < size && a[index] != invalue)
		{
			root = new Node(a[index]);
			root->_left = _BinaryTreeThd(a,size,++index,invalue);
			root->_right =  _BinaryTreeThd(a,size,++index,invalue);
		}
		return root;
	}

	void _InOrderThreading(Node* cur,Node* &prev)//中序线索化
	{
		if(cur == NULL)
			return;
		_InOrderThreading(cur->_left,prev);
		if(cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}
		if(prev && prev->_right == NULL)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}
		prev = cur;
		_InOrderThreading(cur->_right,prev);
	}

	void _PrevOrderThreading(Node* cur,Node* &prev)//先序线索化
	{
		if(cur == NULL)
			return;
		if(cur->_left == NULL)  //前序线索
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}	
		if(prev && prev->_right == NULL)//后序线索
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}
		prev = cur;
		if(cur->_leftTag == LINK)
		{
			_PrevOrderThreading(cur->_left,prev);
		}
		if(cur->_rightTag == LINK)
		{
			_PrevOrderThreading(cur->_right,prev);
		}
	}

	void _PostOrderThreading(Node* cur,Node* &prev)//后序线索化
	{
		if(cur == NULL)
			return;
		_PostOrderThreading(cur->_left,prev);
		_PostOrderThreading(cur->_right,prev);
		if(cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}
		if(prev && prev->_right == NULL)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}	
		prev = cur;
	}
protected:
	Node* _root;//根节点
};


