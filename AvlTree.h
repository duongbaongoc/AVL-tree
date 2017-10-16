#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <iostream>    // For NULL
#include <queue>  // For level order printout
#include <vector> //Insert
#include <algorithm> // For max() function
#include <math.h> //For abs()
using namespace std;

// AvlTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// int size( )            --> Quantity of elements in tree
// int height( )          --> Height of the tree (null == -1)
// void insert( x )       --> Insert x
// void insert( vector<T> ) --> Insert whole vector of values
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted (in) order
// void printPreOrder( )  --> Print tree in pre order
// void printPostOrder( ) --> Print tree in post order
// void printInOrder( )   --> Print tree in *in* order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root( NULL )
      { }

    AvlTree( const AvlTree & rhs ) : root( NULL )
    {
        *this = rhs;
    }

    ~AvlTree( )
    {
       cout << " [!] Destructor called." << endl;
       makeEmpty( );
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     *  TODO: Implement - done
     */
    bool isEmpty( ) const
    {
        return !root;
    }

    /**
     * Return number of elements in tree.
     */
    int size( )
    {
      return size( root );
    }

    /**
     * Return height of tree.
     *  Null nodes are height -1
     */
    int height( )
    {
      return height( root );
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printInOrder( root );
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printInOrder( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printInOrder( root );
    }

    /**
     * Print the tree contents in pre order.
     */
    void printPreOrder( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printPreOrder( root );
    }

    /**
     * Print the tree contents in post order.
     */
    void printPostOrder( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printPostOrder( root );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }

    /**
     * Insert vector of x's into the tree; duplicates are ignored.
     */
    void insert( vector<Comparable> vals)
    {
      for( auto x : vals ) {
        insert( x, root );
      }
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     *  TODO: Implement - implementing
     */
    void remove( const Comparable & x )
    {
	if (!contains(x))
		return;
	BSTremove(x); //remove as in BST
		//balance the tree
    }

    /**
     * BST remove an item given it is in the tree
     */
     void BSTremove(const Comparable & x)
    {
	AvlNode *temp = NULL;
	AvlNode *t = root;
	AvlNode *parent = root;
	//find the item and its parent
	while (t)
	{
		if (t->element == x)
		{
			temp = t;
			break;
		}
		else if (t->element < x)
		{
			parent = t;
			t = t->right;
		}
		else
		{
			parent = t;
			t = t ->left;
		}
	}
	//delete the right node
	/***CASE 1: remove a leaf***/
	if (!(temp->left) && !(temp->right))
	{
		if (root == temp)
		{
			delete temp;
			root = NULL;
		}
		else if (parent->element > temp->element)
		{
			delete temp;
			parent->left = NULL;
		}
		else if (parent->element < temp->element)
		{
			delete temp;
			parent->right = NULL;
		}
	}
	/***CASE 2: remove a node with only left child***/
	else if (temp->left && !(temp->right))
	{
		if (root == temp)
			root = temp->left;
		else if (parent->element < temp->element)
			parent->right = temp->left;
		else if (parent->element > temp->element)
			parent->left = temp->left;
		delete temp;
	}
	/**CASE 3: remove a node with only right child***/
	else if (temp->right && !(temp->left))
	{
		if (root == temp)
			root = temp->right;
		else if (parent->element < temp->element)
			parent->right = temp->right;
		else if (parent->element > temp->element)
			parent->left = temp->right;
		delete temp;
	}
	/***CASE 4: remove a node with 2 children***/
	else
	{
		AvlNode * min = findMax(temp->right, parent);
		temp->element = min->element;
		//delete the min node
		if (parent->element > min->element)
		{
			delete parent->left;
			parent->left = NULL;
		}
		else if (parent->element < min->element)
		{
			delete parent->right;
			parent->right = NULL;
		}
	}
    }


    /**
     * Deep copy. - or copy assignment operator
     *  Will be in part II
     */
    const AvlTree & operator=( const AvlTree & rhs )
    {
      cout << " [!] Copy *assignment* operator called." << endl;
      return *this;
    }


/*****************************************************************************/
  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const Comparable & theElement, AvlNode *lt,
                                                AvlNode *rt, int h = 0 )
          : element( theElement ), left( lt ), right( rt ), height( h ) { }
    };

    AvlNode *root;

    /**
     * Internal method to count nodes in tree
     *  TODO: Implement - implementing
     */
    int size( AvlNode *& t)
    {
	int count = 0;
     	if(t)
	{
		count +=1;
		if (t->left)
			count += size(t->left);
		if (t->right)
			count += size(t->right);
	}
	return count;
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     *  TODO: Implement - implementing
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
	vector<AvlNode *> pAncestors;
        //insert as in BST
	BSTinsert(x, t, pAncestors);
	//update height for ancestor nodes
	for (int i = pAncestors.size()-1; i >= 0; i--)
		pAncestors[i]->height = height(pAncestors[i]);
	//find the unbalanced node
	AvlNode * unbalancedNode = NULL;
	AvlNode * parent = root;
	int i = pAncestors.size()-1;
	for (; i >= 0; i--)
	{
		if (abs(balanceFactor(pAncestors[i])) > 1)
		{
			unbalancedNode = pAncestors[i];
			if (i>0)
				parent = pAncestors[i-1];
			break;
		}
	}
	if (unbalancedNode)
	{
 		AvlNode * newRoot = NULL;
		if (balanceFactor(unbalancedNode) < -1) // right heavy
		{
			if (unbalancedNode->right->element < x)
				//right right insert -> left rotation
				newRoot = rotateWithRightChild(unbalancedNode);
			else
				//right left insert -> right left rotation
				newRoot = doubleWithRightChild(unbalancedNode);
		}
		if ( balanceFactor(unbalancedNode) > 1) //left heavy
		{
			if (unbalancedNode->left->element > x)
				//left left insert -> right rot
				newRoot = rotateWithLeftChild(unbalancedNode);
			else
				//left right insert ->left rigth rot
				newRoot = doubleWithLeftChild(unbalancedNode);
		}
		//stick the newRoot to the tree
		if (parent == unbalancedNode)
			root = newRoot;
		else if (newRoot ->element < parent->element)
			parent->left = newRoot;
		else
			parent->right = newRoot;
	}
	//update ancestors' heights
	for (; i>=0; i--)
	{
		pAncestors[i]->height = height(pAncestors[i]);
	}
    }

    /**
     * Find the balance factor of a node - need to test
     */
    int balanceFactor(AvlNode *node)
    {
	if (!node)
		return 0;
	return height(node->left) - height(node->right);
    }

    /**
     * BST insert - done
     * Return array of ancesstor nodes
     */
    void BSTinsert( const Comparable & x, AvlNode * & t, 
vector<AvlNode *> & pAncestor)
   {
	if (!t)
		t = new AvlNode(x, NULL, NULL);
	else if (x == t->element)
		cout << "No duplicated allowed." << endl;
	else
	{
		pAncestor.push_back(t);
		if (x < t->element)
			BSTinsert(x, t->left, pAncestor);
		else
			BSTinsert(x, t->right, pAncestor);
	}
}

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     *  You'll need this for deletes
     *  TODO: Implement - done - need to test
     */
    AvlNode * findMin( AvlNode *t, AvlNode *&parent)
    {
    	if (t)
		while (t->left)
		{
			parent = t;
			t = t->left;
		}
	return t;
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     *  TODO: Implement - done - need to test
     */
    AvlNode * findMax( AvlNode *t, AvlNode *&parent)
    {
	if (t)
		while (t->right)
		{
			parent = t;
			t = t->right;
		}
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     *  TODO: Implement - done
     */
    bool contains( const Comparable & x, AvlNode *t ) const
    {
	while (t)
	{
		if (x == t->element)
			return true;
		else if ( x > t->element)
			t = t->right;
		else
			t = t->left;
	}
	return false;
    }

/******************************************************/

    /**
     * Internal method to make subtree empty.
     *  TODO: implement for destructor - done
     * 
     */
    void makeEmpty( AvlNode * & t )
    {
	if (t)
	{
		if (t->left)
			makeEmpty(t->left);
		if (t->right)
			makeEmpty(t->right);
		delete t;
	}
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     *  TODO: Implement
     */
    void printInOrder( AvlNode *t ) const
    {
	if (t)
	{
		if (t->left)
    			printInOrder(t->left);
		cout << t->element << " ";
		if (t->right)
			printInOrder(t->right);
	}
    }

    /**
     * Internal method to print a subtree rooted at t in pre order.
     *  TODO: Implement
     */
    void printPreOrder( AvlNode *t ) const
    {
    	if (t)
	{
		cout << t->element << " ";
		if (t->left)
			printPreOrder(t->left);
		if(t->right)
			printPreOrder(t->right);
	}
    }

    /**
     * Internal method to print a subtree rooted at t in post order.
     *  TODO: Implement
     */
    void printPostOrder( AvlNode *t ) const
    {
    	if(t)
	{
		if(t->left)
			printPostOrder(t->left);
		if(t->right)
			printPostOrder(t->right);
		cout << t->element << " ";
	}
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == NULL )
            return NULL;
        else
            return new AvlNode( t->element, clone( t->left ), clone( t->right ), t->height );
    }


    // Avl manipulations
    /**
     * Return the height of node t or -1 if NULL.
     *  TODO: Implement - done
     */
    int height( AvlNode *t ) const
    {
	if (!t)
		return -1;
	else if (height(t->left) > height(t->right))
		return height(t->left) + 1;
	else
		return height(t->right) + 1;
    }


    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then return new root.
     *  TODO: Implement - implementing
     */
    AvlNode * rotateWithLeftChild( AvlNode * & k2 )
    {
	AvlNode * newRoot = k2->left;
	AvlNode * temp = k2->left->right;
	newRoot->right = k2;
	k2->left = temp;

	k2->height = height(k2);
	newRoot->height = height(newRoot);

	return newRoot;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then return new root.
     *  TODO: Implement
     */
    AvlNode * rotateWithRightChild( AvlNode * & k1 )
    {
	AvlNode *newRoot = k1->right;
	AvlNode * temp = k1->right->left;
	newRoot->left = k1;
	k1->right = temp;

	k1->height = height(k1);
	newRoot->height = height(newRoot);

	return newRoot;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then return new root.
     *  TODO: Implement
     */
    AvlNode * doubleWithLeftChild( AvlNode * & k3 )
    {
	k3->left = rotateWithRightChild(k3->left); //first rotation
	return rotateWithLeftChild(k3); //second rotation
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then return new root.
     *  TODO: Implement
     */
    AvlNode * doubleWithRightChild( AvlNode * & k1 )
    {
	k1->right = rotateWithLeftChild(k1->right);
	return rotateWithRightChild(k1);
    }
};

#endif
