#include"api.h"

void start_API(t_log *logger){

	char *input;
	input = readline(">");
	while(strcmp("", input)) {
		processQuery(input, logger);
		free(input);
		input = readline(">");
	}
	free(input);
}

e_query processQuery(char *query, t_log *logger) {

	char log_msg[100];
	e_query queryType;
	char **args = string_split(query, " ");
//			parseQuery(query);

	queryType = getQueryType(args[0]); //guardamos el tipo de query por ej: SELECT

	int invalidQuery = validateQuerySyntax(args, queryType); //validamos que sea correcta y sino lanzamos exception
	if (!invalidQuery){
		return queryError();
	}

	switch(queryType) { //identificamos query y procedemos a su ejecucion

		case QUERY_SELECT:

			printf("%s",qselect(args[1], args[2]));
//			sprintf(log_msg, "Recibi un SELECT %s %s", args[1], args[2]);
			free(args);
			break;

		case QUERY_INSERT:

			if(args[4] == NULL) args[4] = string_itoa(getCurrentTime());
			qinsert(args[1], args[2], args[3], args[4]);
//			sprintf(log_msg, "Recibi un INSERT %s %s %s", args[1], args[2], args[3]);
			free(args);
			break;

		case QUERY_CREATE:
			if(qcreate(args[1], args[2], args[3], args[4]))
			printf("creado con exito\n");
			else printf("error en la creacion\n");
//			sprintf(log_msg, "Recibi un CREATE %s %s %s %s", args[1], args[2], args[3], args[4]);
			free(args);
			break;

		case QUERY_DESCRIBE:

			//describe(args[1]);

			sprintf(log_msg, "Recibi un DESCRIBE %s", args[1]);
			free(args);
			break;

		case QUERY_DROP:

			//drop(args[1]);

			sprintf(log_msg, "Recibi un DROP %s", args[1]);
			free(args);
			break;

		default:
			free(args);
			return queryError(logger);

	}

//	log_info(logger, log_msg);
	return queryType;
}


uint64_t getCurrentTime(){
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return (uint64_t)((tv.tv_sec)*1000 + (tv.tv_usec)/1000);
}

char **parseQuery(char *query){

	if(string_starts_with(query,"INSERT")){
		char **value = string_split(query,"\"");
		char **args = string_split(query," ");
		char **toReturn = malloc(sizeof(char**));
		char *x0 = string_new();
		char *x1 = string_new();
		char *x2 = string_new();
		char *x3 = string_new();
		char *x4 = string_new();
		strcpy(x0,args[0]);
		strcpy(x1,args[1]);
		strcpy(x2,args[2]);
		strcpy(x3,value[1]);
		toReturn[0] = x0;
		toReturn[1] = x1;
		toReturn[2] = x2;
		toReturn[3] = x3;
		if(value[2] == NULL){
			strcpy(x4,"null");
			toReturn[4] = x4;
		}
		else{
			strcpy(x4,value[2]);
			string_trim(&x4);
			toReturn[4] = x4;
		}
		;
		printf("%s\n",toReturn[0]);
		printf("%s\n",toReturn[1]);
		printf("%s\n",toReturn[2]);
		printf("%s\n",toReturn[3]);
		printf("%s\n",toReturn[4]);
		free(value); free(args);
		return toReturn;
	}
	else{
		char **args = string_split(query," ");
		return args;
	}

}
