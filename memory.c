/*
 * memory.c
 * COMP 40 Fall 2019 um
 * 
 * Implementation of memory interface
 *
 * Written by:    Troy Prebenda, Tim Holt
 * Last modified: Nov. 15, 2019
 */


#include "memory.h"
#include "assert.h"


/******************* PRIVATE UM FUNCTION PROTOTYPES **************************/
uint32_t add_seg(Mem memory, Seq_T new_seg);
uint32_t rem_seg(Mem memory, uint32_t seg_ID);


/************************** PUBLIC FUNCTIONS *********************************/

/* 
 * Function: new_Mem
 * Purpose:  ALlocates memory for Mem struct object
 * Input:    none
 * Output:   the newly allocated Mem struct 
 * Notes:    Allocates memory for Mem object, to be cleared by 
 *           free_Mem()
 */ 
Mem new_Mem()
{

    Mem memory = malloc(sizeof(struct Mem));
    assert(memory != NULL);

    memory -> segments = Seq_new(1);
    memory -> freed_segs = Seq_new(0);

    return memory;

}

/* 
 * Function: free_Mem
 * Purpose:  Frees memory associated with a Mem struct instance
 * Input:    memory - an instance of a Mem struct
 * Output:   none 
 * Notes:    Frees memory associated with a Mem struct, allocated via the
 *           new_Mem function
 */
void free_Mem(Mem memory)
{
    assert(memory != NULL);

    int num_segs = Seq_length(memory -> segments);
    for (int i = 0; i < num_segs; i++) {
        Seq_T curr_seq = Seq_get(memory -> segments, i);
        if (curr_seq != NULL) {
            Seq_free(&(curr_seq));
        }
    }

    Seq_free(&(memory -> segments));
    Seq_free(&(memory -> freed_segs));

    free(memory);

}

/* 
 * Function: load_seg0
 * Purpose:  Loads a sequence of uint32_ts into the 1st element of the memory
 *           sequence
 * Input:    memory - a Mem struct representing memory segments,  
 * Output:   none 
 * Notes:    This function is designed to load instructions from a sequence
 *           into the appropriate place in memory
 */
void load_seg0(Mem memory, Seq_T seg0)
{
    assert(memory != NULL);
    assert(seg0 != NULL);

    Seq_addlo(memory -> segments, seg0);

}

/* 
 * Function: seg_length
 * Purpose:  gets the length of a given segment of memory
 * Input:    memory - a Mem struct, seg_ID - a uint32_t representing the
 *           segment of interest
 * Output:   a uint32_t representing the length of the segment of interest
 */ 
uint32_t seg_length(Mem memory, uint32_t seg_ID)
{
    assert(memory != NULL);

    return Seq_length(Seq_get(memory -> segments, seg_ID));

}


/* 
 * Function: map_seg
 * Purpose:  Allocates memory for a new segment of memory
 * Input:    memory - a Mem struct representing memory segments, num_words -
 *           a uint32_t representing the number of elements in the new segment
 * Output:   a uint32_t representing the ID of the newly mapped segment
 */ 
uint32_t map_seg(Mem memory, uint32_t num_words)
{

    assert(memory != NULL);

    Seq_T new_seg = Seq_new(num_words);
    /* Initializes all words in segment to 0 */
    for (uint32_t i = 0; i < num_words; i++) {
        Seq_addhi(new_seg, 0);
    }
    
    return add_seg(memory, new_seg);

}

/* 
 * Function: add_seg
 * Purpose:  adds a new sequence to the larger memory sequence in an available
 *           location
 * Input:    memory - a Mem struct representing memory segments, new_seg -
 *           a new sequence representing the segment to be added to the memory
 *           sequence
 * Output:   a uint32_t representing the ID of the newly added segment
 * Notes:    Private helper function
 */ 
