
#include "heap.h"

void _init_heap()
{
	heap.first_pool = 0; // initialize the heap pointer
	_add_pool(&heap, (unsigned int)HEAP_ADDRESS, HEAP_SIZE, HEAP_BLOCK_SIZE);  // add block to heap
}

void * _malloc(unsigned int size)
{
	return _BitmapAlloc(&heap, size);
}

int _add_pool(struct _HEAP *heap, uint32 block_address, uint32 block_size, uint32 internal_block_size)
{
	_HEAPBLOCK		*block;
	uint32				block_count;
	uint32				x;
	uint8				*bitmap;

	block = (_HEAPBLOCK*)block_address;
	block->total_size = block_size - sizeof(_HEAPBLOCK);
	block->block_size = internal_block_size;

	block->next = heap->first_pool;
	heap->first_pool = block;

	block_count = block_size / internal_block_size;
	bitmap = (uint8*)&block[1];

	/* clear bitmap */
	for (x = 0; x < block_count; ++x) {
		bitmap[x] = 0;
	}

	/* reserve room for bitmap */
	block_count = (block_count / internal_block_size) * internal_block_size < block_count ? block_count / internal_block_size + 1 : block_count / internal_block_size;
	for (x = 0; x < block_count; ++x) {
		bitmap[x] = 5;
	}

	block->last_free_block = block_count - 1;

	block->used = block_count;

	return 1;
}

static uint8 _getNextAllocID(uint8 a, uint8 b) 
{
	uint8		c;
	for (c = a + 1; c == b || c == 0; ++c);
	return c;
}

void *_BitmapAlloc(struct _HEAP *heap, uint32 size) 
{
	_HEAPBLOCK			*block;
	uint8				*bitmap;
	uint32				block_count;
	uint32				x, y, z; // loop counters
	uint32				bneed;
	uint8				next_id;

	/* iterate blocks */
	for (block = heap->first_pool; block; block = block->next) {
		/* check if block has enough room */
		if (block->total_size - (block->used * block->block_size) >= size) {

			block_count = block->total_size / block->block_size;
			bneed = (size / block->block_size) * block->block_size < size ? size / block->block_size + 1 : size / block->block_size;
			bitmap = (uint8*)&block[1];

			for (x = (block->last_free_block + 1 >= block_count ? 0 : block->last_free_block + 1); x != block->last_free_block; ++x) {
				/* just wrap around */
				if (x >= block_count) {
					x = 0;
				}

				if (bitmap[x] == 0) {
					/* count free blocks */
					for (y = 0; bitmap[x + y] == 0 && y < bneed && (x + y) < block_count; ++y);

					/* we have enough, now allocate them */
					if (y == bneed) {
						/* find ID that does not match left or right */
						next_id = _getNextAllocID(bitmap[x - 1], bitmap[x + y]); //get an ID for the bitmap. not used for more than allocating internal blocks in the map

																				 /* allocate by setting id */
						for (z = 0; z < y; ++z) {
							bitmap[x + z] = next_id;
						}

						/* optimization */
						block->last_free_block = (x + bneed) - 2;

						/* count used blocks NOT bytes */
						block->used += y;

						return (void*)(x * block->block_size + (uint8*)&block[1]);
					}

					/* x will be incremented by one ONCE more in our FOR loop */
					x += (y - 1);
					continue;
				}
			}
		}
	}

	return 0;
}

void _free(struct _HEAP *heap, void* allocation)
{
	_HEAPBLOCK			*pool;
	uint8				*bitmap;
	uint32				block_count;
	uint32				allocation_base_address;
	uint32				x, end; // loop counters
	uint8				alloc_id_to_clear;
	uint32				offset_in_pool, allocation_index;

	allocation_base_address = (uint32)allocation;
	/* iterate pools */
	for (pool = heap->first_pool; pool; pool = pool->next)
	{
		//Check that the allocation to free is withing this pool
		if (((uint32)&pool[1] + pool->total_size / pool->block_size) < allocation_base_address && ((uint32)&pool[1] + pool->total_size) > allocation_base_address)
		{
			offset_in_pool = allocation_base_address - (uint32)&pool[1];

			//calculate the index for the allocated range
			allocation_index = (offset_in_pool / pool->block_size);
			
			//assign the bitmap ponter the address for the start of the bitmap
			bitmap = (uint8*)&pool[1];

			//get the id for the allocation that is to be removed
			alloc_id_to_clear = bitmap[allocation_index];

			end = pool->total_size / pool->block_size;
			for (x = allocation_index; bitmap[x] == alloc_id_to_clear && x < end; ++x) {
				bitmap[x] = 0;
			}
			/* update free block count */
			pool->used -= x - allocation_index;
			return;
		}
		
	}
}

void _zero_memory(struct _HEAP *heap, void* allocation)
{
	_HEAPBLOCK			*pool;
	uint8				*bitmap;
	uint32				block_count;
	uint32				allocation_base_address;
	uint32				x, end, blockIndex; // loop counters
	uint8				alloc_id_to_zero;
	uint32				offset_in_pool, allocation_index;

	allocation_base_address = (uint32)allocation;
	/* iterate pools */
	for (pool = heap->first_pool; pool; pool = pool->next)
	{
		//Check that the allocation to free is withing this pool
		if (((uint32)&pool[1] + pool->total_size / pool->block_size) < allocation_base_address && ((uint32)&pool[1] + pool->total_size) > allocation_base_address)
		{
			offset_in_pool = allocation_base_address - (uint32)&pool[1];

			//calculate the index for the allocated range
			allocation_index = (offset_in_pool / pool->block_size);

			//assign the bitmap ponter the address for the start of the bitmap
			bitmap = (uint8*)&pool[1];

			//get the id for the allocation that is to be removed
			alloc_id_to_zero = bitmap[allocation_index];

			end = pool->total_size / pool->block_size;
			for (x = allocation_index; bitmap[x] == alloc_id_to_zero && x < end; ++x) {
				uint8 *block = (x * pool->block_size + (uint8*)&pool[1]);
				for (blockIndex = 0; blockIndex < pool->block_size; blockIndex++)
				{
					block[blockIndex] = 0x00;
				}
			}

			return;
		}

	}
}
