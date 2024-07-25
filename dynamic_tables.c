#include <stdlib.h>
#include <string.h>
#define ALLOC_SIZE 50
#define MAX_LINE_LENGTH 80
#define MAX_LABEL_LENGTH 31
#define BITS_IN_WORD 15

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

typedef struct LabelOperand
{
    char name[MAX_LABEL_LENGTH];
    int poisition_in_instr_array;
    struct LabelOperand *next;
} LabelOperand;

typedef struct 
{
    int size;
    LabelOperand *head;
} LabelOperandList; 


/**
 * @brief This method creats an entry in the label table and inserts it at the head of the list.
 * 
 * @param t Pointer to the label table.
 * @param name The name of the label inserted to the table.
 * @param is_data A flag indicating if the new label is a label in the beginning of a data statement.
 */
void create_label_entry(LabelTable *t, char *name, int is_data)
{
    /*allocating new space for a label entry*/
    LabelEntry *new_entry = (LabelEntry *)malloc(sizeof(LabelEntry));
    if (new_entry == NULL) 
    {
        /*Handle memory allocation failure*/
        exit(EXIT_FAILURE);
    }
    /*adding values to the fields in the new entry and updating the table*/
    strcpy(new_entry->name, name);
    new_entry->is_data = is_data;
    t->size++;
    if(t->size == 1)
    {
        t->head = new_entry;
    }
    /*inserting the new entry at the head of the list\table*/
    LabelEntry *temp;
    temp = t->head;
    t->head = new_entry;
    t->head->next = temp;
}

/**
 * @brief This method adds the address to the label entry at the head of the linked-list
 * 
 * @param t Pointer to the label table.
 * @param address The address to be added to the label entry.
 */
void add_address_to_head(LabelTable *t, int address)
{
    memcpy(t->head->address, address, sizeof(int) * BITS_IN_WORD);
}

/**
 * @brief This method creats an entry in the macro table and inserts it at the head of the list.
 * 
 * @param t Pointer to the label table.
 * @param name The name of the macro inserted into the table.
 */
void create_macro_entry(MacroTable *t, char *name)
{
    MacroEntry *new_entry = (MacroEntry *)malloc(sizeof(MacroEntry));
    if (new_entry == NULL) 
    {
        /*Handle memory allocation failure*/
        exit(EXIT_FAILURE);
    }
    strcpy(new_entry->name, name);
    t->size++;
    if(t->size == 1)
    {
        t->head = new_entry;
    }
    MacroEntry *temp;
    temp = t->head;
    t->head = new_entry;
    t->head->next = temp;
}

/**
 * @brief This method adds the macro content to the macro entry at the head of the linked-list
 * 
 * @param t Pointer to the macro table.
 * @param str The content to be added to the macro entry.
 */
void add_content_to_head(MacroTable *t, char *str)
{
    strcat(t->head->content, str);
}

void add_label_operand(LabelOperandList *list, char *name, int position)
{
    LabelOperand *new_entry = (LabelOperand *)malloc(sizeof(LabelOperand));
    if (new_entry == NULL) 
    {
        /*Handle memory allocation failure*/
        exit(EXIT_FAILURE);
    }
    strcpy(new_entry->name, name);
    new_entry->poisition_in_instr_array = position;
    list->size++;
    if(list->size == 1)
    {
        list->head = new_entry;
    }
    LabelOperand *temp;
    temp = list->head;
    list->head = new_entry;
    list->head->next = temp;
}

