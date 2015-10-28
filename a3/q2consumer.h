#ifndef CONSUMER_H
#define CONSUMER_H
#ifndef BTYPE
#define BTYPE int
#endif
#ifndef SENTINEL
#define SENTINEL -1
#endif

#include "q2buffer.h"

_Task Consumer {
    void main();
    BoundedBuffer<BTYPE> *buffer;
    const int delay;
    const BTYPE sentinel;
    BTYPE *sum;
  public:
    Consumer( BoundedBuffer<BTYPE> &buffer, const int Delay, const BTYPE Sentinel,
                BTYPE &sum );
};
#endif // CONSUMER_H

// vim: set filetype=ucpp :
