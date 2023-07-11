#include "../inc/Hashtable.h"

int Hashtable::hash(int v) const{
   return v % capacity();
}
 
Hashtable::Hashtable()
{
    //initialize values
    hcap = 17;
    hsize = 0;
    loadFactor = 0.65;
    htable = new int[hcap];
    for (int i = 0; i < hcap; i++) {
        htable[i] = -1;
    }
}

Hashtable::Hashtable(int capacity)
{
    //initialize values
    hcap = capacity;
    hsize = 0;
    loadFactor = 0.65;
    htable = new int[hcap];
    for (int i = 0; i < hcap; i++) {
        htable[i] = -1;
    }
}

Hashtable::Hashtable(int capacity, double threshold)
{
    //initialize values
    hcap = capacity;
    hsize = 0;
    loadFactor = threshold;
    htable = new int[hcap];
    for (int i = 0; i < hcap; i++) {
        htable[i] = -1;
    }
}

Hashtable::Hashtable(const Hashtable& other)
{   
    //copy over values from  other hashtable object
    hcap = other.hcap;
    hsize = other.hsize;
    loadFactor = other.loadFactor;
    htable = new int[hcap];
    for (int i = 0; i < hcap; i++) {
        htable[i] = other.htable[i];
    }
}

Hashtable& Hashtable::operator=(const Hashtable& other)
{
    //copy over values from  other hashtable object
    if (this != &other) {
        delete[] htable;
        hcap = other.hcap;
        hsize = other.hsize;
        loadFactor = other.loadFactor;
        htable = new int[hcap];
        for (int i = 0; i < hcap; i++) {
            htable[i] = other.htable[i];
        }
    }
return *this;
}

Hashtable::~Hashtable()
{
    delete[] htable;
}

int Hashtable::size() const
{
    return hsize;
}

int Hashtable::capacity() const
{
    return hcap;
}
double Hashtable::getLoadFactorThreshold() const
{
   return loadFactor;
}

bool Hashtable::empty() const
{
    return (hsize == 0);
}

void Hashtable::insert(int value)
{
    hsize++;
    //check loadfactor to see if the hashtable needs to be expanded
    double load = ((double)size()/ (double)capacity());
    if (load >= loadFactor) {
        //resize array
        int cap = nextPrime(this->hcap * 2);
        //create temp object to hash over values from original
        Hashtable tempArray(cap, this->getLoadFactorThreshold());
        for (int i = 0; i < this->hcap; i++) {
            //if a value is found in original recursively insert the value into the new temp object
            if (htable[i] != -1) {
                tempArray.insert(htable[i]);
            }
        }
        //use copy assignment operator to copy over the temp object into the original hash table
        *this = tempArray;
    }
    //insertion algorithm, tracks buckets visited, using a quadratic probe to traverse the index of the hash table
    int i = 0;
    int bucketsProbed = 0;
    int key = hash(value);
    while (bucketsProbed < capacity()) {
        if (htable[key] == -1) {
            htable[key] = value;
            break;
        }
        i++;
        bucketsProbed++;
        key = (hash(value) + (i * i)) % capacity();
    }
}

void Hashtable::remove(int value)
{
    int key = hash(value);
    int bucketsProbed = 0;
    int i = 0;
    while (bucketsProbed < capacity()) {
        if (htable[key] == value) {
            htable[key] = -1;
            hsize--;
            break;
        }
        i++;
        bucketsProbed++;
        key = (hash(value) + (i * i)) % capacity();
    }
    
}

bool Hashtable::contains(int value) const{
    int key = hash(value);
    int bucketsProbed = 0;
    int i = 0;
    while (bucketsProbed < capacity()) {
        if (htable[key] == value) {
            return true;
        }
        i++;
        bucketsProbed++;
        key = (hash(value) + (i * i)) % capacity();
    }
    return false;
}

int Hashtable::indexOf(int value) const
{
    int key = hash(value);
    int bucketsProbed = 0;
    int i = 0;
    while (bucketsProbed < capacity()) {
        if (htable[key] == value) {
            return key;
        }
        i++;
        bucketsProbed++;
        key = (hash(value) + (i * i)) % capacity();
    }
    return -1;
}

void Hashtable::clear()
{
    for (int i = 0; i < hcap; i++) {
        htable[i] = -1;
    }
    hsize = 0;
}

bool Hashtable::isPrime(int n){
    if (n == 2 || n == 3) { return true; }
    if (n == 0 || n == 1) { return false; }
    //algorithm to determine prime-ness of a number greater than 3
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) { return false; }
    }
    return true;
}

int Hashtable::nextPrime(int n){
    if (isPrime(n)) { return n; }
    else {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }
}
