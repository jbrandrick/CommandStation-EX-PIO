#include "HashList.h"

template <class T>
T* HashList<T>::get (int key) {
  Node* pNode = GetRootNode ();

  while (pNode) {
    if (pNode->key == key)
      return pNode->data;
    pNode = pNode->pNext;
    }

  return nullptr;
}

template <class T>
T* HashList<T>::getOrAdd (int key) {
  T* pT = get (key);

  if (pT != nullptr)
    return pT;

  return MakeNode (key)->data;
}

template <class T>
bool HashList<T>::remove (int key) {
  Node* pNode       = GetRootNode ();
  Node* pPriorNode  = nullptr;

  while (pNode != nullptr  &&  pNode->key != key) {
    pPriorNode = pNode;
    pNode  = pNode->pNext;
  }
  if (pNode == nullptr) return false;

  if (pPriorNode == nullptr) {
    SetRootNode (pNode->pNext);
  } else {
    pPriorNode->pNext = pNode->pNext;
  }
  delete pNode;

  count--;
  seq++;
  return true;
}
