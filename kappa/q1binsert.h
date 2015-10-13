#ifndef __BINSERTSORT_H__
#define __BINSERTSORT_H__

template<typename T> _Coroutine Binsertsort {
    const T Sentinel;                // value denoting end of set
    T value;                         // communication: value being passed down/up the tree
    void main();                    
  public:
    Binsertsort( T Sentinel ) : Sentinel( Sentinel ) {}
    void sort( T value ) {           // value to be sorted
        Binsertsort::value = value;
        resume();
    }
    T retrieve() {                   // retrieve sorted value
        resume();
        return value;
    }
};

#endif
