#pragma once
#include "../lib_Queue/queue.h"
#include <iostream>

template <typename TKey, typename TValue>
struct Node {
	T data;
	Node* left, * right;
};
template <typename TKey, typename TValue>
class Tree
{
	Node<TKey, TValue> * _root;
	public:
	Tree();
	~Tree();
	void insert(const TKey&, const TValue&); //?
	TValue* find(const TKey&) const noexcept;
	void erase(const TKey&);
	bool is_empty() const noexcept;
	void clear() noexcept;//+clear_rec

	void print_w() const noexcept;
	void print_dlcr()const noexcept;
	void print_dlrc()const noexcept;
	void print_dclr()const noexcept;
	void print_dlcr_rec(Node<TKey, TValue>*);
	void print_dlrc_rec(Node<TKey, TValue>*);
	void print_dclr_rec(Node<TKey, TValue>*);
};
template<typename TKey, typename TValue>
Tree<TKey, TValue>::Tree()
{
}

template <typename TKey, typename TValue>
void Tree<TKey, TValue>::print_w() const noexcept{
	if(is_empty())
		Return;
	Queue<Node*> q;
	Node* cur = nullptr;
	q.push* (_root);
	while (!q.is_empty()) {
		Cur = q.top();
		Std::cout << cur->data.second << У Ф;
		q.pop();
		if (cur->left) {
			q.push(cur->left);
		}
		if (cur->right) {
			q.push(cur->right);
		}
	}
}
template <typename TKey, typename TValue>
void Tree<TKey, TValue>::print_dclr_rec(Node<TKey, TValue>* node) {
	if(node == nullptr) //чтобы не стартовали пустые рекурсии
		return;
	Std::cout << node->deta.second << У Ф;
	print_ dclr_rec(node->left); // здесь добавить if
	print_ dclr_rec(node->right); // здесь добавить if
}
template <typename TKey, typename TValue>
void Tree<TKey, TValue>::print_dlcr_rec(Node<TKey, TValue>* node) {
	if(node == nullptr) //чтобы не стартовали пустые рекурсии
		return;
	print_dclr_rec(node->left); // здесь добавить if
	std::cout << node->deta.second << У Ф;
	print_dclr_rec(node->right); // здесь добавить if
}

template <typename TKey, typename TValue>
void Tree<TKey, TValue>::print_dlrc_rec(Node<TKey, TValue>* node) {
	if(node == nullptr) //чтобы не стартовали пустые рекурсии
		return;
	print_dclr_rec(node->left); // здесь добавить if
	std::cout << node->deta.second << У Ф;
	print_dclr_rec(node->right); // здесь добавить if
}

template <typename TKey, typename TValue>
void Tree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	Node* node = new Node(key, value);
	if(is_empty()) {
		_root = node;
		Return;
	}
	Node* cur = nullptr;
	Queue<Node*> q;
	q.push(_root);
	while(1) {
		Cur = q.top();
		q.pop();
		if(!cur->left) {
			cur->left = node;
		}
		if(!cur->right) {
			Cur->right = node;
			q.push(cur->left);
			q.push(cur->right);
		}

	}
}