uint32_t add_seg(Mem memory, Seq_T new_seg)
{
    assert(memory != NULL);
    assert(new_seg != NULL);

    int num_freed = Seq_length(memory -> freed_segs);
    uint32_t pos;

    if (num_freed > 0) {
        pos = (uint32_t)(uintptr_t)(Seq_remlo(memory -> freed_segs));
        Seq_put(memory -> segments, pos, new_seg);
    }
    else {
        pos = Seq_length(memory -> segments);
        Seq_addhi(memory -> segments, new_seg);
    }

    return pos;

}

/* 
 * Function: unmap_seg
 * Purpose:  frees a segment of memory and makes ID available for future use
 * Input:    memory - a Mem struct representing memory segments, seg_ID -
 *           a uint32_t representing the ID of the segment to be freed
 * Output:   none
 */ 
void unmap_seg(Mem memory, uint32_t seg_ID)
{
    assert(memory != NULL);

    uint32_t freed_ID = rem_seg(memory, seg_ID);

    /* Add to list of freed segment IDs */
    Seq_addhi(memory -> freed_segs, (void *)(uintptr_t)freed_ID);

}


/* 
 * Function: rem_seg
 * Purpose:  frees the memory associated with a segment of memory 
 * Input:    memory - a Mem struct representing memory segments, seg_ID -
 *           a uint32_t representing the ID of the segment to be freed
 * Output:   a uint32_t representing the ID of the newly freed segment
 * Notes:    Private helper function
 */ 
uint32_t rem_seg(Mem memory, uint32_t seg_ID)
{
    assert (memory != NULL);

    Seq_T to_remove = Seq_get(memory -> segments, seg_ID);
    Seq_free(&to_remove);

    Seq_put(memory -> segments, seg_ID, NULL);

    return seg_ID;

}

/* 
 * Function: get_val
 * Purpose:  gets the value from a specified index in a specified segment
 * Input:    memory - a Mem struct representing memory segments, seg_ID -
 *           a uint32_t representing the ID of the segment of interest,
 *           word_idx - a uint32_t representing the index of the sequence
 *           where the value of interest is located
 * Output:   a uint32_t representing the value of interest
 */ 
uint32_t get_val(Mem memory, uint32_t seg_ID, uint32_t word_idx)
{

    assert(memory != NULL);

    Seq_T segment = Seq_get(memory -> segments, seg_ID);

    return (uint32_t)(uintptr_t)Seq_get(segment, word_idx);

}

/* 
 * Function: put_val
 * Purpose:  puts a value in a specified index in a specified segment
 * Input:    memory - a Mem struct representing memory segments, seg_ID -
 *           a uint32_t representing the ID of the segment of interest,
 *           word_idx - a uint32_t representing the index of the sequence
 *           where the value is to be placed, val - a uint32_t representing
 *           the value to be inserted into the memory sequence
 * Output:   none
 */ 
void put_val(Mem memory, uint32_t seg_ID, uint32_t word_idx, uint32_t val)
{
    assert(memory != NULL);

    Seq_T segment = Seq_get(memory -> segments, seg_ID);
    assert(segment != NULL);
    
    Seq_put(segment, word_idx, (void *)(uintptr_t)val);

}

/* 
 * Function: duplicate_seg
 * Purpose:  duplicates a segment of memory and replaces a segment of memory
 *           with its duplicate
 * Input:    memory - a Mem struct representing memory segments, orig - a 
 *           uint32_t representing the segment ID of the memory to be
 *           duplicated, destination - a uint32_t representing the segment
 *           ID of the segment in memory where the duplicate will be placed
 * Output:   none
 */ 
void duplicate_seg(Mem memory, uint32_t orig, uint32_t destination)
{
    assert(memory != NULL);

    if (orig != destination) {
        Seq_T segment = Seq_get(memory -> segments, orig);
        int len = Seq_length(segment);
    
        Seq_T duplicate = Seq_new(len);

        for (int i = 0; i < len; i++) {
            Seq_addhi(duplicate, Seq_get(segment, i));
        }

        Seq_T prev = Seq_put(memory -> segments, destination, duplicate);
        Seq_free(&prev);
    }

}