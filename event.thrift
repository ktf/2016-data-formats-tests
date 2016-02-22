
struct TFDigi {
  1: i32 a,
  2: i32 b,
  3: i32 c, 
  4: double d, 
  5: double e
}

struct TFDigis { 
  1: list<TFDigi> a
}

struct TFDigisSoA {
  1: list<i32> a,
  2: list<i32> b,
  3: list<i32> c,
  4: list<double> d, 
  5: list<double> e
}

struct TFHit {
  1: i32 a,
  2: i32 b,
  3: double c,
  4: double d,
  5: double e,
  6: double f,
  7: double g,
  8: double h,
  9: double i,
  10: double l
}

struct TFHits { 
  1: list<TFHit> a
}

struct TFHitsSoA {
  1: list<i32> a,
  2: list<i32> b,
  
  3: list<double> c,
  4: list<double> d,
  5: list<double> e,
  6: list<double> f,
  7: list<double> g,
  8: list<double> h,
  9: list<double> i,
  10: list<double> l
}
