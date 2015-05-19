/* Copyright @2012 by Justin Hines at Bitly under a very liberal license. See LICENSE in the source distribution. */

#ifndef __BLOOM_H__
#define __BLOOM_H__
#include <stdint.h>
#include <stdlib.h>

#define CAPACITY 100000
#define ERROR_RATE .05


const char *dablooms_version(void);

enum {
    TEST_PASS,
    TEST_WARN,
    TEST_FAIL,
};

typedef struct {
    int true_positives;
    int true_negatives;
    int false_positives;
    int false_negatives;
} bloom_stats;

void bloom_score(int positive, int should_positive, bloom_stats *stats, const char *key);
int print_results(bloom_stats *stats);


typedef struct {
    size_t bytes;
    //int    fd; //by xp: what is it?
    char  *array;
} bitmap_t;


bitmap_t *bitmap_resize(bitmap_t *bitmap, size_t old_size, size_t new_size);
bitmap_t *new_bitmap(size_t bytes);

int bitmap_increment(bitmap_t *bitmap, unsigned int index, long offset);
int bitmap_decrement(bitmap_t *bitmap, unsigned int index, long offset);
int bitmap_check(bitmap_t *bitmap, unsigned int index, long offset);
int bitmap_flush(bitmap_t *bitmap);

void free_bitmap(bitmap_t *bitmap);

typedef struct {
    uint64_t id;
    uint32_t count; //by xp: number of elements in this bloom filter
    uint32_t _pad;
} counting_bloom_header_t;


typedef struct {
    counting_bloom_header_t *header;
    unsigned int capacity;
    long offset; //by xp: ???
    unsigned int counts_per_func; //by xp: the sum of elements mapped by hash function
    uint32_t *hashes; //by xp: the point to hash function point lists
    size_t nfuncs; //by xp: number of hash functions
    size_t size; //by xp: elements manged by this bloom filter
    size_t num_bytes; //by xp: space occupied by this counting bloom filter
    double error_rate;
    bitmap_t *bitmap;
    bloom_stats counting_stats; //by  xp: get statistic information
} counting_bloom_t;

int free_counting_bloom(counting_bloom_t *bloom);
counting_bloom_t *new_counting_bloom(unsigned int capacity, double error_rate);
counting_bloom_t *new_counting_bloom_from_file(unsigned int capacity, double error_rate, const char *filename);
int counting_bloom_add(counting_bloom_t *bloom, const char *s, size_t len);
int counting_bloom_remove(counting_bloom_t *bloom, const char *s, size_t len);
int counting_bloom_check(counting_bloom_t *bloom, const char *s, size_t len);

typedef struct {
    uint64_t max_id;
    uint64_t mem_seqnum;
    uint64_t disk_seqnum;
} scaling_bloom_header_t;

typedef struct {
    scaling_bloom_header_t *header;
    unsigned int capacity;
    unsigned int num_blooms;
    size_t num_bytes;
    double error_rate;
    int fd;
    counting_bloom_t **blooms;
    bitmap_t *bitmap;
} scaling_bloom_t;

scaling_bloom_t *new_scaling_bloom(unsigned int capacity, double error_rate, const char *filename);
scaling_bloom_t *new_scaling_bloom_from_file(unsigned int capacity, double error_rate, const char *filename);
int free_scaling_bloom(scaling_bloom_t *bloom);
int scaling_bloom_add(scaling_bloom_t *bloom, const char *s, size_t len, uint64_t id);
int scaling_bloom_remove(scaling_bloom_t *bloom, const char *s, size_t len, uint64_t id);
int scaling_bloom_check(scaling_bloom_t *bloom, const char *s, size_t len);
int scaling_bloom_flush(scaling_bloom_t *bloom);
uint64_t scaling_bloom_mem_seqnum(scaling_bloom_t *bloom);
uint64_t scaling_bloom_disk_seqnum(scaling_bloom_t *bloom);
#endif
