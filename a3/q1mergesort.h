#ifndef Q1MERGESORT
#define Q1MERGESORT

template<typename T> _Task Mergesort {
    T* values, *copy;
    unsigned int low, high, depth;
    void main();
    Mergesort( T values[], unsigned int low, unsigned int high, unsigned int depth, T copy[] ) : values( values ), copy( copy ), low( low ), high( high ), depth( depth ) {}
    void merge( unsigned int low, unsigned int mid, unsigned int high );
    void mergesort( unsigned int low, unsigned int high, unsigned int depth );
  public:
    Mergesort( T values[], unsigned int low, unsigned int high, unsigned int depth ) : values( values ), low( low ), high( high ), depth( depth ) {
        copy = new int[high-low]; 
    }
    ~Mergesort();
};

#endif
// vim: set filetype=ucpp :
