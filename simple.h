#include "TObject.h"
#include <vector>

class Digi : public TObject
{ 
public:
  Digi()
  : a(rand()),b(rand()),c(rand()), d(rand()),e(rand())
  {}
  int a;
  int b;
  int c;
  double d;
  double e;
  ClassDef(Digi,1);
};

class Hit : public TObject
{
public:
  Hit()
  : a(rand()),b(rand()),c(rand()), d(rand()),e(rand()),f(rand()),g(rand()),h(rand()),i(rand()),l(rand())
  {}
  int a;
  int b;
  double c;
  double d;
  double e;
  double f;
  double g;
  double h;
  double i;
  double l;
  ClassDef(Hit,1);
};

class ArrayOfDigi : public TObject {
public:
  std::vector<Digi> digis;
  ClassDef(ArrayOfDigi,1);
};

class ArrayOfHits : public TObject {
public:
  std::vector<Hit> hits;
  ClassDef(ArrayOfHits,1);
};

class StructureOfDigis: public TObject {
public:
  StructureOfDigis() {}
  StructureOfDigis(int s) {
    for(int i = 0; i < s; ++i)
    {
      a.push_back(rand());
      b.push_back(rand());
      c.push_back(rand());
      d.push_back(rand());
      e.push_back(rand());
    }
  }
  std::vector<int> a;
  std::vector<int> b;
  std::vector<int> c;
  std::vector<double> d;
  std::vector<double> e;
  ClassDef(StructureOfDigis,1);
};

class StructureOfHits: public TObject {
public:
  StructureOfHits() {}
  StructureOfHits(int s) {
    for(int ii = 0; ii < s; ++ii)
    {
      a.push_back(rand());
      b.push_back(rand());
      c.push_back(rand());
      d.push_back(rand());
      e.push_back(rand());
      f.push_back(rand());
      g.push_back(rand());
      h.push_back(rand());
      i.push_back(rand());
      l.push_back(rand());
    }
  }
  std::vector<int> a;
  std::vector<int> b;
  std::vector<double> c;
  std::vector<double> d;
  std::vector<double> e;
  std::vector<double> f;
  std::vector<double> g;
  std::vector<double> h;
  std::vector<double> i;
  std::vector<double> l;
  ClassDef(StructureOfHits, 1);
};
