#ifndef FIRST_PASS_UTILITIES_H
#define FIRST_PASS_UTILITIES_H

/* Function prototypes */
void process_data(char *);
void process_instruction(char *);
char *process_label(char *, int);
int is_empty(char *);
int is_comment(char *);
int is_data(char *); 
int is_instruction(char *);

#endif 