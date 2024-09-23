#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Product.h"

/**
 * Auxiliary class that provides functions to save and load products
 */
class Controller {
public:
    /**
     * Saves an array of products in a text file
     * @param products The array of products to save
     * @param filename The name of the file
     * @param num The number of products to save (size of products[])
     */
    void save(Product products[], const char *filename, int num);

    /**
     * Loads products from a file in an array
     * @param filename The name of the file to load products from
     * @param products The array where the products will be loaded in
     * @param num size of the array
     */
    void load(const char *filename, Product products[], int num);
};


#endif 