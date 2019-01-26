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
 *返回值有以下两种情况：
 1.如果t没有右儿子则返回t
 2.如果t有右儿子则返回t中element最大的节点的父节点
 * */
btree findmaxnodeparent(btree t)
{
	btree tmp = NULL;
	btree x=NULL,p=NULL;
	//t为空树
	if(t==NULL)
		return NULL;
	tmp = t;
	//如果t没有右子树，直接返回t
	if(tmp->right==NULL)
		return tmp;
	//t有右子树
	p = tmp;
	x = p->right;
	//判断x是否为最右的节点了
	while(x->right)
	{
		p = p->right;
		x = x->right;
	}
	//此时x是t中最大的节点,p是x的父节点
	return p;
}
/*
 *从以t为根的二叉查找树中删除element为x的节点
 * */
btree delete(unsigned int x, btree t)
{
	btree p=NULL, x_=NULL;//没想好合适的命名。。。
	if(t == NULL)
		return NULL;
	//t为待删除的节点的指针
	if(x == t->element)
	{
		//删除的节点无左子树，则直接删除节点t，且将t赋值为t的右子树的根节点的指针。
		if(t->left == NULL)
		{
			t = t->right;
			return t;
		}
		//t有左子树的情况
		p = findmaxnodeparent(t->left);
		//如果t的左子树没有右儿子
		if(p->right==NULL)
		{
			p->right = t->right;
			t = p;
			return t;
		}
		//t的左子树有右儿子的情形
		else if(p->right != NULL)
		{
			//保存准备替换到删除节点t位置的节点x信息
			x_ = p->right;
			//将p的右子树设置为x的左子树
			p->right = p->right->left;
			//将x的左子树设置为t的左子树
			x_->left = t->left;
			//将x的右子树设置为t的右子树
			x_->right = t->right;
			//t设置成x返回
			t = x_;
			return t;
			
		}

	}
	//没有找到element为x的节点则继续遍历
	else if(x<t->element)
		t->left = delete(x, t->left);
	else 
		t->right = delete(x, t->right);

	return t;
}
/*
 *寻找二叉查找树t中最大的节点
 * */
btree findmax(btree t)
{
	if(t == NULL)
		return NULL;
	while(t->right)
	{
		t = t->right;		
	}
	return t;
}
/*
 *寻找二叉查找树t中最小的节点
 * */
btree findmin(btree t)
{
	if(t == NULL)
		return NULL;
	while(t->left)
	{
		t = t->left;
	}
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
	print(t);printf("\n");
/*	t = delete(6, t);
	print(t);printf("\n");
	t = delete(3, t);
	print(t);printf("\n");
	t = delete(1, t);
	print(t);printf("\n");
	t = delete(7, t);
	print(t);printf("\n");
	if(t==NULL)
	{	
		printf("t is a empty tree\n");
		return 0;
	}*/
	if(t != NULL)
	{
		printf("the max node's element=%d\n",findmax(t)->element);
		printf("the min node's element=%d\n",findmin(t)->element);
	}
	//printf("number of node=%d\n", findnumberofnode(t));
	//printf("number of leaf node= %d\n", findnumberofleafnode(t));
	//printf("number of full node=%d\n", findnumberoffullnode(t));
}
