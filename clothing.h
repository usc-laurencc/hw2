#include <string>
#include <set>
#include "product.h"

class Clothing : public Product {
public:
  Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand);
  
  std::set<std::string> keywords() const;
  std::string displayString() const;
  void dump(std::ostream& os) const;

  // Accessors
  std::string getSize();
  std::string getBrand();
  
private:
  std::string size;
  std::string brand;
};
