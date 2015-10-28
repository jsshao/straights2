#include "q2consumer.h"
#include "MPRNG.h"
extern MPRNG mprng;
void Consumer::main() {
    for ( ;; ) {
        yield( mprng( delay ));             // delay for a random duration
        BTYPE value = buffer->remove();
      if ( value == sentinel ) break;
        *sum += value;
    } // for 
} // void Consumer::main

Consumer::Consumer( BoundedBuffer<BTYPE> &buffer, const int Delay, const BTYPE Sentinel, BTYPE &sum ) :
    buffer( &buffer ), delay( Delay ), sentinel( Sentinel ), sum( &sum ) {}
// vim: set filetype=ucpp :
