#pragma once

#include "CApp.h"
#include "NodoArbolBinario.h"

template <class T>
class ArbolBinario : public CApp {
public:
	ArbolBinario();
	~ArbolBinario();
	bool insert(T data);
	void preOrder();
	void inOrder();
	void postOrder();
	void destroyTree();
private:
	NodoArbolBinario<T> * m_root;
};
