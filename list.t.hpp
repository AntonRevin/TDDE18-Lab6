template <class T>
void List<T>::insert(T const& d) {
    first = new Link<T>(d, first);
}

template <class T>
template <class U>
typename List<T>::template Link<U>* List<T>::Link<U>::clone(Link<U> const* other) {
    if (other != nullptr)
        return new Link(other->data, clone(other->next));
    else
        return nullptr;
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
        List<T> copy(rhs);
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

template <class T>
typename List<T>::template InIterator<T>& List<T>::begin() {
    iterator_begin.setCurrent(first);  // reset Iterator
    return iterator_begin;
}

template <class T>
typename List<T>::template InIterator<T>& List<T>::end() {
    return iterator_end;
}

template <class T>
std::ostream& operator<<(std::ostream& os, typename List<T>::template Link<T> const& link) {
    os << link.data;
    return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, List<T>& list)  // no const by design
{
    typename List<T>::template InIterator<T> it{list.begin()};
    for (; it != list.template end(); ++it)
        os << *it << " ";
    return os;
}