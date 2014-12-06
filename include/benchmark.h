#ifndef BENCHMARK_H_
#define BENCHMARK_H_

#include <sys/time.h>

#include "briandais.h"
#include "gestion_fichier.h"
#include "trieHybride_complexe.h"

/*
 * Standard benchmarking method.
 * Takes the function to benchmark in argument f.
 * Returns the number of microseconds elapsed during f's execution.
 */
long bench(void (*f)());

/* 
 * Benchmarking function for insertion in Briandais tries.
 */  
void bench_insert_briandais();

#endif
