#include <iomanip>
#include <sstream>
#include "mydatastore.h"
#include "util.h"

using namespace std;

void MyDataStore::addProduct(Product* p)
{
  products.insert(p);
  std::set<std::string> keywords = p->keywords();

  // maps keywords to a set of products that use them
  for (std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
    // checks if keyword has already been recorded
    // if keyword is already in database, add product to corresponding set of products
    if (prodInfo.find(*it) != prodInfo.end()) 
      prodInfo[*it].insert(p);
    
    // if keyword has not been added to the database, create a new pair
    else {
      std::set<Product*> prodSet;
      prodSet.insert(p);
      prodInfo.insert(make_pair(*it, prodSet));
    }    
  }
}

void MyDataStore::addUser(User* u)
{
  users.insert(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) 
{
  std::set<Product*> allResults;
  std::set<Product*> currProds;
  
  // iterating through terms
  for (std::vector<std::string>::iterator it = terms.begin(); it != terms.end(); ++it) {
    currProds.clear();
    // checks if term is in database
    if (prodInfo.find(*it) != prodInfo.end())
      currProds = prodInfo[*it];

    // if this is the first term, all results are valid
    if (it == terms.begin()) 
      allResults.insert(currProds.begin(), currProds.end());
    
    else {
      std::set<Product*> temp;
      // finds intersection of results
      if (type == 0) 
        temp = setIntersection(allResults, currProds);
      
      // finds union of results
      else if (type == 1) 
        temp = setUnion(allResults, currProds);
        
      allResults.clear();
      allResults.insert(temp.begin(), temp.end());
    }
  }
  std::vector<Product*> retVec(allResults.begin(), allResults.end());
  return retVec;
}

void MyDataStore::dump(std::ostream& ofile)
{
  ofile << "<products>\n";
  for (std::set<Product*>::iterator it = products.begin(); it != products.end(); ++it) {
    (*it)->dump(ofile);
  }
  ofile << "</products>\n<users>\n";
  
  for (std::set<User*>::iterator it = users.begin(); it != users.end(); ++it) {
    (*it)->dump(ofile);
  }
  ofile << "</users>" << endl;
}
