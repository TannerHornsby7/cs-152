// return true if all elements of the array are positive
int all_positive(int a[], unsigned int alen);

// return true if an element of the array is positive
int exists_positive(int a[], unsigned int alen);

// return the index of the first positive element in an array
int first_positive(int a[], unsigned int alen);

// return # of positives in an array
unsigned int number_positives(int a[], unsigned int alen);

// negate all the elements of an array in place
void negate(int a[], unsigned int alen);

// returns a new array of partial sums
int* partial_sums(int a[], unsigned int alen);

// modifies the array passed in so the elements are reversed
void reverse(int a[], unsigned int alen);

// produces a merged list from two arrays
int* merge(int* a, unsigned int alen, int* b, unsigned int blen);

// finds all primes within a given boundary
unsigned int* primes_in_range(unsigned int lb, unsigned int ub,
 unsigned int* len);