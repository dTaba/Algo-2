# Algoritmos y Estructuras de Datos II

Este repositorio contiene trabajos prácticos y proyectos relacionados con la materia "Algoritmos y Estructuras de Datos II" de la carrera de Ciencias de la Computación.

## Objetivos

- Presentar los conceptos básicos para la solución algorítmica de problemas: especificación, diseño, implementación, complejidad de cómputo.
- Introducir tipos abstractos de datos recursivos.
- Explorar soluciones reconocidas para problemas fundamentales de búsqueda y ordenamiento.
- Presentar técnicas de análisis y diseño de algoritmos.
- Resolver proyectos informáticos aplicando las herramientas aprendidas, incluyendo el manejo de archivos secuenciales.

## Programa

### 1. Tipos Abstractos de Datos y Problemas

- Tipos abstractos de datos: secuencia, pila, cola, arreglo, árbol binario, conjunto, diccionario.
- Especificación: descripción de problemas utilizando tipos abstractos; modularización.
- Recursión: axiomatización de funciones mediante la recursión; inducción estructural.

### 2. Diseño, Estructuras de Datos y Algoritmos

- Diseño: conceptos, módulos, relación implementa_a, invariante de representación y función de abstracción, diagramas conmutativos.
- Complejidad de algoritmos: Análisis asintótico del peor caso y caso promedio. Notación O(). Cotas superiores e inferiores.
- Estructuras de Datos: representaciones para secuencias, pilas, colas, diccionarios y conjuntos. Árboles binarios, árboles AVL, hashing, tries, colas de prioridad (heaps). Búsqueda y ordenamiento en memoria secundaria.
- Algoritmos de Ordenamiento: Inserción, selección, quicksort, mergesort, heapsort. Algoritmos específicos para diferentes tipos de inputs.

### 3. Técnicas Algorítmicas

- Divide & Conquer.
- Generalización de funciones.
- Eliminación de la Recursión: plegado/desplegado; inmersión de parámetros.
- Aplicación de algoritmos y estructuras de datos a otros problemas.

## Uso del Repositorio

Cada trabajo cuenta con su conjunto de tests que se generan de la siguiente manera:

```sh
cmake .
```

Luego de esto se puede generar el test que se quiera ejecutar (revisar targets en CMakeLists.txt)
```sh
make correrTests
```

```sh
./correrTests 
```

```sh
make correrValgrind
```

```sh
./correrValgrind
```
