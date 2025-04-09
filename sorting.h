#ifndef SORTING_H
#define SORTING_H

#include "structure.h"
#include <queue>

// Только объявление (без extern)
extern std::queue<Product> queueSort;

void Sort(int categoryIndex, bool sortByPrice, int filterID);
void SortOutput();
void SortPrice(int categoryIndex, bool sortByPrice);
void SortOutputPrice();


#endif // SORTING_H