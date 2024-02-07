#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <iomanip>
#include <algorithm>
#include "db_parser.h"
#include "product_parser.h"
#include "mydatastore.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);
void buy(User* user, Product* product) ;

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    map<User*, queue<Product*>> carts;
    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
            else if (cmd == "ADD") {
              string username;
              int hitNum;
              User* user;
              if(ss >> username) {
                user = ds.getUser(username);
                if (user == NULL)
                  cout << "Invalid request" << endl;
                
                else {
                  if (ss >> hitNum) {
                    if (hitNum < 1 || hitNum > hits.size())
                      cout << "Invalid request" << endl;

                    else {
                      Product* product = hits[hitNum-1];
                      if (carts.find(user) == carts.end()) { // checks if user's cart has already been registered
                        queue<Product*> items;
                        items.push(product);
                        carts.insert(make_pair(user, items));
                      }
                      else
                        carts[user].push(product);
                    }
                  }
                  else 
                    cout << "Invalid request" << endl;
                }
              }
              else 
                cout << "Invalid request" << endl;
            }

            else if (cmd == "VIEWCART") {
              string username;
              User* user;
              if(ss >> username) {
                user = ds.getUser(username);
                if (user == NULL)
                  cout << "Invalid username" << endl;

                else {
                  queue<Product*> cart(carts[user]);
                  queue<Product*> temp;
                  int num = 1;

                  // iterating through cart
                  while (!cart.empty()) {
                    cout << "Item " << num <<endl;
                    cout << (cart.front())->displayString() << endl;
                    temp.push(cart.front());
                    cart.pop();
                    num++;
                  }

                  // placing items back into the cart
                  while (!temp.empty()) {
                    cart.push(temp.front());
                    temp.pop();
                  }
                }
              }
              else {
                cout << "Invalid username" << endl;
              }
            }

            else if (cmd == "BUYCART") {
              string username;
              User* user;
              if(ss >> username) {
                user = ds.getUser(username);
                if (user == NULL)
                  cout << "Invalid username" << endl;

                else {
                  queue<Product*> temp; // holds items that cannot be purchased
                  
                  // iterating through cart
                  while (!carts[user].empty()) {
                    // if the product is affordable and in stock
                    if ((carts[user].front())->getQty() > 0 && (carts[user].front())->getPrice() <= user->getBalance()) {
                      buy(user, carts[user].front());
                    }
                    // if the product is out of stock or too expensive
                    else {
                      temp.push(carts[user].front());
                    }
                    carts[user].pop();
                  }
                  // move all unpurchased items back into the cart
                  while (!temp.empty()) {
                    carts[user].push(temp.front());
                    temp.pop();
                  }
                }
              }
              else {
                cout << "Invalid username" << endl;
              }
            }

            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}

void buy(User* user, Product* product) 
{
  user->deductAmount(product->getPrice());
  product->subtractQty(1);
}