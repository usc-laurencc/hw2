#include <string>
#include <set>
#include "product.h"
#include "util.h"

class Book : public Product {
public:
  Book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string author);
  
  std::set<std::string> keywords() const;
  std::string displayString() const;
  void dump(std::ostream& os) const;

  // Accessors
  std::string getISBN();
  std::string getAuthor();
  
private:
  std::string ISBN;
  std::string author;
};
