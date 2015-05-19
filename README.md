# Overview

This counting bloom filter implementation is based on the [dablooms of github](https://github.com/bitly/dablooms).

This counting bloom filter can add, delete, and check elements.



# Tables of contents

*  source code files are `murmur.h`, `murmur.c`, `dablooms.h`, `dablooms.c`, `test_dablooms.c`, and `Makefile`;

*  `murmur.h`, `murmur.c`, `dablooms.h`, `dablooms.c`, and `test_dablooms.c` are in a subdirectory named `src`, `Makefile` is in the same directory with `src`;

*  `murmur.h` and `murmur.c` are lib for hashing;

*  `dablooms.h` and `dablooms.c` are for counting bloom filter; 

*  `test_dablooms.c` is for testing, you may program your own test file;

*  `Makefile` is for make, install, clean, or test this filter.



# Steps to run this counting bloom filter

1.  put the source code file in a subdirectory named `src`;

2.  the Makefile should be in the same dir with `src`, not inside `dir`;

3.  get root permission;

4.  to test,
```shell
make test
```
to make,
```shell
make
```
to clean.
```shell
make clean
```


# APIs for this counting bloom filter

* about the capacity and error rate of this counting bloom filter
> the capacity (or the maximum number of elements) is set in `dablooms.h` with macro `CAPACITY`, the error rate is set in `dablooms.h` with macro `ERROR_RATE`.

*  create the counting bloom filter
> the counting bloom filter is created automatically according to arguments `CAPACITY` and `ERROR_RATE`.


*  the function for adding elements
> `int counting_bloom_add(counting_bloom_t *bloom, const char *s, size_t len)`.  
>>  `bloom` is a pointer to the filter which elements are added to;  
>>  `s` is a pointer to the content string of the added element;   
>>  `len` is the length of s.

*  the function for remove elements
> `int counting_bloom_remove(counting_bloom_t *bloom, const char *s, size_t len)`   
>>  `bloom` is a pointer to the filter which elements are to be removed;   
>>  `s` is a pointer to the content string of the removed element;   
>>  `len` is the length of s.

*  the function for checking elements
> `int counting_bloom_check(counting_bloom_t *bloom, const char *s, size_t len)`   
> >  `bloom` is a pointer to the filter which elements are to be removed;   
> >  `s` is a pointer to the content string of the removed element;   
> >  `len` is the length of s.

*  the function for showing statistics
> `int print_results(bloom_stats *stats)`   
> >  `stats` is the pointer to the filter.


# Copyright

xpsair@qq.com
