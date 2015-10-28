#include <iostream>
#include <cstring>
#include <fstream>
#include "q1mergesort.h"
using namespace std;

#ifndef TYPE
#define TYPE int
#endif

template<typename T>
void Mergesort<T>::merge( unsigned int low, unsigned int mid, unsigned int high ) {
    // left is [low, mid ) and right is [mid, high )

    unsigned int left = low, right = mid;
    unsigned int cur = low;

    while ( cur < high ) {
        if ( right < high && ( left == mid || values[right] < values[left] )) {
            copy[cur] = values[right];
            right++;
        } else {
            copy[cur] = values[left];
            left++;
        } // if
        cur++;
    } // while 
    for ( unsigned int i = low; i < high; i++ ) {
        values[i] = copy[i];
    } // for 
} // void Mergesort<T>::merge

template<typename T>
void Mergesort<T>::main() {
    verify();
    mergesort( low, high, depth );
} // void Mergesort<T>::main

template<typename T>
void Mergesort<T>::mergesort( unsigned int low, unsigned int high, unsigned int depth ) {
    if ( high <= low + 1 ) {
        return;
    } // if 
    unsigned int mid = ( low + high ) / 2;
    if ( depth > 0 ) {
        Mergesort<T> right( values, mid, high, depth-1, copy );
        mergesort( low, mid, depth-1 );
    } else {
        mergesort( low, mid, depth );
        mergesort( mid, high, depth );
    } // if

    merge( low, mid, high );
} // void Mergesort<T>::mergesort

template<typename T>
Mergesort<T>::~Mergesort() {
    if ( low == 0 ) {
        delete copy;
    } // if 
} // Mergesort<T>::~Mergesort

unsigned int uDefaultStackSize() {
    return 512 * 1000;        // set task stack-size to 512K
} // unsigned int uDefaultStackSize

void showUsage( string name ) {
    cerr << "Usage: "<< name << " ( -s unsorted-file [ sorted-file ] | -t size ( >= 0 ) [ depth ( >= 0 ) ] )" << endl;
    exit( 1 );
} // void showUsage

void printArray( ostream& out, TYPE values[], unsigned int size ) {
    for ( unsigned int i = 0; i < size; i++ ) {
        if ( i % 22 == 0 && i != 0 ) {
            out << "\n  ";
        } // if 
        out << values[i] << " ";
    } // for 
    out << endl;
} // void printArray

void sortMode( istream& in, ostream& out ) {
    unsigned int count;
    int depth = 0;                                                        // use one processor
    while ( in >> count ) {
        TYPE *values = new TYPE[count];
        TYPE *cur = values;
        for ( unsigned int i = 0; i < count; i++ ) {
            in >> *cur;
            cur++;
        } // for
        printArray( out, values, count );
        {
            uProcessor p[ ( 1  <<  depth ) - 1  ] __attribute__( ( unused ) ); //  2^depth-1 kernel threads
            Mergesort<int> m( values, 0, count, depth );
        } // scope
        printArray( out, values, count );
        out << endl;

        delete values;
    } // while
} // void sortMode

void timeMode( unsigned int size, unsigned int depth ) {
    TYPE *values = new TYPE[size];
    TYPE *cur = values;
    for ( unsigned int i = 0; i < size; i++ ) {
        *cur = size - i;
        cur++;
    } // for
    {
        uProcessor p[ ( 1  <<  depth ) - 1  ] __attribute__( ( unused ) ); //  2^depth-1 kernel threads
        Mergesort<int> m( values, 0, size, depth );
    } // scope
    delete values;
} // void timeMode

void uMain::main() {
    if ( argc < 3 or argc > 4 ) {
        showUsage( argv[0] );
    } // if 
    if ( strcmp( argv[1], "-t" ) == 0 ) {
        int depth = 0;
        char *p;
        if ( argc == 4 ) {
            depth = strtol( argv[3], &p, 10 );
            if ( *p || depth < 0 ) {
                showUsage( argv[0] );
            } // if
        } // if 
        int size = strtol( argv[2], &p, 10 );
        if ( *p || size < 0 ) {
            showUsage( argv[0] );
        } // if
        timeMode( size, depth );
    } else if ( strcmp( argv[1], "-s" ) == 0 ) {
        ofstream outfile;
        ifstream infile;
        if ( argc == 4 ) {
            try {
                outfile.open( argv[3] );
            } catch ( ... ) {
                cerr << "Error! Could not open sorted output file \"" << argv[3] << "\"" << endl;
                showUsage( argv[0] );
            } // try 
        } // if 
        try {
            infile.open( argv[2] );
        } catch ( ... ) {
            cerr << "Error! Could not open unsorted input file \"" << argv[2] << "\"" << endl;
            showUsage( argv[0] );
        } // try 
        if ( argc == 4 ) {
            sortMode( infile, outfile );
        } else {
            sortMode( infile, cout );
        } // if
    } else {
        showUsage( argv[0] );
    } // if


} // void uMain::main

// vim: set filetype=ucpp :
