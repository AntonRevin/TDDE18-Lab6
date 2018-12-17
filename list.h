#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>
#include <string>

//using Data = std::string;

template <class T>
class List {
public:
  List();
  ~List() { delete first; }

  void insert(T const& d);
  
  List(List<T> const&);
  List(List<T>&&);
  List<T>& operator=(List<T> const&);
  List<T>& operator=(List<T>&&);
    
private:

  template <class L>
  class Link {
  public:
    Link(L const& d, Link* n)
      : data(d), next(n) {}
    ~Link() { delete next; }
    
    friend class List;

    static Link<L>* clone(Link<L> const*);
    
  private:
    L data;
    Link<L>* next;
  };
  
  Link<T>* first;
  
public:

  template <class C>
  class ListIterator {
    friend List;
    public:
      explicit ListIterator(Link<C>* c) : current(c) { }
      ListIterator& operator++();

      bool operator==(ListIterator<C> const& other);
      bool operator!=(ListIterator<C> const& other);
      C& operator*();
      C& operator->();

    private:
      Link<C>* current;
      void setCurrent(Link<C>* _value);
  };
  ListIterator<T> iterator_begin{first};
  ListIterator<T> iterator_end{nullptr};
  ListIterator<T>& begin();
  ListIterator<T>& end();

  typedef ListIterator<T> Iterator;
  
};

#endif
