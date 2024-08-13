#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "PagedArray.h"
#include "sorting_algorithms.h"

int main(int argc, char* argv[]) {
    if (argc != 7) {
        std::cerr << "Uso: sorter –input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO>" << std::endl;
        return 1;
    }

    std::string inputPath = argv[2];
    std::string outputPath = argv[4];
    std::string algorithm = argv[6];

    std::ifstream inputFile(inputPath, std::ios::binary | std::ios::ate);
    if (!inputFile) {
        std::cerr << "Error al abrir el archivo de entrada: " << inputPath << std::endl;
        return 1;
    }

    size_t fileSize = inputFile.tellg();
    inputFile.close();

    size_t numIntegers = fileSize / sizeof(int);
    PagedArray arr(inputPath, numIntegers);

    clock_t start = clock();

    if (algorithm == "QS") {
        quickSort(arr, 0, numIntegers - 1);
    } else if (algorithm == "IS") {
        insertionSort(arr, 0, numIntegers - 1);
    } else if (algorithm == "BS") {
        bubbleSort(arr, 0, numIntegers - 1);
    } else {
        std::cerr << "Algoritmo no reconocido. Usa QS, IS o BS." << std::endl;
        return 1;
    }

    clock_t end = clock();

    std::ofstream outputFile(outputPath);
    if (!outputFile) {
        std::cerr << "Error al abrir el archivo de salida: " << outputPath << std::endl;
        return 1;
    }

    for (size_t i = 0; i < numIntegers; ++i) {
        outputFile << arr[i];
        if (i < numIntegers - 1) {
            outputFile << ",";
        }
    }

    outputFile.close();

    double duration = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Tiempo de ejecución: " << duration << " segundos" << std::endl;
    std::cout << "Algoritmo utilizado: " << algorithm << std::endl;
    std::cout << "Page faults: " << arr.getPageFaults() << std::endl;
    std::cout << "Page hits: " << arr.getPageHits() << std::endl;

    return 0;
}
