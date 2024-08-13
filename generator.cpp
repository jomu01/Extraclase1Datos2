#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

void generateFile(const std::string& filePath, size_t numIntegers) {
    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error al abrir el archivo para escritura: " << filePath << std::endl;
        return;
    }

    // Inicializa el generador de números aleatorios
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (size_t i = 0; i < numIntegers; ++i) {
        int randomInt = std::rand();
        outFile.write(reinterpret_cast<const char*>(&randomInt), sizeof(randomInt));
    }

    outFile.close();
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Uso: generator –size <SIZE> -output <OUTPUT FILE PATH>" << std::endl;
        return 1;
    }

    std::string sizeStr = argv[2];
    std::string outputPath = argv[4];

    size_t numIntegers = 0;
    if (sizeStr == "SMALL") {
        numIntegers = 512ULL * 1024 * 1024 / sizeof(int); // 512 MB
    } else if (sizeStr == "MEDIUM") {
        numIntegers = 1024ULL * 1024 * 1024 / sizeof(int); // 1 GB
    } else if (sizeStr == "LARGE") {
        numIntegers = 2ULL * 1024 * 1024 * 1024 / sizeof(int); // 2 GB
    } else {
        std::cerr << "Tamaño no reconocido. Usa SMALL, MEDIUM o LARGE." << std::endl;
        return 1;
    }

    generateFile(outputPath, numIntegers);

    return 0;
}
