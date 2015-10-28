#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <cassert>

template<typename T> class BoundedBuffer {
    T* buffer;
    unsigned int size, index;
    bool produceInUse, consumeInUse, signalBarge;
    uCondLock notEmpty, notFull, notBarging;
    uOwnerLock mutex;
  public:
    BoundedBuffer( const unsigned int size = 10 );
    ~BoundedBuffer();
    void insert( T elem );
    T remove();
};

#ifdef BUSY                            // busy waiting implementation
template<typename T>
BoundedBuffer<T>::BoundedBuffer( const unsigned int size ) : size( size ), index( 0 ) {
    buffer = new T[size];
} // BoundedBuffer<T>::BoundedBuffer

template<typename T>
void BoundedBuffer<T>::insert( T elem ) {
    mutex.acquire();
    while ( index == size ) {
        notFull.wait( mutex );
    } // while 
    assert( index != size );            // check there is space
    buffer[index] = elem;
    index++;
    notEmpty.signal();
    mutex.release();
} // void BoundedBuffer<T>::insert

template<typename T>
T BoundedBuffer<T>::remove() {
    mutex.acquire();
    while ( index == 0 ) {
        notEmpty.wait( mutex );
    } // while 
    assert( index != 0 );               // check there is an item to remove
    index--;
    T value = buffer[index];
    notFull.signal();
    mutex.release();
    return value;
} // T BoundedBuffer<T>::remove

template<typename T>
BoundedBuffer<T>::~BoundedBuffer() {
    delete buffer;
} // BoundedBuffer<T>::~BoundedBuffer
#endif // BUSY

#ifdef NOBUSY                        // no busy waiting implementation
template<typename T>
BoundedBuffer<T>::BoundedBuffer( const unsigned int size ) : size( size ), index( 0 ), produceInUse( false ), consumeInUse( false ), signalBarge( false ) {
    buffer = new T[size];
} // BoundedBuffer<T>::BoundedBuffer

template<typename T>
void BoundedBuffer<T>::insert( T elem ) {
    mutex.acquire();
    if ( produceInUse || consumeInUse || signalBarge ) {
        notBarging.wait( mutex );
        signalBarge = false;
    } // if 
    if ( index == size ) {
        if ( !notBarging.empty() ) {
            signalBarge = true;
            notBarging.signal();
        } // if 
        notFull.wait( mutex );
        produceInUse = false;
    } // if 
    assert( index != size );        //check there is space 
    buffer[index] = elem;
    index++;
    if ( !notEmpty.empty() ) {
        consumeInUse = true;
        notEmpty.signal();
    } else if ( !notBarging.empty() ) {
        signalBarge = true;
        notBarging.signal();
    } // if 
    mutex.release();
} // void BoundedBuffer<T>::insert

template<typename T>
T BoundedBuffer<T>::remove() {
    mutex.acquire();
    if ( produceInUse || consumeInUse || signalBarge ) {
        notBarging.wait( mutex );
        signalBarge = false;
    } // if 
    if ( index == 0 ) {
        if ( !notBarging.empty() ) {
            signalBarge = true;
            notBarging.signal();
        } // if 
        notEmpty.wait( mutex );
        consumeInUse = false;
    } // if 
    assert( index != 0 );       // check we have an item to remove
    index--;
    T value = buffer[index];
    if ( !notFull.empty() ) {
        produceInUse = true;
        notFull.signal();
    } else if ( !notBarging.empty() ) {
        signalBarge = true;
        notBarging.signal();
    } // if 
    mutex.release();
    return value;
} // T BoundedBuffer<T>::remove

template<typename T>
BoundedBuffer<T>::~BoundedBuffer() {
    delete buffer;
} // BoundedBuffer<T>::~BoundedBuffer

#endif // NOBUSY
#endif // BOUNDED_BUFFER_H
// vim: set filetype=ucpp :
