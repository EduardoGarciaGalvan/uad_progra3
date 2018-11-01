#include "../Include/NodoArbolBinario.h"
#include "iostream"

NodoArbolBinario::NodoArbolBinario(int data)
{
	m_Rigth = nullptr;
	m_Left = nullptr;
}

NodoArbolBinario::~NodoArbolBinario()
{
}

bool NodoArbolBinario::insert(int data)
{
	if (data < m_Data) {
		if (m_Left == nullptr) {
			m_Left = new NodoArbolBinario(data);
			return true;
		}
		else {
			return m_Left->insert(data);
		}
	}
	else {
		if (m_Rigth == nullptr) {
			m_Rigth = new NodoArbolBinario(data);
			return true;
		}
		else {
			return m_Rigth->insert(data);
		}
	}
	return false;
}

void NodoArbolBinario::preOrder()
{
	std::cout << m_Data << " ";
	if (m_Left != nullptr) {
		m_Left->preOrder();
	}
	if (m_Rigth != nullptr) {
		m_Rigth->preOrder();
	}
}

void NodoArbolBinario::inOrder()
{
	if (m_Left != nullptr) {
		m_Left->preOrder();
	}
	std::cout << m_Data << " ";
	if (m_Rigth != nullptr) {
		m_Rigth->preOrder();
	}
}

void NodoArbolBinario::postOrder()
{
	if (m_Left != nullptr) {
		m_Left->preOrder();
	}
	if (m_Rigth != nullptr) {
		m_Rigth->preOrder();
	}
	std::cout << m_Data << " ";
}

void NodoArbolBinario::destroyTree()
{
	if (m_Left != nullptr) {
		m_Left->destroyTree();
		delete m_Left;
		m_Left = nullptr;
	}
	if (m_Rigth != nullptr) {
		m_Rigth->destroyTree();
		delete m_Rigth;
		m_Rigth = nullptr;
	}
}
