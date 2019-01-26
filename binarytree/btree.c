#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryTree* btree;
struct BinaryTree{
	unsigned int element;
	btree left;
	btree right;
};
/*
 *x:需要插入的值
 *t:指向树根节点的指针（输入空树）
 *func:将值x插入到t指向的二叉查找树中，如果树为空则创建一颗树，此时x作为该树的根节点。
 * 如果树不为空且树中已存在element为x的节点，则返回。
 * */
btree insert(unsigned int x, btree t)
{
	btree node;
	if(t ==NULL)
	{
		node = malloc(sizeof(struct BinaryTree));
		node->element = x;
		node->left = NULL;
		node->right = NULL;
		return node;
	}
	else if(x<t->element)
		t->left = insert(x, t->left);
	else if(x>t->element)
		t->right = insert(x, t->right);

	return t;
}
/*
 *t:指向树的根节点
 *func:找到以t为根节点的树中的所有节点的数量
 * */
unsigned int findnumberofnode(btree t)
{
	unsigned int number = 0;
	if(t==NULL)
	{
		return 0;
	}
	number ++;
	number += findnumberofnode(t->left);
	number += findnumberofnode(t->right);
	return number;
}
/*
 * 找到以t为根节点的树中所有叶子的数量
 * */
unsigned int findnumberofleafnode(btree t)
{
	unsigned int number = 0;
	if(t == NULL)
		return 0;
	if(t->left==NULL && t->right==NULL)
		number++;
	number += findnumberofleafnode(t->left);
	number += findnumberofleafnode(t->right);
	return number;
}
/*
 *找到以t为根节点的树中所有满节点的数量
 * */
unsigned int findnumberoffullnode(btree t)
{
	unsigned int number = 0;
	if(t==NULL)
		return 0;

	if(t->left && t->right)
		number++;
	number += findnumberoffullnode(t->left);
	number += findnumberoffullnode(t->right);
	return number;
}
/*
 *按照中序遍历的方式打印树中的所有节点，如果树为空则直接返回。
 * */
void print(btree t)
{
	if(t==NULL)
		return;
	print(t->left);
	printf(" %d ", t->element);
	print(t->right);
}

int main()
{
	btree t=NULL;
	t = insert(1, t);
	t = insert(6, t);
	t = insert(3, t);	
	t = insert(7, t);
	t = insert(6, t);
	print(t);printf("\n");
	printf("number of node=%d\n", findnumberofnode(t));
	printf("number of leaf node= %d\n", findnumberofleafnode(t));
	printf("number of full node=%d\n", findnumberoffullnode(t));
}
