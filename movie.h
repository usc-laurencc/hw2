#include "product.h"

class Movie : public Product {
public:
  Movie(const std::string name, double price, int qty, const std::string genre, const std::string rating);
  ~Movie();

  std::set<std::string> keywords() const;
private:
  std::string genre;
  std::string rating;
};