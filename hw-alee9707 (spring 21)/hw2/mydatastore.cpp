#include "mydatastore.h"
#include "util.h"
#include <iostream>
#include <vector>
#include <deque>
#include <map>

myDataStore::~myDataStore(){
    std::map<std::string,User *>::iterator it;
    for(it = users_.begin(); it != users_.end(); it++){
        User * u = it->second;
        delete u;
    }
    std::map<std::string,std::set<Product*> >::iterator it2;
    std::set<Product*>::iterator it3;
    std::set<Product*> setProd;
    for(it2 = products_.begin(); it2!=products_.end(); it2++){
        for(it3 = it2->second.begin(); it3 != it2->second.end(); it3++){
            setProd.insert(*it3);   // Copy products_ into setProd
        }
    }
    std::set<Product*> setDel;
    std::set<Product*>::iterator it4;
    for(it4=setDel.begin(); it4!=setDel.end(); it4++){
        Product* p = *(it4);
        delete p;   // Delete products from setProd
    }
    users_.clear();
    setDel.clear();
}
void myDataStore::addProduct(Product* p){
   std::set<std::string> ans;
   std::set<std::string>::iterator it;  
   std::map<std::string,std::set<Product *> >::iterator it2; 
   ans = p->keywords(); // ans stores keywords of product
   for(it = ans.begin(); it != ans.end();it++){
       if(products_.find(*it) != products_.end()){  // Product p exists
           it2 = products_.find(*it);
           it2->second.insert(p);
       }
       else{ // New Map
           products_[*it].insert(p);
       }
   }
}
void myDataStore::addUser(User* u){
    std::deque<Product*> cart;
    users_[u->getName()] = u;
    carts_[u->getName()] = cart;
}
void myDataStore::addToCart(std::string username, Product* p){
    std::map<std::string, std::deque<Product*> >::iterator it;
    if(carts_.find(username)!=carts_.end()){    // User is found add to cart
        it = carts_.find(username);
        (it->second).push_back(p);
    }
    else{   // User is not found
        std::cout << "User Not Found" << std::endl;
    }
}
void myDataStore::viewCart(std::string username){
    std::map<std::string,std::deque<Product *> >::iterator it;
    if(carts_.find(username) != carts_.end()){ // User Found
        it = carts_.find(username);
        for(unsigned int i = 0; i < it->second.size();i++){ // Print Cart
            std::cout << (it->second[i])->displayString() << std::endl;
        }
    }
    else{   // User not found
        std::cout << "User Not Found" << std::endl;
    }
}
void myDataStore::buyCart(std::string username){
    std::map<std::string,std::deque<Product *> >::iterator it;
    std::map<std::string,User*>::iterator it2;
    std::deque<Product*> wallet;
    if(carts_.find(username) != carts_.end()){ // User found
        it = carts_.find(username);
        it2 = users_.find(username);
        for(unsigned int i = 0; i < (it->second).size(); i++){
            double amt = (it->second[i])->getPrice();   // price of item
            double bal = it2->second->getBalance(); // balance
            if((bal >= amt) && ((it->second[i])->getQty() > 0)){  // User Balance is enough + enough stock
                (it2->second)->deductAmount(amt);
                it->second[i]->subtractQty(1);
                (it->second).pop_front();
                i--;
            }
            else{ // Not enough balance or not enough stock
                wallet.push_back(it->second[i]);
                (it->second).pop_front();
                i--;
            }
        }
        it->second = wallet;
    }
}
std::vector<Product*> myDataStore::search(std::vector<std::string>& terms, int type){
    std::vector <Product*> ans;
    std::set<Product*> setAns;
    std::map<std::string,std::set<Product *> >::iterator it;
    std::set<Product *>::iterator it2;

    for(unsigned int i = 0; i < terms.size(); i++){
        if(products_.find(terms[i]) != products_.end()){
            it = products_.find(terms[i]);
            if(setAns.empty() && type == 1){  // setIntersection() & Empty
                setAns = it->second;
            }
            else if(i == 0 && type == 0){   // setUnion & type == 0
                setAns = it->second;
            }
            if(type == 0){  // setIntersection()
                setAns = setIntersection(it->second,setAns);
            }
            else if(type == 1){  //setUnion()
                setAns = setUnion(it->second,setAns);
            }
        }
        else{
            if(type == 0){ // No terms found = cleared
                setAns.clear();
                break;
            }
        }
    }
    
    for(it2 = setAns.begin();it2 != setAns.end();it2++){ // Copy setAns into ans
        ans.push_back(*it2);
    }
    return ans;
}
void myDataStore::dump(std::ostream& ofile){
    std::map<std::string,std::set<Product*> >::iterator it;
    std::set<Product*> ans;
    std::set<Product*>::iterator it2;
    std::set<Product*>::iterator it3;
    std::map<std::string, User*>::iterator it4;

    for(it=products_.begin(); it!=products_.end(); ++it){
        for(it2 = it->second.begin(); it2!=it->second.end(); ++it2){
            ans.insert(*it2);   // Every single product is added
        }
    }
    ofile << "<products> \n";  
    for(it3 = ans.begin(); it3!=ans.end(); ++it3){
        (*it3)->dump(ofile);
        ofile << "\n";
    }
    ofile << "<products>\n<users>\n";
    for(it4 = users_.begin(); it4!=users_.end(); ++it4){
        (it4->second)->dump(ofile);
    }
    ofile << "</users>\n";
}