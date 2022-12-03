#include "bst.h"
#include "avlbst.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <set>

using namespace std;

/*
Fill in the slot of the given class, return true if it was successful
and return false if it was unsuccessful
*/
void scheduleHelper(int classVal, int time, int amt, map<int,int> &ans){
    if(amt<=1){
        ans[classVal]++;
        return;
    }
}
int main(int argc, char* argv[]){
    if(argc < 2){
        cout << "Error, not enough inputs" << endl;
        return 1;
    }

    ifstream f(argv[1]);
    int exams, students, timeslots, className;
    string name, line;
    map<string,set<int> > sched;    // Map of student name to schedule
    map<int,int> classes;   // Map of class name to students
    map<int,int> ans;

    // if classes is  equal to 1, just set it at 1
    // if classes have more than one student taking it, check if both students doesn't have
    // those classes which are set, then set it to 1, if else set it to 2 and so on?
    if(!f.is_open())
        return 1;
    f >> exams >> students >> timeslots;
    while(getline(f,line)){
        stringstream ss(line);
        ss >> name;
        while(ss >> className){
            sched[name].insert(className);
            classes[className]++;
        }
    }
    return 0;
}