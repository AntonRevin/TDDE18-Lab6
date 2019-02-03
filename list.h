#ifndef _LIST_H_
#define _LIST_H_

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
    class Link {
       public:
        explicit Link(T const& d, Link* n)
            : data(d), next(n) {}
        ~Link() { delete next; }

        friend List;

        static Link* clone(Link const*);

       private:
        T data;
        Link* next;
    };

    Link* first;

   public:
    using value_type = T;
    class ListIterator {
        friend List;

       public:
        ListIterator& operator++();
        bool operator==(ListIterator const& other) const;
        bool operator!=(ListIterator const& other) const;
        T& operator*() const;
        T& operator->() const;

       private:
        explicit ListIterator(Link* c) : current(c) {}
        Link* current;
        void setCurrent(Link* _value);
    };
    ListIterator begin() const;
    ListIterator end() const;

    template <class T_ext>
    friend std::ostream& operator<<(std::ostream&, const List<T_ext>&);
    typedef ListIterator Iterator;
};

#include "list.tcc"
#endif
