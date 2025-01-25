// PruebaOMP.cpp : Programa para sumar dos arreglos en paralelo usando OpenMP
//

#include <iostream>
#include <omp.h>
#include <chrono>

#define N 1000
#define chunk 100
#define mostrar 10

// Función para imprimir los primeros valores de un arreglo
void imprimirArreglo(float* a, float* b, float* c);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";
    float a[N], b[N], c[N];
    int i;

    // Inicializacion la semilla del generador de números aleatorios
    srand(static_cast<unsigned int>(time(0)));

    // Inicializacion los arreglos a y b con valores aleatorios
    for (i = 0; i < N; i++) {
		a[i] = static_cast<float>(rand());
		b[i] = static_cast<float>(rand());
	}
    int pedazos = chunk;

	// Iniciar el temporizador
    auto start = std::chrono::high_resolution_clock::now();

    // Suma de los arreglos en paralelo usando OpenMP
    #pragma omp parallel for \
    shared(a,b,c, pedazos) private(i) \
    schedule(static, pedazos)
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Medicion del tiempo de ejecución
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    // Imprimir los primeros valores de los arreglos a, b y c

    imprimirArreglo(a, b, c);

	// Imprimir el tiempo de ejecución
	std::cout << "Tiempo de ejecucion: " << duration.count() << " segundos" << std::endl;
	return 0;
}

// Implementación de la función para imprimir los primeros valores de tres arreglos
void imprimirArreglo(float* a, float* b, float* c) {

    std::cout << "Arreglo A\t\tArreglo B\t\tArreglo C" << std::endl;
    std::cout << "---------\t\t---------\t\t---------" << std::endl;
    for (int x = 0; x < mostrar; x++) {
        std::cout << "[" << x << "] " << a[x] << "\t\t[" << x << "] " << b[x] << "\t\t[" << x << "] " << c[x] << std::endl;
    }
}
