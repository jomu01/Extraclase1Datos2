#include "PagedArray.h"
#include <stdexcept>
#include <iostream>

const size_t PAGE_SIZE = 4096; // Tamaño de la página en número de enteros (ajustar si es necesario)

PagedArray::PagedArray(const std::string& inputFilePath, size_t numIntegers)
    : inputFile(inputFilePath, std::ios::binary), numIntegers(numIntegers) {
    if (!inputFile) {
        throw std::runtime_error("Error al abrir el archivo de entrada.");
    }
    tempFile.open("temp.bin", std::ios::binary | std::ios::trunc);
    if (!tempFile) {
        throw std::runtime_error("Error al abrir el archivo temporal.");
    }
}

PagedArray::~PagedArray() {
    for (size_t i = 0; i < 4; ++i) {
        if (!pages[i].empty()) {
            tempFile.seekp(i * PAGE_SIZE * sizeof(int));
            tempFile.write(reinterpret_cast<const char*>(pages[i].data()), PAGE_SIZE * sizeof(int));
        }
    }
}

size_t PagedArray::getPageIndex(size_t index) const {
    return index / PAGE_SIZE;
}

size_t PagedArray::getPageOffset(size_t index) const {
    return index % PAGE_SIZE;
}

void PagedArray::loadPage(size_t pageIndex) {
    size_t pagePos = pageIndex % 4;
    size_t offset = pageIndex * PAGE_SIZE * sizeof(int);
    inputFile.seekg(offset);
    pages[pagePos].resize(PAGE_SIZE);
    inputFile.read(reinterpret_cast<char*>(pages[pagePos].data()), PAGE_SIZE * sizeof(int));
    pageMap[pageIndex] = pagePos;
    pageFaults++;
}

void PagedArray::unloadPage(size_t pageIndex) {
    if (pageMap.count(pageIndex)) {
        size_t pagePos = pageMap[pageIndex];
        tempFile.seekp(pagePos * PAGE_SIZE * sizeof(int));
        tempFile.write(reinterpret_cast<const char*>(pages[pagePos].data()), PAGE_SIZE * sizeof(int));
        pageMap.erase(pageIndex);
    }
}

int& PagedArray::operator[](size_t index) {
    size_t pageIndex = getPageIndex(index);
    size_t pageOffset = getPageOffset(index);

    if (pageMap.count(pageIndex)) {
        pageHits++;
        return pages[pageMap[pageIndex]][pageOffset];
    } else {
        if (pageMap.size() >= 4) {
            unloadPage(pageIndex);
        }
        loadPage(pageIndex);
        return pages[pageMap[pageIndex]][pageOffset];
    }
}

size_t PagedArray::getPageFaults() const {
    return pageFaults;
}

size_t PagedArray::getPageHits() const {
    return pageHits;
}
