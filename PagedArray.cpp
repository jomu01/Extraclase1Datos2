#include "PagedArray.h"
#include <stdexcept>
#include <cstring>

PagedArray::PagedArray(const std::string& filename, size_t pageSize)
    : filename(filename), pageSize(pageSize), pageCount(0),
      totalPageFaults(0), totalPageHits(0) {
    // Assuming pageSize is the number of integers per page
    std::ifstream infile(filename, std::ios::binary | std::ios::ate);
    if (!infile.is_open()) {
        throw std::runtime_error("Unable to open file.");
    }
    size_t fileSize = infile.tellg();
    infile.close();
    pageCount = (fileSize + pageSize * sizeof(int) - 1) / (pageSize * sizeof(int));

    pages.resize(4, nullptr);
    isPageLoaded.resize(pageCount, false);
}

PagedArray::~PagedArray() {
    for (int* page : pages) {
        delete[] page;
    }
}

int& PagedArray::operator[](size_t index) {
    size_t pageIndex = calculatePageIndex(index);
    if (!isPageLoaded[pageIndex]) {
        loadPage(pageIndex);
    } else {
        ++totalPageHits;
    }
    return pages[pageIndex][calculateOffset(index)];
}

const int& PagedArray::operator[](size_t index) const {
    size_t pageIndex = calculatePageIndex(index);
    if (!isPageLoaded[pageIndex]) {
        throw std::runtime_error("Page not loaded.");
    }
    return pages[pageIndex][calculateOffset(index)];
}

void PagedArray::loadPage(size_t pageIndex) {
    size_t pageOffset = pageIndex * pageSize * sizeof(int);
    std::ifstream infile(filename, std::ios::binary);
    infile.seekg(pageOffset);

    size_t pageSizeBytes = pageSize * sizeof(int);
    char* buffer = new char[pageSizeBytes];
    infile.read(buffer, pageSizeBytes);

    int* page = new int[pageSize];
    std::memcpy(page, buffer, pageSizeBytes);
    delete[] buffer;

    if (pages.size() >= 4) {
        unloadPage(0); // Simple replacement policy: unload the first page
    }

    pages.push_back(page);
    isPageLoaded[pageIndex] = true;
    ++totalPageFaults;
}

void PagedArray::unloadPage(size_t pageIndex) {
    if (isPageLoaded[pageIndex]) {
        delete[] pages[pageIndex];
        pages[pageIndex] = nullptr;
        isPageLoaded[pageIndex] = false;
    }
}

void PagedArray::printStats() const {
    std::cout << "Page faults: " << totalPageFaults << std::endl;
    std::cout << "Page hits: " << totalPageHits << std::endl;
}

size_t PagedArray::calculatePageIndex(size_t index) const {
    return index / pageSize;
}

size_t PagedArray::calculateOffset(size_t index) const {
    return index % pageSize;
}
