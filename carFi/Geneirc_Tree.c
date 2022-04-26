#include "Generic_tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



Tree createTree()
{
    Tree tree;
    tree = (Tree)malloc(sizeof(struct tree));
    if(!tree) return NULL;
    tree->head = NULL;
    tree->elementCount = 0;
    return tree;
}

int freeNode(Tree_Node* node)
{
    if(node != NULL)
    {   
        free(node->data);
        free(node);
        return 1;
    }
    return 0;
}


int insert_helper(Tree_Node **head, void* data, size_t size, int (*compare)(const void* a,const void* b))
{
    if(*head == NULL)
    {
        *head = (Tree_Node*)malloc(sizeof(Tree_Node));
        if(!(*head))
        { 
            free(*head);
            return 0;
        }
        (*head)->left = NULL;
        (*head)->right = NULL;
        (*head)->data = malloc(size);
        if(!((*head)->data))
        {
            free((*head)->data);
            return 0;
        }
        memcpy((*head)->data,data,size);
        return 1;
    }
    else
    {
        if(compare(data,(*head)->data) < 0)
        {
            return insert_helper(&((*head)->left),data,size,compare);
        }
        else if(compare(data,(*head)->data) > 0)
        {
            return insert_helper(&((*head)->right),data,size,compare);
        }
    }
    return 0;
}

int insert(Tree tree, void* data, size_t size, int (*compare)(const void* a,const void* b))
{
    if(insert_helper(&(tree->head),data,size,compare))
    {
        tree->elementCount++;
        return 1;
    }
    return 0;
}

Tree_Node* search_helper(Tree_Node* head, void* data, int (*compare)(const void* a ,const void* b))
{
    if (head == NULL) return NULL;
    else if (compare(data,head->data) > 0) return search_helper(head->right, data, compare);
    else if (compare(data,head->data) < 0) return search_helper(head->left, data, compare);
    else return head;
}


Tree_Node* search(Tree tree, void* data, int (*compare)(const void* a ,const void* b))
{
    return search_helper(tree->head,data,compare);
}

Tree_Node* findMin(Tree_Node* head) 
{
    if(!head || !(head->left)) 
    return head;
    return findMin(head->left);
}

Tree_Node* findMax(Tree_Node* head)
{
    if(!head || !(head->right)) 
    return head;
    else return findMax(head->right);
}


Tree_Node* deleteNode_helper(Tree_Node* head, void* data,size_t size,int (*compare)(const void*,const void*))
{   
    Tree_Node* cur;
    Tree_Node* prev;

    cur = head;
    prev = NULL;

    while (cur != NULL && compare(cur->data,data) != 0)
    {
        prev = cur;
        if(compare(data,cur->data) < 0) cur = cur->left;
        else  cur = cur->right;
    }
    if (cur == NULL)
    {
        return head;
    }
    if (cur->left == NULL || cur->right == NULL)
    {
        Tree_Node* newCur;
        if (cur->left == NULL) newCur = cur->right;
        else newCur = cur->left;
        if (prev == NULL) return newCur;
        if (cur == prev->left) prev->left = newCur;
        else prev->right = newCur;
        freeNode(cur);
    }
    else
    {
        Tree_Node* p;
        Tree_Node* temp;
        p = NULL;
        temp = cur->right;
        while (temp->left != NULL)
        {
            p = temp;
            temp = temp->left;
        }
        if (p != NULL)  p->left = temp->right;
        else cur->right = temp->right;
        memcpy(cur->data,temp->data,size);
        freeNode(temp);
    }
    return head;
}


int deleteNode(Tree tree, void* data, size_t size, int (*compare)(const void* a,const void* b))
{
    Tree_Node* head = search(tree,data,compare);
    if(tree && head)
    {
        tree->head = deleteNode_helper(tree->head,data,size,compare);
        if(tree->elementCount == 1) tree->head = NULL;
        tree->elementCount--;
        return 1;
    }
    return 0;
}

void deleteTree_helper(Tree_Node* head)
{
    if (head == NULL) return;
    deleteTree_helper(head->left);
    deleteTree_helper(head->right);
    freeNode(head);
    head = NULL;
}

int deleteTree(Tree tree)
{
    if(tree != NULL)
    {
        deleteTree_helper(tree->head);
        tree->head= NULL;
        tree->elementCount = 0;
        return 1;
    }
    return 0;
}


