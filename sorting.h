#ifndef SORTING_H
#define SORTING_H


extern std::queue<Product> queueSort;

void Sort(int categoryIndex, bool sortByPrice, int filterID);
void SortOutput();
void SortPrice(int categoryIndex, bool sortByPrice);
void SortOutputPrice();


#endif 