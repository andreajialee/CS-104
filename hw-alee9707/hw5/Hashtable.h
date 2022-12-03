#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

template <class T>
class Hashtable{
    public:
        Hashtable(bool debug = false, unsigned int size = 11);
        ~Hashtable();
        void add(std::string k, const T& val);
        const T& lookup (std::string k);
        int count(std::string k);
        void reportAll(std::ostream & ofile) const;
    private:
        bool debug;
        unsigned int size;
        void resize();
        int hash(std::string k) const;
        std::vector<std::pair<std::string,T> > vec;  // Vector stores hashtable
        int sizes[17] = {11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117};
        int rVals[5];
        int n;
};
#endif

template<typename T> 
Hashtable<T>::Hashtable(bool debug_, unsigned int size_){
    this->debug = debug_;
    this->size = size_;

    rVals[0] = 983132572;
    rVals[1] = 62337998;
    rVals[2] = 552714139;
    rVals[3] = 984953261;
    rVals[4] = 261934300;

    n = 0;  // # of elements inserted
}

template<typename T> 
Hashtable<T>::~Hashtable(){
    vec.clear(); 
}

template<typename T> 
int Hashtable<T>::hash(std::string k) const{
    int wVals[5];  
    int wPos = 4;
    std::string og = k;
    // If string length >= 6
    if(k.length()>=6){
        while(k!=""){
            long hashVal = 0;
            int power = 5;
            std::string temp;
            if(k.length()>=6){
                temp = k.substr(k.length()-6,k.length());
                k = k.substr(0,k.length()-6);
            }
            else{
                break;
                // change this later
            }
            for(unsigned int i=0; i<temp.length(); i++){
                hashVal+= pow(27,power) * (int)(temp[i]-'a'+1);
                power--;
            }
            wVals[wPos] = hashVal;
            wPos--;
        }
    }
    if(wPos>=0){    // There are still leftover chars in the strings
        int power = k.length()-1;
        long hashVal = 0;
        for(unsigned int i=0; i<k.length(); i++){
            hashVal += pow(27,power) * (int)(k[i]-'a'+1);
            power--;
        }
        wVals[wPos] = hashVal;
    }
    long long sum = 0;
    for(int i=0; i<5; i++){
        sum += rVals[i] * wVals[i];
    }
    return sum;
}

template<typename T> 
void Hashtable<T>::add(std::string k, const T& val){
    if(lookup(k)==val){
        return;
    }
    double load = (double)n/(double)size;
    if(load >= 0.5){
        this->resize();
    }
    // Insert element
    //int val = hash(k);  // REMEMBER TO MOD BY SIZE
    int hashVal = hash(k) % size;
    std::vector<std::pair<std::string,T>> tempVec(n);
    T dummy;
    for(int i=0; i<vec.size(); i++){    // Rehash values
        std::pair<std::string,T> cur = vec[i];
        int newHash = hash(cur.first);
        if(tempVec.at(newHash)==dummy){  // CHANGE!!!!!! // check if nothing there
            tempVec[newHash%size] = cur;
        }
        else{   // Collision!! Quadratic Probing
            int j = 1;
            while(vec.at(newHash%size)!=dummy){
                newHash = hash(cur.first) + j*j;
                j++;
            }
                tempVec[newHash%size] = cur;
        }
    }

}

template<typename T> 
void Hashtable<T>::resize(){
    int i = 0;
    while(n>sizes[i] && i<17){
        i++;
    }
    n = sizes[i];   // New size
    vec.resize(n);  // Resize vector
    std::vector<std::pair<std::string,T>> tempVec(n);
    T dummy;
    for(int i=0; i<vec.size(); i++){    // Rehash values
        std::pair<std::string,T> cur = vec[i];
        int newHash = hash(cur.first);
        if(tempVec.at(newHash)==dummy){  // CHANGE!!!!!! // check if nothing there
            tempVec[newHash%size] = cur;
        }
        else{   // Collision!! Quadratic Probing
            int j = 1;
            while(vec.at(newHash%size)!=dummy){
                newHash = hash(cur.first) + j*j;
                j++;
            }
                tempVec[newHash%size] = cur;
        }
    }
    vec = tempVec;
}

template<typename T>
const T& Hashtable<T>::lookup (std::string k){
    for(unsigned int i=0; i<vec.size(); i++){
        if(vec[i].first == k)
            return vec[i].second;
    }
    T temp;
    return temp;
}

template<typename T> 
void Hashtable<T>::reportAll(std::ostream & ofile) const{
    int count = 0;    // See how many values have been traversed
    T val;
    for(unsigned int i = 0; i < vec.size(); i++){
        if(vec[i].second != val){  // Check to see if there's a value there
            count++;
            if(count == n){ // If traversed all inserted values, break
                ofile << vec.at(i).first << " " << vec.at(i).second << std::endl;
                break;
            }
            else{
                ofile << vec.at(i).first << " " << vec.at(i).second << std::endl;
            }
        }
    }
}