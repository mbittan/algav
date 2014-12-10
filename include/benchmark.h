#ifndef BENCHMARK_H_
#define BENCHMARK_H_

#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

#include "briandais.h"
#include "gestion_fichier.h"
#include "trieHybride_complexe.h"

#define _XOPEN_SOURCE 777

#define MS_TO_S(ms) ((double)ms/1000000)

#define NB_THREADS 6

/*
 * Standard benchmarking method.
 * Takes the function to benchmark in argument f.
 * Returns the number of microseconds elapsed during f's execution.
 */
long bench(void (*f)());

/* 
 * Benchmarking function for insertion in Briandais tries.
 * The final tree is built by successive insertions.
 */  
void bench_insert_briandais();

/* 
 * Benchmarking function for insertion in Briandais tries.
 * This function builds each tree separately in multiple threads
 * and merges them.
 */ 
void bench_insert_briandais_mthread();

/* 
 * Benchmarking function for deletion of Hamlet in Briandais trie.
 */  
void bench_delete_briandais();

/*
 * Benchmarking function for destruction of an entire Briandais trie.
 */
void bench_destroy_briandais();

/* 
 * Benchmarking function for searching of Hamlet and All's Well words
 * in Shakespeare's Briandais trie.
 */  
void bench_search_briandais();

/* 
 * Benchmarking function for counting how many words there are
 * in Shakespeare's Briandais trie.
 */  
void bench_count_briandais();

/* 
 * Benchmarking function for counting how many null pointers there are
 * in Shakespeare's Briandais trie.
 */  
void bench_count_null_briandais();

#endif
