#include <iostream>
#include <string>

// Helper Function
void permute(std::string in, int pos){
    // If position = size of length, reached end = no more permutations
    if(pos==in.length()){
        std::cout << in << std::endl;
    }
    else{
        for(int i=pos; i<in.length(); i++){
            std::swap(in[i], in[pos]);  // Swap current i char with pos
            permute(in, pos+1); // Continue to go until end of the string in
            std::swap(in[i], in[pos]);  // Backtrace
        }
    }
}
void permutations(std::string in){
    permute(in, 0);
}
