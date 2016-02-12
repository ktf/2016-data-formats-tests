#ifndef __MSGPACK_EDM__
#define __MSGPACK_EDM__

#include <msgpack.hpp>

class MPDigi {
public:
    int a;
    int b;
    int c;
    double d;
    double e;
    MSGPACK_DEFINE(a, b, c, d, e);
};

class MPHit {
public:
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
    MSGPACK_DEFINE(a, b, c, d, e, f, g, h, i, l);
};

#endif
