#ifndef ITERATOR_H
#define ITERATOR_H

#include <queue>
#include "struct.h"
#include "list.h"


using namespace std;

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
    dfs(_term);
  }

  T currentItem() const {
    return _dfs[_index];
  }

  bool isDone() const {
    return _index >= _dfs.size() - 1;
  }

  void next() {
    _index++;
  }

  void dfs(T term) {
    _dfs.push_back(term);

    Struct *s = dynamic_cast<Struct *>(term);
    if(s){
      for (int i=0; i<s->arity(); i++){
        dfs(s->args(i));
      }
    }

    List *l = dynamic_cast<List *>(term);
    if(l){
      for (int i=0; i<l->arity(); i++){
        dfs(l->args(i));
      }
    }
  }
private:
  int _index;
  T _term;
  vector<T> _dfs;
};

template <class T>
class BFSIterator :public Iterator<T> {
public:
  BFSIterator(T term): _index(0), _term(term) {}

  void first() {
    _index = 1;
    queue<T> q;
    q.push(_term);

    while(!q.empty()) {
      T n = q.front();
      q.pop();
      _bfs.push_back(n);

      Struct *s = dynamic_cast<Struct *>(n);
      if (s){
       for (int i = 0; i < s->arity(); i++){
        q.push(s->args(i));
       }
      }

      List *l = dynamic_cast<List *>(n);
      if(l){
        for (int i = 0; i < l->arity(); i++){
          q.push(l->args(i));
        }
      }
    }
  }

  T currentItem() const {
    return _bfs[_index];
  }

  bool isDone() const {
    return _index >= _bfs.size() - 1;
  }

  void next() {
    _index++;
  }

private:
  int _index;
  T _term;
  vector<T> _bfs;
};
#endif
