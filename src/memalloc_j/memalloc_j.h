union header;
typedef union header header_t;

header_t *get_free_block(size_t size);
void free_j(void *block);
void *malloc_j(size_t size);
void *calloc_j(size_t num, size_t nsize);
void *realloc_j(void *block, size_t size);
