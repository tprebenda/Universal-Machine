/*
 * input.c
 * COMP 40 Fall 2019 um
 * 
 * Implementation for input processing interface
 *
 * Written by:    Troy Prebenda, Tim Holt
 * Last modified: Nov. 15, 2019
 */

#include <sys/types.h>
#include <sys/stat.h>
#include "assert.h"

#include "input.h"
#include "bitpack.h"
#include "memory.h"
#include "fileio.h"

/* Macros */
#define BYTES_PER_WORD (off_t)4
#define BITS_PER_BYTE 8


/******************* PRIVATE UM FUNCTION PROTOTYPES **************************/
int get_num_words(char *um_name);


/************************** PUBLIC FUNCTIONS *********************************/

/* 
 * Function: load_instructions
 * Purpose:  Packs all instructions from input file into 32bit words and loads
 *           them into segment 0 of new Mem object
 * Input:    char *um_file
 * Output:   Mem struct object
 * Notes:    Closes the input file
 */ 
Mem load_instructions(char *um_file)
{
    
    Mem memory = new_Mem();
    Seq_T seg0 = Seq_new(1);

    int c;
    uint32_t word;
    off_t num_words = get_num_words(um_file);
    FILE *fp = open_read_file(um_file);

    /* Packs the instructions into individual 32bit words, adds them to seg0 */
    for (off_t i = 0; i < num_words; i++)  {
        for (int j = (BYTES_PER_WORD - 1); j >= 0; j--) {
            c = fgetc(fp);
            word = Bitpack_newu(word, BITS_PER_BYTE, (j * BITS_PER_BYTE), c);
        }
        Seq_addhi(seg0, (void *)(uintptr_t)word);
    }
    
    /* Loads seg0 into memory struct object */
    load_seg0(memory, seg0);

    close_file(fp);

    return memory;

}


/* 
 * Function: get_num_words
 * Purpose:  Uses stat struct to get the total number of instructions from file
 * Input:    char *um_file
 * Output:   int
 * Notes:    Exits (failure) if given file cannot be opened
 */ 
int get_num_words(char *um_file)
{

    struct stat sb;
    if (stat(um_file, &sb) == -1) {
        fprintf(stderr, "Could not open and get stats of given file.\n");
    }

    off_t num_bytes = sb.st_size;

    /* In case given .um file does not include properly sized 32bit words */
    if ((num_bytes % BYTES_PER_WORD) != 0) {
        fprintf(stderr, "Improperly formatted file for um execution.\n");
        exit(EXIT_FAILURE);
    }

    return (num_bytes / BYTES_PER_WORD);
    
}