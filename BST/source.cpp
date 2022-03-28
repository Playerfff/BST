#include <iostream>
#include <string.h>
using namespace std;

struct BSTnode
{
	int key = 0;
	BSTnode* left = NULL;
	BSTnode* right = NULL;
};

BSTnode* search(BSTnode* t, int k)//在BST中查找key==k的节点，并返回该节点
{
	if (t == NULL || t->key == k) return t;
	if (k < t->key) return search(t->left, k);
	if (k > t->key) return search(t->right, k);
}

void insert(BSTnode*& t, int k)
{
	if (t == NULL)
	{
		t = new BSTnode;
		t->key = k;
	}
	else if (k < t->key)
		insert(t->left, k);
	else if (k > t->key)
		insert(t->right, k);
	else if (k == t->key)
		return;
}

inline BSTnode* find_tree_min(BSTnode* t)
{
	while (t->left != NULL)
	{
		t = t->left;
	}
	return t;
}

inline BSTnode* find_tree_min(BSTnode* t, BSTnode* u)
{
	if (t == u)return NULL;
	while (t->left != u)
	{
		t = t->left;
	}
	return t;
}

void del(BSTnode*& t, int k)
{
	BSTnode* p, * m;//找k
	p = m = t; bool flag = true;
	while (p != NULL && p->key != k)
	{
		m = p;
		if (k < p->key)
		{
			p = p->left;
			flag = true;
		}
		else
		{
			p = p->right;
			flag = false;
		}
	}//p指向k节点，m是p的父节点（p==m时根节点是key==k）
	if (p == NULL) return;//BST中没有key==k的节点,或者是对空树删除从这里出
	if (p->left == NULL && p->right == NULL)//情况1，p为叶节点
	{
		if (m == p)
		{
			t = NULL;
			return;
		}
		if (flag)
			m->left = NULL;
		else
			m->right = NULL;
		return;
	}
	if (p->left == NULL)//情况2，p只有一个孩子
	{
		if (m == p)
		{
			t = t->right;
			return;
		}
		p = p->right;
		if (flag)
			m->left = p;
		else
			m->right = p;
		return;
	}
	if (p->right == NULL)
	{
		if (m == p)
		{
			t = t->left;
			return;
		}
		p = p->left;
		if (flag)
			m->left = p;
		else
			m->right = p;
		return;
	}
	//情况3，k有2个孩子
	BSTnode* u = find_tree_min(p->right);
	if (m != p)
	{
		if (flag)
			m->left = u;
		else
			m->right = u;
		BSTnode* r = u->right;
		BSTnode* j = find_tree_min(p->right, u);
		if (j != NULL)
		{
			j->left = r;
			u->left = p->left;
			u->right = p->right;
		}
		else
		{
			u->left = p->left;
		}
		return;
	}
	else
	{
		BSTnode* r = u->right;
		BSTnode* j = find_tree_min(p->right, u);
		j->left = r;
		u->left = p->left;
		u->right = p->right;
		t = u;
		return;
	}
}

void print_midorder(BSTnode* t)
{
	if (t == NULL) return;
	print_midorder(t->left);
	printf("%d ", t->key);
	print_midorder(t->right);
}

void print_firstorder(BSTnode* t)
{
	if (t == NULL) return;
	printf("%d ", t->key);
	print_firstorder(t->left);
	print_firstorder(t->right);
}

int main()
{
	int T; string wd; int val;
	cin >> T;
	BSTnode* t = NULL;
	while (T > 0)
	{
		cin >> wd >> val;
		if (wd == "Insert")
			insert(t, val);
		if (wd == "Remove")
			del(t, val);
		T--;
	}
	print_midorder(t);
	printf("\n\n");
	print_firstorder(t);
	printf("\n");
	return 0;
}