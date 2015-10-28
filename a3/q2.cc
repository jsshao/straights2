#include "q2buffer.h"
#include "q2consumer.h"
#include "q2producer.h"
#include "MPRNG.h"
#include <vector>
#include <iostream>

using namespace std;

MPRNG mprng;

void usageError( string name ) {
   cerr << "Usage: " << name << " [ Cons ( > 0 ) [ Prods ( > 0 ) [ Produce ( > ) [ BufferSize ( > 0 ) [ Delay ( > 0 ) ] ] ] ] ]"  << endl;
   exit( 1 );
} // void usageError

void uMain::main() {
    int cons = 5;
    int prods = 3;
    int produce = 10;
    int buffersize = 10;
    int delays = cons + prods;

    char *pt;
    switch ( argc ) {
        case 6:
            delays = strtol( argv[5], &pt, 10 );
            if ( *pt || delays <= 0 ) {
                usageError( argv[0] );
            } // if
        case 5:
            buffersize = strtol( argv[4], &pt, 10 );
            if ( *pt || buffersize <= 0 ) {
                usageError( argv[0] );
            } // if
        case 4:
            produce = strtol( argv[3], &pt, 10 );
            if ( *pt || produce <= 0 ) {
                usageError( argv[0] );
            } // if
        case 3:
            prods = strtol( argv[2], &pt, 10 );
            if ( *pt || prods <= 0 ) {
                usageError( argv[0] );
            } // if
        case 2:
            cons = strtol( argv[1], &pt, 10 );
            if ( *pt || cons <= 0 ) {
                usageError( argv[0] );
            } // if
        case 1:
            break;
        default:
            usageError( argv[0] );
    } // switch 

    #ifdef __U_MULTI__
        uProcessor p[3] __attribute__(( unused )); // create 3 kernel threads for a total of 4
    #endif // __U_MULTI__

    BoundedBuffer<BTYPE> buffer( buffersize );

    BTYPE *sums = new BTYPE[cons];
    vector<Consumer*> consumers;
    vector<Producer*> producers;

    for ( int i = 0; i < prods; i++ ) {
        producers.push_back( new Producer( buffer, produce, delays ));
    } // for 
    for ( int i = 0; i < cons; i++ ) {
        sums[i] = 0;
        consumers.push_back( new Consumer( buffer, delays, SENTINEL, sums[i] ));
    } // for 

    // wait for all producers to finish
    for ( int i = 0; i < prods; i++ ) {
        delete producers[i];
    } // for 

    for ( int i = 0; i < cons; i++ ) {
        buffer.insert( SENTINEL );
    } // for 

    BTYPE sum = 0;
    // wait for all consumers to finish
    for ( int i = 0; i < cons; i++ ) {
        delete consumers[i];
        sum += sums[i];
    } // for 

    delete[] sums;

    cout << "total: " << sum << endl;

} // void uMain::main
// vim: set filetype=ucpp :
