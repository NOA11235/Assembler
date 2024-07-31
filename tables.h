/*this file includes different tables used for the assembler*/
#ifndef TABLES_H
#define TABLES_H

#include "dynamic_tables.h"
#define MAX_OP_NAME_LEN 5
#define MAX_DATA_NAME_LEN 8
#define NUM_OF_OP 16
#define NUM_OF_DATA 4
#define NUM_OF_ADDRESS_METHODS 4

extern LabelTable symbol_table, extern_table, entry_table;
extern MacroTable macro_table;
extern LabelOperandList label_operand_list;

struct op_table
{
    int code;
    char name[MAX_OP_NAME_LEN];
    int num_of_operands;
    /*in those array if addressing method i is allowed, then than cell i would be 1 and otherwise 0*/
    int source_address_method[NUM_OF_ADDRESS_METHODS];
    int target_address_method[NUM_OF_ADDRESS_METHODS];
} op[] = {
            {0, "mov", 2, {1,1,1,1}, {0,1,1,1}},
            {1, "cmp", 2, {1,1,1,1}, {1,1,1,1}},
            {2, "add", 2, {1,1,1,1}, {0,1,1,1}}, 
            {3, "sub", 2, {1,1,1,1}, {0,1,1,1}}, 
            {4, "lea", 2, {0,1,0,0}, {0,1,1,1}}, 
            {5, "clr", 1, {0}, {0,1,1,1}}, 
            {6, "not", 1, {0}, {0,1,1,1}}, 
            {7, "inc", 1, {0}, {0,1,1,1}}, 
            {8, "dec", 1, {0}, {0,1,1,1}}, 
            {9, "jmp", 1, {0}, {0,1,1,0}}, 
            {10, "bne", 1, {0}, {0,1,1,0}}, 
            {11, "red", 1, {0}, {0,1,1,1}},
            {12, "prn", 1, {0}, {1,1,1,1}},
            {13, "jsr", 1, {0}, {0,1,1,0}},
            {14, "rts", 0, {0}, {0}},
            {15, "stop", 0, {0}, {0}}
       };

struct data_table
{
    int code;
    char name[MAX_DATA_NAME_LEN];
} data[] = {
            {0, ".data"},
            {1, ".string"},
            {2, ".entry"},
            {3, ".extern"}
       };

#endif