/*
 * memory.h
 * COMP 40 Fall 2019 um
 * 
 * Interface for Memory and segment management
 *
 * Written by:    Troy Prebenda, Tim Holt
 * Last modified: Nov. 15, 2019
 *
 * Description: This interface manages segmented memory
 *              for UM programs

 * Checked runtime errors: passing in NULL where a Mem struct
 *                         or a sequence is requested
 */

/* ------------------------------- includes -------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "seq.h"

/* ------------------------------- define ---------------------------------- */

#ifndef MEMORY_INCLUDED
#define MEMORY_INCLUDED

/* ---------------------------- struct defintions -------------------------- */

typedef struct Mem {
    Seq_T segments;
    Seq_T freed_segs;
} *Mem;

/* ------------------------------- prototypes------------------------------- */

/* allocates memory for a Mem struct */ 
Mem new_Mem();

/* frees the memory associated with a Mem struct */ 
void free_Mem(Mem memory);

/* loads a sequence of uint32_t instructions into segment 0 */
void load_seg0(Mem memory, Seq_T seg0);

/* returns the number of elements in the segment of interest */
uint32_t seg_length(Mem memory, uint32_t seg_ID);

/* maps a new segment with num_words elements */
uint32_t map_seg(Mem memory, uint32_t num_words);

/* unmaps a segment specified by seg_ID */
void unmap_seg(Mem memory, uint32_t seg_ID);

/* gets the value from a segment at a specified index */
uint32_t get_val(Mem memory, uint32_t seg_ID, uint32_t word_idx);

/* inserts a value in a segment at a specified index */ 
void put_val(Mem memory, uint32_t seg_ID, uint32_t word_idx, uint32_t val);

/* duplicates segment with ID orig and places the duplicate in segment
 * destination
 */
void duplicate_seg(Mem memory, uint32_t orig, uint32_t destination);


#endif