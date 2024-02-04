#include <sstream>
#include <iomanip>
#include <sstream>
#include "product.h"
#include "util.h"
#include "book.h"

using namespace std;

Book::Book(const std::string name, double price, int qty, const std::string ISBN, const std::string author) :
  Product("book", name, price, qty) 
{
  this->ISBN = ISBN;
  this->author = author;
}

std::set<std::string> Book::keywords() const 
{
  std::set<std::string> list;
  std::set<std::string> temp;

  // saving author
  temp = parseStringToWords(convToLower(author));
  list.insert(temp.begin(), temp.end());

  // saving title
  temp = parseStringToWords(convToLower(name_));
  list.insert(temp.begin(), temp.end());

  list.insert(ISBN); // saving ISBN
  return list;
}

std::string Book::displayString() const 
{
  std::stringstream ss;
  ss << name_ << "\nAuthor" << author << " ISBN: " << ISBN + "\n" << price_ << " " << qty_ << " left.";
  return ss.str();
}

void Book::dump(std::ostream& os) const 
{
  Product::dump(os);
  os << ISBN << "\n" << author << endl;
}

std::string Book::getISBN()
{
  return ISBN;
}
std::string Book::getAuthor()
{
  return author;
}