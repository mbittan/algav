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

/* 
 * Benchmarking function for listing words in Shakespeare's Briandais trie.
 */  
void bench_list_briandais();

/* 
 * Benchmarking function for computing height of Shakespeare's Briandais trie.
 */  
void bench_height_briandais();

/* 
 * Benchmarking function for computing average depth of Shakespeare's Briandais
 * trie.
 */  
void bench_average_depth_briandais();

/* 
 * Benchmarking function for finding if a word is a prefix in Shakespeare's
 * Briandais trie.
 */  
void bench_prefix_briandais();

/* 
 * Benchmarking function for merging 2 Briandais tries (Hamlet and All's Well).
 */  
void bench_merge_briandais();

/* 
 * Benchmarking function for converting Shakespeare's Briandais trie into a
 * hybrid trie.
 */  
void bench_convert_to_hybrid();

/* 
 * Benchmarking function for exporting Shakespeare's Briandais trie into an
 * SVG image file viewable with a web browser or Inkscape.
 */  
void bench_export_to_svg();

/* 
 * Benchmarking function for inserting an unknown word in Shakespeare's
 * Briandais trie. The word will be 'youtizzzzz' to have a worst-case
 * scenario like insertion.
 */  
void bench_worst_insertion_briandais();

/* 
 * Benchmarking function for the used space in memory of Shakespeare's
 * Briandais trie.
 */  
void bench_memory_usage_briandais();

#endif
