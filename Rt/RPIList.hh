//
// RPIList.h - class RPIList
// KAS 91/05/16
//
#ifndef __RPIList_h
#define __RPIList_h

#include "scalar.h"
#include "Ray.hh"
#include "_RPI.hh"

class Prim;

class RPIList {
  _RPI*	first;
  _RPI*	last;
  Ray _wr;

  RPIList(_RPI* f, _RPI* l) : first(f), last(l) {}
public:
  RPIList() : first((_RPI*) RPINULL), last((_RPI*) RPINULL) {}
  RPIList(int n, const Ray& R, Prim* P, scalar T, ...);
  ~RPIList() { first = last = (_RPI*) RPINULL; }

  const Ray &wr() { return _wr; }
  void wr(const Ray &x) { _wr = x; }

  int isEmpty() const { return first == (_RPI*) RPINULL; }
  
  void delete_all();

  void insert(_RPI* p) {
    if ( p != (_RPI*) RPINULL ) {
      if ( first == (_RPI*) RPINULL )
        last = p;
      p->next(first);
      first = p;
    }
  }
  void insert(RPI* p) { insert( (_RPI*) p ); }
  void append(_RPI* p) {
    if ( p != (_RPI*) RPINULL ) {
      if ( first == (_RPI*) RPINULL ) {
        first = p;
      } else {
        last->next(p);
      }
            
      p->next((_RPI*) RPINULL);
      last = p;
    }
  }
  void append(RPI *p) { append( (_RPI*) p ); }
  void insert(RPIList &l) {
    if ( l.first != (_RPI*) RPINULL ) {
      if ( first == (_RPI*) RPINULL ) {
        first = l.first;
        last = l.last;
      } else {
        l.last->next(first);
        first = l.first;
      }
      l.first = l.last = (_RPI*) RPINULL;
    }
  }
  void append(RPIList &l) {
    if ( l.first != (_RPI*) RPINULL ) {
      if ( last == (_RPI*) RPINULL ) {
        first = l.first;
        last = l.last;
      } else {
        last->next(l.first);
        last = l.last;
      }
      l.first = l.last = (_RPI*) RPINULL;
    }
  }
  RPI *begin() { return (RPI*) first; }
  RPI *end() { return (RPI*) RPINULL; }

  void merge(RPIList &l);
  void sort();
};

#endif
