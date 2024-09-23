#ifndef PRODUCT_H
#define PRODUCT_H

class Product {
private:
  // Every product has an id
  unsigned int id;

  // The name of the product
  char *name;

  // The price of the product
  float price;

public:
  /**
   * @brief Constructor
   *
   * @param id The id of the product
   * @param name The name of the product
   * @param price The price of the product
   */
  Product(unsigned int id, char *name, float price);

  // Desctructor
  ~Product();

  /**
   * @brief Getter for the name
   *
   * @return char* The name
   */
  char *getName();

  /**
   * @brief Getter for the id
   *
   * @return unsigned int The id of the product
   */
  unsigned int getId();

  /**
   * @brief Getter for the price
   *
   * @return float The price of the product
   */
  float getPrice();
};

#endif