#ifndef _LIST_H_
#define _LIST_H_

#include <algorithm>
#include <iostream>
#include <string>

//using Data = std::string;

template <class T>
class List {
   public:
    explicit List();
    ~List() { delete first; }

    void insert(T const& d);

    explicit List(List<T> const&);
    explicit List(List<T>&&);
    List<T>& operator=(List<T> const&);
    List<T>& operator=(List<T>&&);

   private:
    template <class U>
    class Link {
       public:
        explicit Link(U const& d, Link<U>* n)
            : data(d), next(n) {}
        ~Link() { delete next; }

        friend /*clas*/ List /*<U>*/;

        static Link<U>* clone(Link<U> const*);

        template <class U_EXT>
        friend std::ostream& operator<<(std::ostream&, Link<U_EXT> const&);

       private:
        U data;
        Link<U>* next;
    };

    Link<T>* first;

   public:
    template <class S>
    class InIterator {
        friend List;  // To access public fields of List (iterator_begin, iterator_end, ...)
       public:
        explicit InIterator(Link<S>* c) : current(c) {
        }

        InIterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator==(InIterator<S> const& other) const { return other.current == current; }
        bool operator!=(InIterator<S> const& other) const { return other.current != current; }
        S& operator*() const { return current->data; }
        S& operator->() const { return current->data; }

       private:
        void setCurrent(Link<S>* c) { current = c; }
        Link<S>* current;
    };
    InIterator<T> iterator_begin{first};
    InIterator<T> iterator_end{nullptr};
    InIterator<T>& begin();
    InIterator<T>& end();

    template <class T_EXT>
    friend std::ostream& operator<<(std::ostream&, List<T_EXT> const&);
    using value_type = T;
    typedef InIterator<T> Iterator;
};

#include "list.t.hpp"
#endif