#include "q2producer.h"
#include "MPRNG.h"
extern MPRNG mprng;

void Producer::main() {
    for ( int i = 1; i <= produce; i++ ) {
        yield( mprng( delay ));             // delay for a random duration
        buffer->insert( BTYPE(i) );
    } // for 
} // void Producer::main

Producer::Producer( BoundedBuffer<BTYPE> &buffer, const int Produce, const int Delay ) : 
    buffer( &buffer ), produce( Produce ), delay( Delay ) {}

// vim: set filetype=ucpp :
