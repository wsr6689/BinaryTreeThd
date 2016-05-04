#pragma once
#include <iostream>
using namespace std;

enum PointerTag
{
	THREAD,//������
	LINK,  //�ڵ�
};

template <class T>
struct BinaryTreeNode//�ڵ�
{
	BinaryTreeNode(const T& data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
		,_leftTag(LINK)
		,_rightTag(LINK)
	{}
	T _data;   //����
	BinaryTreeNode* _left; //����
	BinaryTreeNode* _right;//�Һ���
	PointerTag _leftTag;//����������־
	PointerTag _rightTag;//�Һ���������־
};

template <class T>
class BinaryTreeThd
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTreeThd()  //�޲ι��캯��
		:_root(NULL)
	{}
	BinaryTreeThd(const T* a,size_t size,const T& invalue) //�вι��캯��
	{ 
		size_t index = 0;
		_root = _BinaryTreeThd(a,size,index,invalue);
	}
	void InOrderThreading()//����������
	{
		Node* prev = NULL;
		_InOrderThreading(_root,prev);	
	}
	void PrevOrderThreading()//����������
	{
		Node* prev = NULL;
		_PrevOrderThreading(_root,prev);
	}
	void PostOrderThreading()//����������
	{
		Node* prev = NULL;
		_PostOrderThreading(_root,prev);
	}
	void InOrderThd()//�������
	{
		cout<<"�������:"<<endl;
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

	void PrevOrderThd()//�������
	{
		cout<<"�������:"<<endl;
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

	//void PostOrderThd()//�������
	//{
	//	cout<<"�������:"<<endl;
	//	Node* cur = _root;
	//	
	//}
public:
	Node* _BinaryTreeThd(const T* a,size_t size,size_t& index,const T& invalue)//������
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

	void _InOrderThreading(Node* cur,Node* &prev)//����������
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

	void _PrevOrderThreading(Node* cur,Node* &prev)//����������
	{
		if(cur == NULL)
			return;
		if(cur->_left == NULL)  //ǰ������
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}	
		if(prev && prev->_right == NULL)//��������
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

	void _PostOrderThreading(Node* cur,Node* &prev)//����������
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
	Node* _root;//���ڵ�
};


