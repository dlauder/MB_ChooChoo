#ifndef _HEAP_H_
#define _HEAP_H_

#include "..\defines\datatypes.h"


typedef struct _HEAPBLOCK
{
	struct _HEAPBLOCK *next;
	uint32 total_size;
	uint32 used;
	uint32 block_size;
	uint32 last_free_block;
}_HEAPBLOCK;

typedef struct _HEAP
{
	struct _HEAPBLOCK *first_pool;
}_HEAP;

 struct _HEAP heap;

#define HEAP_ADDRESS	0x18000
#define HEAP_SIZE		0x8000
#define HEAP_BLOCK_SIZE	0x10

void _init_heap();
int _add_pool(struct _HEAP *heap, uint32 block_address, uint32 block_size, uint32 internal_block_size);
static uint8 _getNextAllocID(uint8 a, uint8 b);
void *_BitmapAlloc(struct _HEAP *heap, uint32 size);
void * _malloc(unsigned int size);
void _free(struct _HEAP *heap, void* allocation);
void _zero_memory(struct _HEAP *heap, void* allocation);


#endif