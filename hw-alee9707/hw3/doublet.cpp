#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <cctype>
#include "MinHeap.h"

std::string upperCase(std::string word){
    for(int i=0; i<(int)word.length(); i++){
        word[i] = std::toupper(word[i]);
    }
    return word;
}

int returnH(std::string first, std::string second){
    int h = 0;
    for(unsigned int i=0; i<first.length(); i++){
        if(first[i]!=second[i]){
            h++;
        }
    }
    return h;
}

std::string tieBreaker(std::string first, std::string second){
    if(first.compare(second) < 0)
        return first;
    else
        return second;
}

int main(int argc, char* argv[]){
    // Check if enough inputs
    if(argc < 4){
        std::cout << "Error, not enough inputs" << std::endl;
        return 1;
    }
    // Create file stream
    std::fstream file; file.open(argv[3]);
    int n;
    file >> n;
    // Check file stream
    if(file.fail()){
        std::cout << "Error, incorrect inputs" << std::endl;
        return 1;
    }
    // Instantiate maps, sets, and etc.
    std::string first = upperCase(argv[1]);
    std::string second = upperCase(argv[2]);
    MinHeap<std::string> open(2);        // Create heap 
    std::set<std::string> words;         // Set of all words
    std::set<std::string> closed;        // Set of words accessed
    std::map<std::string,int> g;         // Keeps track of g values
    std::set<std::string> added;          // Keeps track of when word was added
    int exp = 0;                         // Amount of expansions
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";           // String of letters to switch out
    std::set<char> letters;              // Use set so letters aren't duplicated 

    // Take in words from file
    std::string word;
    while(file >> word){
        word = upperCase(word);
        if(word.length()>second.length() || word.length()<second.length()){
            continue;           // Ignore words of diff length
        }
        words.insert(word);     // Add words from txt file into set of words
    }
    // Begin A* Search by added start node
    open.add(first, 0);
    added.insert(first);
    g[first] = 0;
    // A* Search
    while (!open.isEmpty()) {
        // curr = top of heap
        std::string curr = open.peek();
        // If at goal, search is done
        if (curr == second) {
            std::cout << g[curr] << std::endl;
            std::cout << exp << std::endl;
            return 0;
        }
        open.remove();              // Remove curr node
        closed.insert(curr);        // Add curr node to explored list
        exp++;                      // Increment amt of expansions

        // Generate neighbors of the node & find priority
        for (unsigned int i = 0; i < curr.length(); i++) {
            for (unsigned int j = 0; j < alphabet.length(); j++) {    
                std::string temp = curr;
                temp[i] = alphabet[j];
                // Check if word is valid
                if (words.find(temp) == words.end()){   // Word doesn't exist
                    continue;
                }
                
                if (closed.find(temp) != closed.end()) {
                    continue;
                }
                int h = returnH(temp,second);
                // Calculate priority 
                g[temp] = g[curr] + 1;
                int f = h + g[temp];
                int priority = f * (temp.length() + 1) + h;
                
                if(added.find(temp)!=added.end()){
                    open.update(temp, priority);
                }
                // If not added
                else {
                    added.insert(temp);
                    open.add(temp, priority);
                }
            }
        }
    }

    std::cout << "No transformation" << std::endl;
    std::cout << exp << std::endl;
    return 0;
}