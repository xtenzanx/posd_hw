#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "term.h"
#include "atom.h"
#include "number.h"
#include "variable.h"
#include "struct.h"
#include "list.h"
#include "iterator.h"


TEST(iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term*> *itStruct = s.createIterator();
    itStruct->first();
    EXPECT_EQ("1", itStruct->currentItem()->symbol());
    EXPECT_FALSE(itStruct->isDone());
    itStruct->next();
    EXPECT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    EXPECT_FALSE(itStruct->isDone());
    itStruct->next();
    EXPECT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    EXPECT_TRUE(itStruct->isDone());
}

TEST(iterator, nested_iterator) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  StructIterator<Term*> it(&s);
  it.first();
  it.next();
  Struct *s2 = dynamic_cast<Struct *>(it.currentItem());

  StructIterator<Term*> it2(s2);
  it2.first();
  EXPECT_EQ("X", it2.currentItem()->symbol());
  EXPECT_FALSE(it2.isDone());
  it2.next();
  EXPECT_EQ("2", it2.currentItem()->symbol());
  EXPECT_FALSE(it2.isDone());
  it2.next();
  EXPECT_TRUE(it2.isDone());
}

TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    ListIterator<Term*> it(&l);
    Iterator<Term*>* itList = &it;
    itList->first();
    EXPECT_EQ("1", itList->currentItem()->symbol());
    EXPECT_FALSE(itList->isDone());
    itList->next();
    EXPECT_EQ("t(X, 2)", itList->currentItem()->symbol());
    EXPECT_FALSE(itList->isDone());
    itList->next();
    EXPECT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    EXPECT_TRUE(itList->isDone());
}

TEST(iterator, NullIterator){
  Number one(1);
  NullIterator<Term*> nullIterator(&one);
  nullIterator.first();
  EXPECT_TRUE(nullIterator.isDone());
  Iterator<Term*> * it = one.createIterator();
  it->first();
  EXPECT_TRUE(it->isDone());
}

//---Struct---

//dfs(tom, s(1, X), 2, Y)
TEST(iterator, Struct_DFS_1) {
  Atom tom("tom");
  Number n1(1);
  Number n2(2);
  Variable X("X");
  Variable Y("Y");
  Struct s(Atom("s"), { &n1, &X });
  Struct dfs(Atom("dfs"), { &tom, &s, &n2, &Y });

  Iterator<Term*> *it = dfs.createDFSIterator();
  it->first();
  EXPECT_EQ("tom", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("s(1, X)", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("1", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("X", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("2", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("Y", it->currentItem()->symbol());
  EXPECT_TRUE(it->isDone());
}

//dfs(X, s2(s1(tom, 1), 2), Y)
TEST(iterator, Struct_DFS_2) {
  Atom tom("tom");
  Number n1(1);
  Number n2(2);
  Variable X("X");
  Variable Y("Y");
  Struct s1(Atom("s1"), { &tom, &n1 });
  Struct s2(Atom("s2"), { &s1, &n2 });
  Struct dfs(Atom("dfs"), { &X, &s2, &Y });

  Iterator<Term*> *it = dfs.createDFSIterator();
  it->first();
  EXPECT_EQ("X", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("s2(s1(tom, 1), 2)", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("s1(tom, 1)", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("tom", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("1", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("2", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("Y", it->currentItem()->symbol());
  EXPECT_TRUE(it->isDone());
}

//bfs(tom, s(1, X), 2, Y)
TEST(iterator, Struct_BFS_1) {
  Atom tom("tom");
  Number n1(1);
  Number n2(2);
  Variable X("X");
  Variable Y("Y");
  Struct s(Atom("s"), { &n1, &X });
  Struct bfs(Atom("bfs"), { &tom, &s, &n2, &Y });

  Iterator<Term*> *it = bfs.createBFSIterator();
  it->first();
  EXPECT_EQ("tom", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("s(1, X)", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("2", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("Y", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("1", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("X", it->currentItem()->symbol());
  EXPECT_TRUE(it->isDone());
}

//bfs(X, s2(s1(tom, 1), 2), Y)
TEST(iterator, Struct_BFS_2) {
  Atom tom("tom");
  Number n1(1);
  Number n2(2);
  Variable X("X");
  Variable Y("Y");
  Struct s1(Atom("s1"), { &tom, &n1 });
  Struct s2(Atom("s2"), { &s1, &n2 });
  Struct bfs(Atom("bfs"), { &X, &s2, &Y });

  Iterator<Term*> *it = bfs.createBFSIterator();
  it->first();
  EXPECT_EQ("X", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("s2(s1(tom, 1), 2)", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("Y", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("s1(tom, 1)", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("2", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("tom", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("1", it->currentItem()->symbol());
  EXPECT_TRUE(it->isDone());
}

//---List---

//[tom, [1, X], 2, Y]
TEST(iterator, List_DFS_1) {
  Atom tom("tom");
  Number n1(1);
  Number n2(2);
  Variable X("X");
  Variable Y("Y");
  List l({ &n1, &X });
  List dfs({ &tom, &l, &n2, &Y });

  Iterator<Term*> *it = dfs.createDFSIterator();
  it->first();
  EXPECT_EQ("tom", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("[1, X]", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("1", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("X", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("2", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("Y", it->currentItem()->symbol());
  EXPECT_TRUE(it->isDone());
}

//[X, [[tom, 1], 2], Y]
TEST(iterator, List_DFS_2) {
  Atom tom("tom");
  Number n1(1);
  Number n2(2);
  Variable X("X");
  Variable Y("Y");
  List l1({ &tom, &n1 });
  List l2({ &l1, &n2 });
  List dfs({ &X, &l2, &Y });

  Iterator<Term*> *it = dfs.createDFSIterator();
  it->first();
  EXPECT_EQ("X", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("[[tom, 1], 2]", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("[tom, 1]", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("tom", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("1", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("2", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("Y", it->currentItem()->symbol());
  EXPECT_TRUE(it->isDone());
}

//[tom, [1, X], 2, Y]
TEST(iterator, List_BFS_1) {
  Atom tom("tom");
  Number n1(1);
  Number n2(2);
  Variable X("X");
  Variable Y("Y");
  List l({ &n1, &X });
  List bfs({ &tom, &l, &n2, &Y });

  Iterator<Term*> *it = bfs.createBFSIterator();
  it->first();
  EXPECT_EQ("tom", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("[1, X]", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("2", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("Y", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("1", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("X", it->currentItem()->symbol());
  EXPECT_TRUE(it->isDone());
}

//[X, [[tom, 1], 2], Y]
TEST(iterator, List_BFS_2) {
  Atom tom("tom");
  Number n1(1);
  Number n2(2);
  Variable X("X");
  Variable Y("Y");
  List l1({ &tom, &n1 });
  List l2({ &l1, &n2 });
  List bfs({ &X, &l2, &Y });

  Iterator<Term*> *it = bfs.createBFSIterator();
  it->first();
  EXPECT_EQ("X", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("[[tom, 1], 2]", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("Y", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("[tom, 1]", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("2", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("tom", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("1", it->currentItem()->symbol());
  EXPECT_TRUE(it->isDone());
}

#endif
