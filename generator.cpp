#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

void generateFile(const string &sizeArg, const string &outputFilePath) {
    // Determinar el tamaño del archivo en bytes
    long long sizeInBytes;
    if (sizeArg == "SMALL") sizeInBytes = 512LL * 1024 * 1024; // 512 MB
    else if (sizeArg == "MEDIUM") sizeInBytes = 1LL * 1024 * 1024 * 1024; // 1 GB
    else if (sizeArg == "LARGE") sizeInBytes = 2LL * 1024 * 1024 * 1024; // 2 GB
    else {
        cerr << "Invalid size argument. Use SMALL, MEDIUM, or LARGE." << endl;
        exit(1);
    }

    // Crear y abrir el archivo binario para escritura
    ofstream outFile(outputFilePath, ios::binary);
    if (!outFile) {
        cerr << "Error opening file for writing: " << outputFilePath << endl;
        exit(1);
    }

    // Generar números enteros aleatorios y escribirlos en el archivo
    srand(static_cast<unsigned int>(time(0))); // Inicializar la semilla para números aleatorios
    for (long long i = 0; i < sizeInBytes / sizeof(int); ++i) {
        int randomNumber = rand();
        outFile.write(reinterpret_cast<char*>(&randomNumber), sizeof(randomNumber));
    }

    // Cerrar el archivo
    outFile.close();
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        cerr << "Usage: generator --size <SIZE> --output <OUTPUT FILE PATH>" << endl;
        return 1;
    }

    string sizeArg;
    string outputFilePath;

    for (int i = 1; i < argc; ++i) {
        if (string(argv[i]) == "--size") {
            if (i + 1 < argc) sizeArg = argv[++i];
            else {
                cerr << "Missing value for --size" << endl;
                return 1;
            }
        } else if (string(argv[i]) == "--output") {
            if (i + 1 < argc) outputFilePath = argv[++i];
            else {
                cerr << "Missing value for --output" << endl;
                return 1;
            }
        } else {
            cerr << "Unknown argument: " << argv[i] << endl;
            return 1;
        }
    }

    generateFile(sizeArg, outputFilePath);
    return 0;
}
