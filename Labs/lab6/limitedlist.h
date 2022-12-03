#include <iostream>
using namespace std;

class LimitedList {
      public:
        LimitedList (int capacity);
         /* creates a list fixed to this capacity. It can still grow and
            shrink with insert/remove, but if an insert would make the
            size exceed the capacity, it will throw an exception. */
        void set (int i, const string & item); // exactly the same as standard set
        const string & get (int i) const; // exactly the same as standard get
        void insert (int i, const string & item);
          /* almost the same as standard insert, except if the list is
             full, it will throw an exception rather than resizing.
             In the case of the exception being thrown, it will not alter
             the list. */
        void remove (int i); // exactly the same as standard remove
      protected:
        int find (const string & item) const;
          /* returns the first location at which item is stored in the
             list. Returns -1 if the item isn’t in the list. */
        int size () const;
          // returns the number of items currently stored in the list
      private:
        // the actual variables used to store stuff
};

class Brain : public LimitedList {
      public:
      Brain(int capacity){
          memory = LimitedList(capacity);
          max = capacity;
      }
          // create a new Brain with the given fixed capacity.
        void remember (const string & fact){
            remove(memory.find(fact));
            insert(mem,fact);
        }
          /* access the fact, i.e., mark it as freshly remembered.
             We will never ask you to remember a fact that you haven’t learned. */
        void learn (const string & fact){
            if(mem<max){
                mem++;
                insert(mem, fact);
            }
            else{
                remove(0);
                insert(mem, fact);
            }
        }
          /* add the given fact to the brain, and mark it as freshly remembered.
             If the brain is full, throw out the least recently used fact
             to make room for the newly added fact. */
        private:
            int mem = 0;
            int max;
            LimitedList memory;
};

