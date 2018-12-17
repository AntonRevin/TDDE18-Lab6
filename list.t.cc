#include <algorithm>
#include <iostream>

#include "list.h"

template <class T>
void List<T>::insert(T const& d) {
    first = new Link<T>(d, first);
}

//-----------------------------------------------------//
// Important copy and assignment stuff
template <class T>
template <class L>
typename List<T>::template Link<L>* List<T>::Link<L>::clone(Link<L> const* dolly) {
    if (dolly != nullptr) {
        return new Link(dolly->data, clone(dolly->next));
    } else {
        return nullptr;
    }
}

template <class T>
List<T>::List() : first(nullptr) {
    std::clog << "***Default construction" << std::endl;
}

template <class T>
List<T>::List(List<T> const& l) {
    std::clog << "***Copy construction" << std::endl;
    first = Link<T>::clone(l.first);
}

template <class T>
List<T>::List(List<T>&& l) {
    std::clog << "***Move construction" << std::endl;
    first = l.first;
    l.first = nullptr;
}

template <class T>
List<T>& List<T>::operator=(List<T> const& rhs) {
    std::clog << "***Copy assignment" << std::endl;
    if (&rhs != this) {
        List copy(rhs);
        std::swap(first, copy.first);
    }
    return *this;
}

template <class T>
List<T>& List<T>::operator=(List<T>&& rhs) {
    std::clog << "***Move assignment" << std::endl;
    if (&rhs != this) {
        std::swap(first, rhs.first);
    }
    return *this;
}

/* Iterator functions */

template <class T>
template <class C>
typename List<T>::template ListIterator<C>& List<T>::ListIterator<C>::operator++() {
    current = current->next;
    return *this;
}

template <class T>
template <class C>
bool List<T>::ListIterator<C>::operator==(ListIterator<C> const& other) {
    return other.current = current;
}

template <class T>
template <class C>
bool List<T>::ListIterator<C>::operator!=(ListIterator<C> const& other) {
    return other.current != current;
}

template <class T>
typename List<T>::template ListIterator<T>& List<T>::begin() {
    iterator_begin.setCurrent(first);  // reset the iterator
    return iterator_begin;
}

template <class T>
typename List<T>::template ListIterator<T>& List<T>::end() {
    return iterator_end;
}

template <class T>
std::ostream& operator<<(std::ostream& os, typename List<T>::template Link<T> const& link) {
    os << link.data;
    return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, List<T>& list) {
    typename List<T>::template InIterator<T> it{list.begin()};
    for (; it != list.template end(); ++it)
        os << *it << " ";
    return os;
}