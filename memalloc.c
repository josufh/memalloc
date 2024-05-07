#include <unistd.h>
#include <string.h>
#include <pthread.h>

typedef char ALIGN[16];

union header {
  struct {
    size_t size;
    unsigned is_free;
    union header *next;
  } s;
  ALIGN stub;
};
typedef union header header_t;

header_t *head = NULL, *tail = NULL;
pthread_mutex_t malloc_lock;

header_t *get_free_block(size_t size) {
  header_t *curr = head;
  while(curr) {
    if (curr->s.is_free && curr->s.size >= size) return curr;
    curr = curr->s.next;
  }
  return NULL;
}

void free(void *block) {
  if (!block) return;

  header_t *header, *temp;
  void *pb;

  pthread_mutex_lock(&malloc_lock);

  header = (header_t*)block - 1;
  pb = sbrk(0);

  if ((char*)block + header->s.size == pb) {
    if (head == tail) {
      head = tail = NULL;
    } else {
      temp = head;
      while (temp) {
        if(temp->s.next == tail) {
          temp->s.next = NULL;
          tail = temp;
        }
        temp = temp->s.next;
      }
    }
    sbrk(0 - header->s.size - sizeof(header_t));

    pthread_mutex_unlock(&malloc_lock);
    return;
  }
  header->s.is_free = 1;
  pthread_mutex_unlock(&malloc_lock);
}

void *malloc(size_t size) {
  if (!size) return NULL;
    
  size_t total_size;
  void *block;
  header_t *header;
  
  pthread_mutex_lock(&malloc_lock);
  
  header = get_free_block(size);
  if (header) {
    header->s.is_free = 0;
    pthread_mutex_unlock(&malloc_lock);
    return (void*)(header + 1);
  }
  total_size = sizeof(header_t) + size;
  block = sbrk(total_size);
  if (block == (void*) -1) {
    pthread_mutex_unlock(&malloc_lock);
    return NULL;
  }
  header = block;
  header->s.size = size;
  header->s.is_free = 0;
  header->s.next = NULL;
  
  if (!head) head = header;
  if (tail) tail->s.next = header;
  tail = header;
  
  pthread_mutex_unlock(&malloc_lock);
  return (void*)(header + 1);
}

void *calloc(size_t num, size_t nsize) {
  if (!num || !nsize) return NULL;
  
  size_t size;
  void *block;
  
  size = num * nsize;
  if (nsize != size / num) return NULL;
  
  block = malloc(size);
  if (!block) return NULL;
  
  memset(block, 0, size);
  return block;
}

void *realloc(void *block, size_t size) {
  if (!block || !size) return malloc(size);
  
  header_t *header;
  void *ret;
  
  header = (header_t*)block - 1;
  if (header->s.size >= size) return block;
  
  ret = malloc(size);
  if (ret) {
    memcpy(ret, block, header->s.size);
    free(block);
  }
  return ret;
}
