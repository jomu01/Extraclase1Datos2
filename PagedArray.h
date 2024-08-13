#ifndef PAGEDARRAY_H
#define PAGEDARRAY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class PagedArray {
public:
    PagedArray(const std::string& filename, size_t pageSize = 1024 * 1024 * 4);
    ~PagedArray();

    int& operator[](size_t index);
    const int& operator[](size_t index) const;

    void loadPage(size_t pageIndex);
    void unloadPage(size_t pageIndex);

    void printStats() const;

private:
    std::string filename;
    size_t pageSize;
    size_t pageCount;
    std::vector<int*> pages;
    std::vector<bool> isPageLoaded;

    size_t calculatePageIndex(size_t index) const;
    size_t calculateOffset(size_t index) const;

    size_t totalPageFaults;
    size_t totalPageHits;
};

#endif // PAGEDARRAY_H
