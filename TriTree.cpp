/* Code for implementing insertion and deletion in a trinary tree.
 * This file contains a class (Tri_Nary_Tree) to represent the trinary tree with functions 
 * to perform insert and delete functionality.
 * The insertNode() function and its helper function insertToTriTree() function
 * perform the insertoin operation. 
 * The deleteNode function and its helper function getSuccessor function 
 * perform the deletion operation. 
 
 * Please note that in the deletion operation, if the node to delete has right                   
 * children and no mid children, the delete method swap the node to delete with successor of this
 * node and delete the successor from the right subtree since the problem did not specify how to 
 * reconstruct the tree. This is to minimize the necessary tree reconstruction.
 */

#include <iostream>

class Tri_Nary_Tree {
private:
    int val;
    Tri_Nary_Tree *root;
    Tri_Nary_Tree *left;
    Tri_Nary_Tree *mid;
    Tri_Nary_Tree *right;
public:
    Tri_Nary_Tree(int val);
    void insertNode(int value);
    Tri_Nary_Tree* insertToTriTree(int val, Tri_Nary_Tree* node);   // helper function
    Tri_Nary_Tree* deleteNode(int value, Tri_Nary_Tree* node);
    Tri_Nary_Tree* getSuccessor(Tri_Nary_Tree* node);

};

Tri_Nary_Tree::Tri_Nary_Tree(int val)
{
    root->val = val;
    root->left = NULL;
    root->mid = NULL;
    root->right = NULL;
}

/* Insert a new node to the tree. */
void Tri_Nary_Tree::insertNode(int value)
{
    insertToTriTree(value, root);
}

/* Helper function for insert. Should pass in root node of the tree when calling this function from insertNode() */
Tri_Nary_Tree* Tri_Nary_Tree::insertToTriTree(int val, Tri_Nary_Tree* node)
{
    if(node == NULL)
    {
        Tri_Nary_Tree newNode = Tri_Nary_Tree(val);     // create new node
        return newNode.root;
    }
    else
    {
        if(val > node->val)
        {
            node->right = insertToTriTree(val, node->right);
        }
        else if(val < node->val)
        {
            node ->left = insertToTriTree(val, node->left);
        }
        else
        {
            node->mid = insertToTriTree(val, node->mid);
        }
        return node;
    }
}

/* Find successor node (smallest node in the right subtree) and return that node*/
Tri_Nary_Tree* Tri_Nary_Tree::getSuccessor(Tri_Nary_Tree *node)
{
    if(node == NULL)
    {
        return NULL;
    }
    else
    {
        while(node)
        {
            node = node->left;
        }
        return node;
    }
}

/* Should pass in root as node param when calling this funciton for the first time 
   Returns NULL if the node to delete does not exist in the tree
 */
Tri_Nary_Tree* Tri_Nary_Tree::deleteNode(int value, Tri_Nary_Tree* node)
{
    if(node == NULL)
    {
        return NULL;        // node to delete does not exist
    }
    else if(node->val < value)
    {
        node->left = deleteNode(value, node->left);
    }
    else if(node->val > value)
    {
        node->right = deleteNode(value, node->right);
    }
    else                    // node->val == value
    {
        if(node->mid)
        {
            node->mid = deleteNode(value, node->mid);
        }
        else if(node->right)
        {
            Tri_Nary_Tree* successor = getSuccessor(node->right);
            if(successor)
            {
                node->val = successor->val;
                node->right = deleteNode(successor->val, node->right); // start delete from right sub tree
            }
        }
        else
        {
            node = node->left;
        }
    }
    return node;
}

