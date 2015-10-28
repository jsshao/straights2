#ifndef PRODUCER_H
#define PRODUCER_H
#ifndef BTYPE
#define BTYPE int
#endif
#ifndef SENTINEL
#define SENTINEL -1
#endif

#include "q2buffer.h"

_Task Producer {
    void main();
    BoundedBuffer<BTYPE> *buffer;
    const int produce, delay;
  public:
    Producer( BoundedBuffer<BTYPE> &buffer, const int Produce, const int Delay );
};

#endif //PRODUCER_H
// vim: set filetype=ucpp :
