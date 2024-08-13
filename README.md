# Extraclase1Datos2

# Binary File Generator and Sorter

Este repositorio contiene dos herramientas en C++ para generar y ordenar archivos binarios grandes que contienen números enteros aleatorios.

## Contenido del Repositorio

1. **`generator.cpp`**: Programa para generar archivos binarios con números enteros aleatorios.
2. **`sorter.cpp`**: Programa para ordenar archivos binarios utilizando diferentes algoritmos de ordenamiento.
3. **`PagedArray.h`** y **`PagedArray.cpp`**: Implementación de la clase `PagedArray` para manejar la paginación de archivos binarios.
4. **`sorting_algorithms.cpp`**: Implementación de los algoritmos de ordenamiento (Quick Sort, Insertion Sort, Bubble Sort).
5. **`README.md`**: Este archivo.

## Cómo Compilar

### Generador de Archivos Binarios

Para compilar el generador de archivos binarios:

```sh
g++ -o generator generator.cpp
```

### Programa de Ordenamiento

Para compilar el programa de ordenamiento:

1. Compila los archivos objeto:

    ```sh
    g++ -c PagedArray.cpp
    g++ -c sorting_algorithms.cpp
    ```

2. Compila el programa `sorter`:

    ```sh
    g++ -o sorter sorter.cpp PagedArray.o sorting_algorithms.o
    ```

## Cómo Ejecutar

### Generar un Archivo Binario

Para generar un archivo binario con números enteros aleatorios:

- Para un archivo de 512 MB:

    ```sh
    ./generator -size SMALL -output output_512MB.bin
    ```

- Para un archivo de 1 GB:

    ```sh
    ./generator -size MEDIUM -output output_1GB.bin
    ```

- Para un archivo de 2 GB:

    ```sh
    ./generator -size LARGE -output output_2GB.bin
    ```

### Ordenar un Archivo Binario

Para ordenar un archivo binario, utiliza el programa `sorter` con el algoritmo deseado:

- **Quick Sort (QS)**:

    ```sh
    ./sorter -input output_1GB.bin -output sorted_output.bin -alg QS
    ```

- **Insertion Sort (IS)**:

    ```sh
    ./sorter -input output_1GB.bin -output sorted_output.bin -alg IS
    ```

- **Bubble Sort (BS)**:

    ```sh
    ./sorter -input output_1GB.bin -output sorted_output.bin -alg BS
    ```

## Detalles Adicionales

- **`PagedArray`**: La clase `PagedArray` maneja la paginación de archivos binarios, cargando y descargando páginas de datos en memoria para permitir el ordenamiento de archivos grandes.

- **Algoritmos de Ordenamiento**: Se implementan tres algoritmos de ordenamiento (Quick Sort, Insertion Sort y Bubble Sort) que funcionan sobre el `PagedArray`.

## Ejemplos de Uso

1. **Generar un archivo de 1 GB**:
    ```sh
    ./generator -size MEDIUM -output output_1GB.bin
    ```

2. **Ordenar el archivo de 1 GB usando Quick Sort**:
    ```sh
    ./sorter -input output_1GB.bin -output sorted_output.bin -alg QS
    ```

3. **Verificar el archivo ordenado**:
    El archivo `sorted_output.bin` contendrá los números enteros ordenados en orden ascendente, separados por comas.

## Notas

- Asegúrate de que el archivo ejecutable tenga permisos de ejecución en sistemas Unix/Linux.
- En Windows, usa `generator.exe` y `sorter.exe` en lugar de `generator` y `sorter`.

## Contribuciones

Las contribuciones al proyecto son bienvenidas. Por favor, abre un issue o envía un pull request para mejorar el proyecto.

## Licencia

Este proyecto está licenciado bajo la Licencia MIT. Consulta el archivo `LICENSE` para obtener más detalles.
```

Asegúrate de guardar este contenido en un archivo llamado `README.md` en la raíz de tu repositorio. Esto proporcionará a los usuarios del repositorio toda la información necesaria para compilar y usar las herramientas proporcionadas.