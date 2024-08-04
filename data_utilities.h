#ifndef DATA_UTILITIES_H
#define DATA_UTILITIES_H

void process_data_data(char *, FileInfo *, MachineCodeImage *);
void process_string_data(char *, FileInfo *, MachineCodeImage *);
void process_entry_data(char *, EntryTableNode *);
void process_extern_data(char *, ExternTableNode *);

#endif 