#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"
#include <queue>

template <class T>
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual T currentItem() const = 0;
  virtual bool isDone() const = 0;
};

template <class T>
class NullIterator :public Iterator<T>{
public:
  NullIterator(T n){}
  void first(){}
  void next(){}
  T currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }
};

template <class T>
class StructIterator :public Iterator<T> {
public:
  friend class Struct;
  void first() {
    _index = 0;
  }

  T currentItem() const {
    return _s->args(_index);
  }

  bool isDone() const {
    return _index >= _s->arity();
  }

  void next() {
    _index++;
  }
   StructIterator(Struct *s): _index(0), _s(s) {}
private:
  int _index;
  Struct* _s;
};

template <class T>
class ListIterator :public Iterator<T> {
public:
  ListIterator(List *list): _index(0), _list(list) {}

  void first() {
    _index = 0;
  }

  T currentItem() const {
    return _list->args(_index);
  }

  bool isDone() const {
    return _index >= _list->arity();
  }

  void next() {
    _index++;
  }
private:
  int _index;
  List* _list;
};

template <class T>
class DFSIterator :public Iterator<T> {
public:
  DFSIterator(T term): _index(0), _term(term) {}

  void first() {
    _index = 1;
    _terms.clear();
    DFS(_term);

  }

  T currentItem() const {
    return _terms[_index];
  }

  bool isDone() const {
    return _index >= _terms.size() - 1;
  }

  void next() {
    _index++;
  }

  void DFS(T term) {
    _terms.push_back(term);
    Struct *ps = dynamic_cast<Struct*>(term);
    List *pl = dynamic_cast<List*>(term);
    if (ps){
      for (int i=0;i<ps->arity();i++)
        DFS(ps->args(i));
    }
    if(pl)
    {
      for (int i=0;i<pl->arity();i++)
        DFS(pl->args(i));
    }
  }
private:
  int _index;
  T _term;
  std::vector<T> _terms;
};

template <class T>
class BFSIterator :public Iterator<T> {
public:
  BFSIterator(T term): _index(0), _term(term) {}

  void first() {
    _index = 1;
    _terms.clear();
    BFS(_term);
  }

  T currentItem() const {
    return _terms[_index];
  }

  bool isDone() const {
    return _index >= _terms.size() - 1;
  }

  void next() {
    _index++;
  }

  void BFS(T term) {
    queue<T> q;
    q.push(_term);
    while(!q.empty()) {
      T n = q.front();
      q.pop();
      _terms.push_back(n);
      Struct *ps = dynamic_cast<Struct *>(n);
      List *pl = dynamic_cast<List *>(n);
      if (ps) {
       for (int i = 0; i < ps->arity(); i++)
        q.push(ps->args(i));
      } else if (pl) {
        for (int i = 0; i < pl->arity(); i++)
          q.push(pl->args(i));
      }
    }
  }
private:
  int _index, tmp = 0;
  T _term;
  std::vector<T> _terms;
};
#endif
