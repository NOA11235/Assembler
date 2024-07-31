#ifndef DYNAMIC_TABLES_H
#define DYNAMIC_TABLES_H
#include "common.h"

/*LabelEntry structer for the LabelTable, implemented as a linked-list*/
typedef struct LabelEntry
{
    char name[MAX_LABEL_LENGTH];
    int address[BITS_IN_WORD];
    int is_data : 1; /*one bit flag*/
    struct LabelEntry *next;
} LabelEntry;

typedef struct 
{
    int size;
    LabelEntry *head;
} LabelTable;

/*MacroEntry structer for the MacroTable, implemented as a linked-list */
typedef struct MacroEntry
{
    char name[MAX_LABEL_LENGTH];
    char content[MAX_LINE_LENGTH];
    struct MacroEntry *next;
} MacroEntry;

typedef struct 
{
    int size;
    MacroEntry *head;
} MacroTable;

/*LabelOperand structer for the LabelOperandList, implemented as a linked-list */
typedef struct LabelOperand
{
    char name[MAX_LABEL_LENGTH];
    int position_in_instruction_array;
    int position_in_file;
    struct LabelOperand *next;
} LabelOperand;

typedef struct 
{
    int size;
    LabelOperand *head;
} LabelOperandList;

/* Function prototypes */
void create_label_entry(LabelTable *, char *, int);
void add_address_to_head(LabelTable *, int);
void create_macro_entry(MacroTable *, char *);
void add_content_to_head(MacroTable *, char *);
void add_label_operand(LabelOperandList *, char *, int, int);

#endif