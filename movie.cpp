#include <sstream>
#include <iomanip>
#include "product.h"
#include "util.h"
#include "movie.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) :
  Product(category, name, price, qty) 
{
  this->genre = genre;
  this->rating = rating;
}

std::set<std::string> Movie::keywords() const 
{
  std::set<std::string> list;
  std::set<std::string> temp;

  // saving rating
  temp = parseStringToWords(convToLower(rating));
  list.insert(temp.begin(), temp.end());

  // saving movie name
  temp = parseStringToWords(convToLower(name_));
  list.insert(temp.begin(), temp.end());

  return list;
}

std::string Movie::displayString() const 
{
  std::stringstream ss;
  ss << name_ << "\nGenre" << genre << " Rating: " << rating + "\n" << price_ << " " << qty_ << " left.";
  return ss.str();
}

void Movie::dump(std::ostream& os) const 
{
  Product::dump(os);
  os << genre << "\n" << rating << endl;
}

std::string Movie::getGenre()
{
  return genre;
}
std::string Movie::getRating()
{
  return rating;
}