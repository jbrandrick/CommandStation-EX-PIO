
#ifndef HashList_h
#define HashList_h

template <class T>
class HashList {

  class Node;

  public:
    HashList<T> () noexcept {
      pRoot = nullptr;
      count = 0;
    };

    T*    get (int);
    T*    getOrAdd (int);
    bool  remove (int);
    int   size () {
      return count;
    }


    class Iterator;

    Iterator begin () {
      return Iterator(pRoot);
    }

    class Iterator {
      private:
        const Node* pCurrentNode;

      public:
        Iterator (const Node* pNode) noexcept :
          pCurrentNode (pNode) {};

        void next () {
          if (pCurrentNode)
            pCurrentNode = pCurrentNode->pNext;
        }
        bool hasNext () {
          return pCurrentNode != nullptr;
        }

        bool operator!= (const Iterator& iterator) {
          return pCurrentNode != iterator.pCurrentNode;
        }
        T* operator* () {
          return pCurrentNode->data;
        }
        int key () {
          return pCurrentNode->key;
        }
    };


    private:
      Node* pRoot;
      int   count;


      class Node {

        int   key;
        T*    data;
        Node* pNext;

        friend class HashList;
      };


      Node* MakeNode (int key) {
        Node* pNewNode  = new Node;
        pNewNode->key   = key;
        pNewNode->data  = new T;
        pNewNode->pNext = nullptr;

        Node* pNode     = GetRootNode ();

        if (pNode) {
          while (pNode->pNext) {
            pNode       = pNode->pNext;
          }
          pNode->pNext  = pNewNode;

        } else {
          SetRootNode (pNewNode);
        }
        count++;

        return pNewNode;
      }

      Node* GetRootNode () {
        return pRoot;
      }
      void SetRootNode (Node* pNode) {
        pRoot = pNode;
      }

};

#endif
