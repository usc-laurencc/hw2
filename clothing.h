#include "product.h"

class Clothing : public Product {
public:
  Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand);
  ~Clothing();

  std::set<std::string> keywords() const;

private:
  std::string size;
  std::string brand;
};