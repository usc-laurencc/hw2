#include <set>
#include <vector>
#include <string>
#include <map>
#include "datastore.h"
#include "user.h"

class MyDataStore : public DataStore {
public:
  MyDataStore();
  ~MyDataStore();
  void addProduct(Product* p);
  void addUser(User* u);
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  void dump(std::ostream& ofile);
  User* getUser(std::string username);

private:
  std::map<std::string, std::set<Product*>> prodInfo;
  std::set<Product*> products;
  std::set<User*> users;
};

