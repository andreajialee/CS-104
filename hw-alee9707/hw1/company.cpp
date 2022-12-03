#include <vector>
#include "company.hpp"

// Initializes the tracker with n students and their 1-person companies.
CompanyTracker::CompanyTracker(int n)
{
  numCompanies = n;
  companies = new Company* [numCompanies];
  for (int i = 0; i < numCompanies; ++i)
      companies[i] = new Company ();
}

// Deallocates all dynamically allocated memory.
CompanyTracker::~CompanyTracker()
{
  // your implementation goes here
  for(int i=0; i<numCompanies; i++){
    Company* temp = getLargest(i);
    // Deallocates merged companies
    while(temp!=companies[i]){
      split(i);
      temp = getLargest(i);
    }
    delete companies[i];
  }
  delete [] companies;
}

void CompanyTracker::merge(int i, int j)
{
  // your implementation goes here
  if (i>numCompanies-1 || j>numCompanies-1 || i<0 || j<0){
    //std::cout << "Out of bounds" << std::endl;
    return;
  }
  if(i==j){
    //std::cout << "Cannot merge, same company" << std::endl;
    return;
  }
  else if(getLargest(i) == getLargest(j)){
    //std::cout << "Cannot merge, same company" << std::endl;
    return;
  }
  Company* tempParent = new Company(getLargest(i), getLargest(j));
  getLargest(i)->parent = tempParent;
  getLargest(j)->parent = tempParent;
}

void CompanyTracker::split(int i)
{
  // your implementation goes here
  if(i>numCompanies-1 || i<0){
    //std::cout << "Out of Bounds" << std::endl;
    return;
  }
  Company* par = getLargest(i);
  if(!companies[i]->parent){
    //std::cout << "Cannot split, one person company" << std::endl;
    return;
  }
  par->merge1->parent = nullptr;
  par->merge2->parent = nullptr;
  delete par;
}

bool CompanyTracker::inSameCompany(int i, int j)
{
  // your implementation goes here
  if(i==j){
    return true;
  }
  else if(i>numCompanies-1 || j>numCompanies-1 || i<0 || j<0){
    return false;
  }
  if(getLargest(i) == getLargest(j)){
    return true;
  }
  return false;
}

Company* CompanyTracker::getLargest(int i)
{
  // your implementation goes here
  Company* cur = companies[i];
  while(cur->parent){
    cur = cur->parent;
  }
  return cur;
}
 