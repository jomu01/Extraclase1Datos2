#ifndef PAGED_ARRAY_H
#define PAGED_ARRAY_H

#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

class PagedArray {
public:
    PagedArray(const std::string& inputFilePath, size_t numIntegers);
    ~PagedArray();

    int& operator[](size_t index);

    size_t getPageFaults() const;
    size_t getPageHits() const;

private:
    std::ifstream inputFile;
    std::ofstream tempFile;
    size_t numIntegers;
    std::vector<int> pages[4];
    std::unordered_map<size_t, size_t> pageMap;
    size_t pageFaults = 0;
    size_t pageHits = 0;

    size_t getPageIndex(size_t index) const;
    size_t getPageOffset(size_t index) const;
    void loadPage(size_t pageIndex);
    void unloadPage(size_t pageIndex);
};

#endif // PAGED_ARRAY_H
