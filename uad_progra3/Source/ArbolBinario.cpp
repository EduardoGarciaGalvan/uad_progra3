#include "../Include/ArbolBinario.h"

template <class T>
ArbolBinario<T>::ArbolBinario()
{
	m_root = nullptr;
}

template <class T>
ArbolBinario<T>::~ArbolBinario()
{
	destroyTree();
}

template <class T>
bool ArbolBinario<T>::insert(T data)
{
	bool inserted = false;
	if (m_root == nullptr) {
		m_root = new NodoArbolBinario(data);
		inserted = true;
	}
	else {
		inserted = m_root->insert(data);
	}
	return inserted;
}

template <class T>
void ArbolBinario<T>::preOrder()
{
	if (m_root != nullptr) {
		m_root->preOrder();
	}
}

template <class T>
void ArbolBinario<T>::inOrder()
{
	if (m_root != nullptr) {
		m_root->inOrder();
	}
}

template <class T>
void ArbolBinario<T>::postOrder()
{
	if (m_root != nullptr) {
		m_root->postOrder();
	}
}

template <class T>
void ArbolBinario<T>::destroyTree()
{
	if (m_root != nullptr) {
		m_root->destroyTree();
		delete m_root;
		m_root = nullptr;
	}
}
