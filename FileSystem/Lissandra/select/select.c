#include"select.h"

char *qselect(char *table, char* strKey){

	char *url = string_new();
	t_list *list = list_create();
	FILE *file;
	string_append(&url,"tables/");
	string_append(&url,table);
	string_append(&url, ".bin");
	file = fopen(url,"r");
	loadList(list,file);
//	fclose(file);
	t_list *dataList = listToDATAmode(list);
	list_destroy_and_destroy_elements(list,free);
	char *value = string_new();
	uint16_t key = atoi(strKey);
	value = getValue(dataList,key);
	list_destroy_and_destroy_elements(dataList,dataSelect_destroy);
	free(url);
	return value;
}

void dataSelect_destroy(void* data ){
	free(((dataSelect*)data)->value);
	free(data);
}

//carga la lista con la info del archivo
void loadList(t_list *list,FILE *file){
	char *line = malloc(sizeof(char)*100);
	char *aux;
	while(fgets(line, sizeof(char)*100, file) != NULL){
		aux = malloc(sizeof(char)*(strlen(line)+1));
		strcpy(aux,line);
		list_add(list,aux);
	}
	free(line);
	fclose(file);
}

//duelvue el ultimo valor de la lista que matchea con la key
char *getValue(t_list *list,uint16_t key){
	t_list *sortedList;
	sortedList = list_sorted(list,biggerTimeStamp);

	bool _lastKey(void *elem){
		return isLastKey(key,elem);
	}
	char *value = malloc(sizeof(char)*100);
	dataSelect *returnValue =  (dataSelect*) list_find(sortedList, _lastKey);
	strcpy(value,returnValue->value);
	list_destroy_and_destroy_elements(sortedList,dataSelect_destroy);
	return value;
}

//duelvue true si el priemr elemento fue agregado despues que el segundo
bool biggerTimeStamp(void *elem1, void *elem2){
	return ((dataSelect*)elem1)->timeStamp > ((dataSelect*)elem2)->timeStamp;
}

//devuelve true si el elemento que se le pasa coincide con la key
bool isLastKey(uint16_t key,void* elem){
	return key == ((dataSelect*)elem)->key;
}


//recibe una lista de "timestamp;key;value" y devuelve una transformada a tipo dataSelect
t_list *listToDATAmode(t_list *list){
	t_list *pivot = list_create();
	pivot = list_map(list,elemToDATAmode);
	return pivot;
}

//recibe un elemento de tipo "timestamp;key;value" devuelve uno de tipo dataSelect con los campos asignados respectivamente
void *elemToDATAmode(void *lfsElem){
	char **lfsArray = string_split(lfsElem, ";");
	dataSelect *pivot = malloc(sizeof(dataSelect));
	pivot->timeStamp = atoi((char*)lfsArray[0]);
	pivot->key = atoi((char*)lfsArray[1]);
	pivot->value = lfsArray[2];
	return pivot;
}