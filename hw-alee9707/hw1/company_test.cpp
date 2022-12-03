#include <iostream>
#include "company.cpp"
#include "company.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  CompanyTracker test = CompanyTracker(10);
  // Testing inSameCompany first
  cout << endl << "================= COMPARISON TESTS =================" << endl << endl;
  cout << "Comparing 0 & 0" << endl;
  if(test.inSameCompany(0,0)){
      cout << "====== SAME VALUE COMPARISON TEST COMPLETE ======" << endl << endl;
  }
  cout << "Comparing 0 & 11" << endl;
  if(!test.inSameCompany(0,11)){
      cout << "====== OUT OF BOUNDS COMPARISON TEST COMPLETE ======" << endl << endl;
  }

  cout << "Merging 0 & 1" << endl;
  test.merge(0,1);
  if(test.inSameCompany(0,1)){
      cout << "Comparing 0 & 1" << endl;
      cout << "====== SAME COMPANY COMPARISON TEST COMPLETE ======" << endl << endl;
  }
  if(!test.inSameCompany(0,2)){
      cout << "Comparing 0 & 2" << endl;
      cout << "====== DIFF COMPANY COMPARISON TEST COMPLETE ======" << endl << endl;
  }
  test.split(0);

  cout << endl << "=============== OUT OF BOUNDS TESTS ===============" << endl << endl;
  // Simple Merge
  cout << "Merging 0 & 11" << endl;
  test.merge(0,11);
  cout << " ====== MERGE OUT OF BOUNDS TEST COMPLETE ======" << endl << endl;
  cout << "Splitting 11" << endl;
  test.split(11);
  cout << " ====== SPLIT OUT OF BOUNDS TEST COMPLETE ======" << endl << endl;

  cout << endl << "=============== MERGE & SPLIT TESTS ===============" << endl << endl;

  cout << "Merging 0 & 1" << endl;
  test.merge(0,1);
  if(test.inSameCompany(0,1)){
      cout << "Merged 0 & 1" << endl;
      cout << " ======= SIMPLE MERGE TEST COMPLETE =======" << endl << endl;
  }
  // Simple Split
  cout << "Splitting 0" << endl;
  test.split(0);
  if(!test.inSameCompany(0,1)){
      cout << "Split 0" << endl;
      cout << " ======= SIMPLE SPLIT TEST COMPLETE =======" << endl << endl;
  }

  // Merging Same Value Test
  cout << "Merging 0 & 0" << endl;
  test.merge(0,0);
  cout << " ======= DUPLICATE VALUE MERGE TEST COMPLETE =======" << endl << endl;

  cout << endl << "=============== MULTIPLE MERGE TESTS ===============" << endl << endl;
  // Merges 0 & 1
  test.merge(0,1);
  if(test.inSameCompany(0,1)){
      cout << "Merged 0 & 1" << endl;
  }
  // Merges 2 & 3
  test.merge(2, 3);
  if(test.inSameCompany(2, 3)){
      cout << "Merged 2 & 3" << endl;
  }
  // Merges 0 & 2
  test.merge(0, 2);
  if(test.inSameCompany(1,3)){
      cout << "Merged 0 & 3" << endl << endl;
  }

  // See if 0 & 3 are same company 
  if(test.inSameCompany(0,3)){
      cout << "0 & 3 are in same company" << endl;
      cout << " ======= MULTIPLE MERGE TEST 1 COMPLETE =======" << endl << endl;
  }
  // See if 1 & 3 are same company
  if(test.inSameCompany(1,3)){
      cout << "1 & 3 are in same company" << endl;
      cout << " ======= MULTIPLE MERGE TEST 2 COMPLETE =======" << endl << endl;
  }

  cout << endl << "================ ERROR MERGE TESTS ================" << endl << endl;

  cout << "Merging 0 & 3" << endl;
  test.merge(0,3);
  cout << " ======= SAME COMPANY MERGE TEST 1 COMPLETE =======" << endl << endl;
  cout << "Merging 1 & 3" << endl;
  test.merge(1,3);
  cout << " ======= SAME COMPANY MERGE TEST 2 COMPLETE =======" << endl << endl;

  cout << endl << "=============== MULTIPLE SPLIT TESTS ===============" << endl << endl;

  cout << "Splitting 2" << endl;
  test.split(2);
  // Just to see what companies are still merged
  if(test.inSameCompany(0,1)){
      cout << "0 & 1 still merged" << endl;
  }
    if(test.inSameCompany(0,2)){
      cout << "0 & 2 still merged" << endl;
  }
    if(test.inSameCompany(0,3)){
      cout << "0 & 3 still merged" << endl;
  }
    if(test.inSameCompany(1,2)){
      cout << "1 & 2 still merged" << endl;
  }
    if(test.inSameCompany(1,3)){
      cout << "1 & 3 still merged" << endl;
  }
    if(test.inSameCompany(2,3)){
      cout << "2 & 3 still merged" << endl;
  }
  cout << " ======= MULTIPLE SPLIT TEST 1 COMPLETE =======" << endl << endl;
  
  cout << "Splitting 2" << endl;
  test.split(2);
    if(test.inSameCompany(0,1)){
      cout << "0 & 1 still merged" << endl;
  }
    if(test.inSameCompany(0,2)){
      cout << "0 & 2 still merged" << endl;
  }
    if(test.inSameCompany(0,3)){
      cout << "0 & 3 still merged" << endl;
  }
    if(test.inSameCompany(1,2)){
      cout << "1 & 2 still merged" << endl;
  }
    if(test.inSameCompany(1,3)){
      cout << "1 & 3 still merged" << endl;
  }
    if(test.inSameCompany(2,3)){
      cout << "2 & 3 still merged" << endl;
  }
  cout << " ======= MULTIPLE SPLIT TEST 2 COMPLETE =======" << endl << endl;

  cout << "Splitting 2" << endl;
  test.split(2);
  cout << " ======= SINGLE COMPANY SPLIT TEST COMPLETE =======" << endl << endl;

  test.split(0);

    // Transitive Properties
  cout << endl << "=============== TRANSITIVE MERGE TEST ===============" << endl << endl;
  test.merge(0,1);
  cout << "Merging 0 & 1" << endl;
  test.merge(1,2);
  cout << "Merging 1 & 2" << endl;
  cout << "Comparing 0 & 2" << endl;
  if(test.inSameCompany(0,2)){
    cout << "0 & 2 have the same parent" << endl;
    cout << " ======= TRANSITIVE MERGE TEST COMPLETE =======" << endl << endl;
  }
  return 0;
}

/*

*/