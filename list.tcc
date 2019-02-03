#include <algorithm>
#include <iostream>

#include "list.h"

template <class T>
void List<T>::insert(T const& d) {
    first = new Link(d, first);
}

//-----------------------------------------------------//
// Important copy and assignment stuff
template <class T>
typename List<T>::Link* List<T>::Link::clone(Link const* dolly) {
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
    first = Link::clone(l.first);
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
T& List<T>::ListIterator::operator*() const {
    return current->data;
}

template <class T>
T& List<T>::ListIterator::operator->() const {
    return current->data;
}

template <class T>
void List<T>::ListIterator::setCurrent(Link* _value) {
    current = _value;
}

template <class T>
typename List<T>::ListIterator& List<T>::ListIterator::operator++() {
    current = current->next;
    return *this;
}

template <class T>
bool List<T>::ListIterator::operator==(ListIterator const& other) const {
    return other.current = current;
}

template <class T>
bool List<T>::ListIterator::operator!=(ListIterator const& other) const {
    return other.current != current;
}

template <class T>
typename List<T>::ListIterator List<T>::begin() const {
    return ListIterator(first);
}

template <class T>
typename List<T>::ListIterator List<T>::end() const {
    return ListIterator(nullptr);
}

template <class T>
std::ostream& operator<<(std::ostream& os, const List<T>& list) {
    for (auto i : list) {
        os << i << " ";
    }
    return os;
}