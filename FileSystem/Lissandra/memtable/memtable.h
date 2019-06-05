#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<stdbool.h>
#include<commons/collections/list.h>
#include<commons/string.h>
#include<commons/txt.h>

extern t_list *memtable;

typedef struct{
	char *timestamp;
	char *key;
	char *value;
}Iinsert;

typedef struct{
	char *table;
	t_list *inserts;
}Itable;


void mt_insert(char *, char*, char *,char *);
bool mt_tableExists(char*);
t_list *mt_getTableToInsert(char*);
void mt_addNewInsert(t_list*, char*, char*, char*);
void mt_clean();
void mt_cleanPivot(t_list *);
void tableDestroyer(void*);
void insertDestroyer(void*);