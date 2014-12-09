#ifndef BENCHMARK_H_
#define BENCHMARK_H_

#include <sys/time.h>

#include "briandais.h"
#include "gestion_fichier.h"
#include "trieHybride_complexe.h"

#define MS_TO_S(ms) ((double)ms/1000000)

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

/*
 * Benchmarking function for destruction of an entire Briandais trie.
 */
void bench_destroy_briandais();

#endif
