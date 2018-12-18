#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>
#include <string>

//using Data = std::string;

template <class T> class List {
   public:
    explicit List();
    ~List() { delete first; }

    void insert(T const& d);

    explicit List(List<T> const&);
    explicit List(List<T>&&);
    List<T>& operator=(List<T> const&);
    List<T>& operator=(List<T>&&);

   private:
    template <class L> class Link {
        public:
            explicit Link(L const& d, Link* n)
                : data(d), next(n) {}
            ~Link() { delete next; }

            friend List;

            static Link<L>* clone(Link<L> const*);

            template<class U_EXT>
            friend std::ostream& operator<<(std::ostream&, Link<U_EXT> const&);
        private:
            L data;
            Link<L>* next;
    };

    Link<T>* first;

   public:
    template <class C> class ListIterator {
        friend List;
        public:
            explicit ListIterator(Link<C>* c) : current(c) {}
            ListIterator& operator++();

            bool operator==(ListIterator<C> const& other) const;
            bool operator!=(ListIterator<C> const& other) const;
            C& operator*() const;
            C& operator->() const;
        private:
            Link<C>* current;
            void setCurrent(Link<C>* _value);
    };
    ListIterator<T> iterator_begin{first};
    ListIterator<T> iterator_end{nullptr};
    ListIterator<T>& begin();
    ListIterator<T>& end();

    template <class T_ext>
    friend std::ostream& operator<<(std::ostream&, List<T_ext> const&);
    using value_type = T;
    typedef ListIterator<T> Iterator;
};

#include "list.tcc"
#endif
