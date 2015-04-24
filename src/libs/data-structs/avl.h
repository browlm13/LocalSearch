#ifndef AVL_H
#define AVL_H

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

//--------------------------
//		avl	prototype											(for base class)
//			--------------------------------
template <class T>
class avl
{

private:

			/*		
				Note:	Each derived class must impliment
						a version of every member in private:
																*/
/*
	struct Node 								
	{
		Node(int data) :
			data(data),							
			height(0), balance(0),
			left(0), right(0)
		{ }

		//optional member
		int data;
		//optional member

		int height;
		int balance;
		Node *left;
		Node *right;	
	} *root;
*/
	//void _insert(int data, Node *&cur);			
	//void _write(Node* ptr);

	T *root;
	
public:
	//virtual void insert(int data);
	//virtual void write();

protected:
	void set_height_balance(T *& cur);
	void balance(T *& cur);
	void ll_rotation(T *& alpha);
	void rr_rotation(T *& alpha);
	void lr_rotation(T *& alpha);
	void rl_rotation(T *& alpha);

public:
	avl()	: root(0)	{ };
	~avl()	{ };								//not sure what needs to be done here
};
/*
///////////////////////////////////////////////////////////////////////////
////////////////////////// Public Interface ///////////////////////////////
///////////////////////////////////////////////////////////////////////////

//--------------------------
//		insert 		( to override )
//			--------------------------------
template <class T>
void avl<T>::insert(int data)
{	_insert(data, root);	}

//--------------------------
//		write 		( to override )
//			--------------------------------
template <class T>
void avl<T>::write()
{	_write(root);	}

///////////////////////////////////////////////////////////////////////////
////////////////////////// Private Methods ////////////////////////////////
///////////////////////////////////////////////////////////////////////////

//--------------------------
//		_write	 	( to override )
//			--------------------------------
template <class T>
void avl<T>::_write(Node *ptr){
	if(ptr){
		_write(ptr->left);
		cout << ptr->data << " " << ptr-> balance << " " << ptr->height << endl;
		_write(ptr->right);
	}
}

//--------------------------
//		_insert		( to override )
//			--------------------------------
template <class T>
void avl<T>::_insert(int data, Node *&cur){
	//insert when null
	if(!cur)
		cur = new Node(data);

	//otherwise advance left or right
	else if(data < cur->data)
		_insert(data, cur->left);

	else if(data > cur->data)
		_insert(data, cur->right);

	//duplicate handaling
	else{
		cout << "duplicate" << endl;
	}

	//balance Nodes involved in insert
	balance(cur);
}
*/
///////////////////////////////////////////////////////////////////////////

////////////////////////// UNCHANGING METHODS /////////////////////////////

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
////////////////////////// Protected Methods //////////////////////////////
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------------------
//									balancing methods
//-------------------------------------------------------------------------------------------------------------

//--------------------------
//		set_height_balance
//			--------------------------------
template <class T>
void avl<T>::set_height_balance(T *&cur){
	if(cur){
		int left_height = cur->left ? cur->left->height : 0;
		int right_height = cur->right ? cur->right->height : 0;

		//set height as 1 + max of child node heights
		cur->height = 1 + ((left_height > right_height) ? left_height : right_height);
		//set balance as diffrence
		cur->balance = left_height - right_height;
	}
}
//--------------------------
//		balance
//			--------------------------------
template <class T>
void avl<T>::balance( T *& cur ){
	//sets correct height and balance attributes
	set_height_balance(cur);

	//perform rotations if nessicary

	//left heavy
	if(cur->balance > 1){
		//ll
		if(cur->left->balance > 0)
			ll_rotation(cur);
		//lr
		else
			ll_rotation(cur);
	}

	//right heavy
	else if (cur->balance < -1){
		//rr
		if(cur->right->balance < 0)
			rr_rotation(cur);
		//rl
		else
			rl_rotation(cur);
	}
}

//--------------------------
//		ll_rotation
//			--------------------------------
template <class T>
void avl<T>::ll_rotation(T *& alpha){
	T *tmp = alpha;
	alpha = alpha->left;
	tmp->left = alpha->right;
	alpha->right = tmp;

	set_height_balance(alpha->left);
	set_height_balance(alpha->right);
	set_height_balance(alpha);
}

//--------------------------
//		rr_rotation
//			--------------------------------
template <class T>
void avl<T>::rr_rotation(T *& alpha){
	T *tmp = alpha;
	alpha = alpha->right;
	tmp->right = alpha->left;
	alpha->left = tmp;

	set_height_balance(alpha->left);
	set_height_balance(alpha->right);
	set_height_balance(alpha);
}

//--------------------------
//		lr_rotation
//			--------------------------------
template <class T>
void avl<T>::lr_rotation(T *& alpha){
	rr_rotation(alpha->right);
	ll_rotation(alpha);
}

//--------------------------
//		rl_rotation
//			--------------------------------
template <class T>
void avl<T>::rl_rotation(T *& alpha){
	ll_rotation(alpha->right);
	rr_rotation(alpha);
}

#endif //AVL_H