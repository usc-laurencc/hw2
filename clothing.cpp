#include <sstream>
#include <iomanip>
#include "product.h"
#include "util.h"
#include "clothing.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) :
  Product(category, name, price, qty) 
{
  this->size = size;
  this->brand = brand;
}

std::set<std::string> Clothing::keywords() const 
{
  std::set<std::string> list;
  std::set<std::string> temp;

  // saving brand
  temp = parseStringToWords(convToLower(brand));
  list.insert(temp.begin(), temp.end());

  // saving product name
  temp = parseStringToWords(convToLower(name_));
  list.insert(temp.begin(), temp.end());

  return list;
}

std::string Clothing::displayString() const 
{
  std::stringstream ss;
  ss << name_ << "\nSize" << size << " Brand: " << brand + "\n" << price_ << " " << qty_ << " left.";
  return ss.str();
}

void Clothing::dump(std::ostream& os) const 
{
  Product::dump(os);
  os << size << "\n" << brand << endl;
}

std::string Clothing::getSize()
{
  return size;
}
std::string Clothing::getBrand()
{
  return brand;
}