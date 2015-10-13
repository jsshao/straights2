#include "q1binsert.h"
#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
void Binsertsort<T>::main() {                    
    Binsertsort<T> less(Sentinel), greater(Sentinel);
    T pivot = value;         // first value passed to coroutine
    for ( ;; ) {
        suspend();

        if (value == Sentinel)
            break;

        if (value <= pivot)
            less.sort( value );
        else
            greater.sort( value );
    }

    less.sort( Sentinel );
    for ( ;; ) {
        suspend();
        value = less.retrieve();
        if ( value == Sentinel )
            break;
    }
    value = pivot;
    greater.sort( Sentinel );
    for ( ;; ) {
        suspend();
        value = greater.retrieve();
        if ( value == Sentinel )
           break; 
    }
}

void run(istream *in, ostream *out) {
    for ( ;; ) {
        int num_of_elements;
        *in >> num_of_elements;
        if (in->fail())
            break;

        Binsertsort<TYPE> sortTree(SENTINEL);
        for (int i = 0; i < num_of_elements; i++) {
            TYPE input;
            *in >> input;
            *out << input << " ";
            sortTree.sort( input );
        }

        *out << endl;
        sortTree.sort(SENTINEL);
        for (int i = 0; i < num_of_elements; i++)
            *out << sortTree.retrieve() << " ";
        *out << endl << endl;
    }
}

void uMain::main() {
    ostream *outfile = &cout;               // default value
    switch ( argc ) {
        case 3:
            try {
                outfile = new ofstream( argv[2] );
            } catch( uFile::Failure ) {
                cerr << "Error! Could not open output file \"" << argv[4] << "\"" << endl;
                exit( EXIT_FAILURE );
            } // try
            // FALL THROUGH
        case 2:
            try {
                istream *infile = new ifstream( argv[1] );
                run( infile, outfile );
                delete infile;
                if (outfile != &cout)
                    delete outfile;
            } catch( uFile::Failure ) {
                cerr << "Error: cannot open \"" << argv[1] << "\" for reading" << endl;
                exit( EXIT_FAILURE );
            } // try
            break;
        default:
            cerr << "Usage: " << argv[0] << " unsorted-file [ sorted-file ]" << endl;
            exit( EXIT_FAILURE );
    }
}
