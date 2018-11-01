#pragma once

class NodoArbolBinario {
public:
	NodoArbolBinario(int data);
	~NodoArbolBinario();
	bool insert(int data);
	void preOrder();
	void inOrder();
	void postOrder();
	void destroyTree();
private:
	NodoArbolBinario * m_Left;
	NodoArbolBinario *m_Rigth;
	int m_Data;
};
