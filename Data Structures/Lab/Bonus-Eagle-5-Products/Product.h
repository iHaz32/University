#ifndef PRODUCT_H
#define PRODUCT_H

/**
 * Represents a product
 */
class Product {
private:
    // the name
    char *name;
    // the price
    float price;
public:
    //Default constructor
    Product();

    // Constructor with two parameters: the name and the price of the product
    Product(const char *name, float price);

    // Getter for the name
    char *getName();

    // Setter for the name
    void setName(const char *name);

    // Getter for the price
    float getPrice();

    // Setter for the price
    void setPrice(float price);

    // Destructor
    ~Product();

};

#endif