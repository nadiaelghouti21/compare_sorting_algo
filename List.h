#pragma once
#ifndef LIST_H_
#define LIST_H_

template <class Key, class Value>
class List;     // Incomplete declaration.

template <class Key, class Value>
class ListItr;     // Incomplete declaration.

template <class Key, class Value>
class  ListNode
{
    Key element;
    Value item;
    ListNode* next;

    ListNode() : element(), item(), next(nullptr) {};
    ListNode(const Key& theElement, const Value& i, ListNode* n = NULL)
        : element(theElement), item(i), next(n) { }  // Constructor 



    friend class List< Key, Value>;
    friend class ListItr< Key, Value>;
};


template <class Key, class Value>
class ListItr
{
public:
    ListItr() : current(NULL) { }
    bool isPastEnd() const
    {
        return current == NULL;
    }
    void advance()
    {
        if (!isPastEnd())   current = current->next;
    }
    const Value& retrieve_v() const
    {
        if (isPastEnd())    throw - 1;
        return current->item;
    }
    const Key& retrieve_k() const
    {
        if (isPastEnd())    throw - 1;
        return current->element;
    }

private:
    ListNode <Key, Value>* current;    // Current position

    ListItr(ListNode<Key, Value>* theNode)
        : current(theNode) { }

    friend class List<Key, Value>;    // Grant access to constructor
};
template <class Key, class Value>
class List
{
public:
    List() {
        header = new ListNode<Key, Value>;
    }


    List(const List& rhs) {
        header = new ListNode<Key, Value>;
        *this = rhs;  // Deep Copy
    }

    ~List() {
        /*makeEmpty();  // Get rid of all list nodes
        delete header;  // then get rid of the header*/
    }


    bool isEmpty() const {
        return header->next == NULL;
    }


    void makeEmpty() {
        while (!isEmpty())
            remove(first().retrieve_k());
    }


    ListItr<Key, Value> zeroth() const {
        return ListItr<Key, Value>(header);
    }


    ListItr<Key, Value> first() const {
        return ListItr<Key, Value>(header->next);
    }

    ListItr<Key, Value> findPrevious(const Key& x) const {
        ListNode<Key, Value>* itr = header;

        while (itr->next != NULL && itr->next->element != x)
            itr = itr->next;

        if (itr->next == NULL) {
            // x was not found in the list, or we reached the end of the list
            // You may want to handle this case accordingly, such as returning a special iterator
            // or throwing an exception
            return ListItr<Key, Value>(nullptr);
        }

        return ListItr<Key, Value>(itr);
    }


    void insert(const Key& w, const Value& x, const ListItr<Key, Value>& p) {
        if (p.current != NULL)
            p.current->next = new ListNode<Key, Value>(w, x, p.current->next);
    }

    ListItr<Key, Value> find(const Key& x) const
    {
        ListNode<Key, Value>* itr = header->next; // Initialize

        while (itr != NULL && itr->element != x)
            itr = itr->next;

        return ListItr<Key, Value>(itr);
    }


    void remove(const Key& x) {
        ListItr<Key, Value> p = findPrevious(x); // Locate previous of x, if any

        if (p.current->next != NULL)
        {
            ListNode<Key, Value>* oldNode = p.current->next;
            p.current->next = p.current->next->next;  // Bypass deleted node
            delete oldNode;
        }
    }




private:
    ListNode<Key, Value>* header;
};


#endif