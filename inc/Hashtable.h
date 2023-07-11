#ifndef ORDEREDLINKEDLIST_H
#define ORDEREDLINKEDLIST_H
#include <iostream>

class Hashtable
{
   private:
      int hash(int v) const;
      int hcap;
      int hsize;
      double loadFactor;
      int* htable;
public:
	Hashtable();
	Hashtable(int);
	Hashtable(int, double);
	Hashtable(const Hashtable& other);
	Hashtable& operator=(const Hashtable& other);
	~Hashtable();

        int size() const;
        int capacity() const;
        double getLoadFactorThreshold() const;
        bool empty() const;
	    void insert(const int);
        void remove(int);
        bool contains(int) const;
        int indexOf(int) const;
        void clear();
        static bool isPrime(int n);
        static int nextPrime(int n);
};
#endif
