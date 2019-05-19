#include"Kernel.h"

int server;

t_config *config;
t_queue *new, *ready;
sem_t MUTEX_NEW, MUTEX_READY, PROC_PEND;
t_log *logger;

int main(int argc, char **argv) {

	init_kernel();

	start_API(logger);

	config_destroy(config);
	log_destroy(logger);
	queue_destroy_and_destroy_elements(new, process_destroy);
	queue_destroy_and_destroy_elements(ready, process_destroy);

	return 0;
}

void load_config() {
	config = config_create("../.config");
	if(config == NULL) {
		log_error(logger, "No se pudo abrir el archivo de configuracion");
		exit(-1);
	}
}

void init_kernel() {
	iniciar_logger(&logger);
	load_config();
	new = queue_create();
	ready = queue_create();
	sem_init(&MUTEX_NEW, 0, 1);
	sem_init(&MUTEX_READY, 0, 1);
	sem_init(&PROC_PEND, 0, 0);
	int memSocket = connect_to_memory(get_memory_ip(), get_memory_port());
	request_memory_pool(memSocket);
	closeConnection(memSocket);
}

e_query newQuery(char *query) {

	char log_msg[100];
	e_query queryType;

	char **args = validate_query_and_return_args(query);
	if(args == NULL)
		return queryError();

	queryType = getQueryType(args[0]);

	int isQuery = 0;
	switch(queryType) {
		case QUERY_SELECT:
			isQuery = 1;
			sprintf(log_msg, "Recibi un SELECT %s %s", args[1], args[2]);
			break;

		case QUERY_INSERT:
			isQuery = 1;
			sprintf(log_msg, "Recibi un INSERT %s %s %s", args[1], args[2], args[3]);
			break;

		case QUERY_CREATE:
			isQuery = 1;
			sprintf(log_msg, "Recibi un CREATE %s %s %s %s", args[1], args[2], args[3], args[4]);
			break;

		case QUERY_DESCRIBE:
			isQuery = 1;
			sprintf(log_msg, "Recibi un DESCRIBE %s", args[1]);
			break;

		case QUERY_DROP:
			isQuery = 1;
			sprintf(log_msg, "Recibi un DROP %s", args[1]);
			break;

		case QUERY_JOURNAL:
			sprintf(log_msg, "Recibi un JOURNAL");
			break;

		case QUERY_ADD:
			sprintf(log_msg, "Recibi un ADD MEMORY %s TO %s", args[2], args[4]);
			break;

		case QUERY_RUN:
			if(!read_lql_file(args[1]))
				return queryError();
			sprintf(log_msg, "Recibi un RUN %s", args[1]);
			break;

		case QUERY_METRICS:
			sprintf(log_msg, "Recibi un METRICS");
			break;

		default:
			return queryError(logger);
	}

	if(isQuery) {
		t_query *newQuery = query_create(queryType, args);
		t_list *queryList = list_create();
		list_add(queryList, (void*)newQuery);
		t_process *newProcess = process_create(queryList);

		add_process_to_new(newProcess);
	}

	log_info(logger, log_msg);
	return queryType;
}

int read_lql_file(char *path) {
	char buffer[200];
	FILE *lql = fopen(path, "rt");
	if(lql == NULL) {
		char msg[200];
		sprintf(msg, "No se ha podido abrir el archivo %s", path);
		log_error(logger, msg);
		return 0;
	}

	t_list *fileQuerys = list_create();

	while(fgets(buffer, sizeof(buffer), lql)) {
		char **args = validate_query_and_return_args(buffer);
		if(args == NULL) {
			list_destroy_and_destroy_elements(fileQuerys, query_destroy);
			fclose(lql);
			printf("El archivo no es valido.\n");
			return 0;
		}

		e_query queryType = getQueryType(args[0]);
		t_query *currentQuery = query_create(queryType, args);
		list_add(fileQuerys, (void*)currentQuery);
	}

	t_process *newProcess = process_create(fileQuerys);
	add_process_to_new(newProcess);

	fclose(lql);
	return 1;
}

void add_process_to_new(t_process* process) {
	sem_wait(&MUTEX_NEW);
	queue_push(new, (void*) process);
	sem_post(&MUTEX_NEW);
	sem_post(&PROC_PEND);
	log_info(logger, "Nuevo proceso agregado a la cola de NEW");
}

int connect_to_memory(char *IP, int PORT) {
	return connectToServer(IP, PORT);
}

void request_memory_pool(int memSocket) {

}

char *get_memory_ip() {
	return config_get_string_value(config, "MEM_IP");
}

int get_memory_port() {
	return config_get_int_value(config, "MEM_PORT");
}

int get_quantum() {
	return config_get_int_value(config, "QUANTUM");
}

int get_multiprogramming_degree() {
	return config_get_int_value(config, "MULT_DEGREE");
}

int get_metadata_refresh_rate() {
	return config_get_int_value(config, "MD_REFRESH_RATE");
}

int get_execution_delay() {
	return config_get_int_value(config, "EXEC_DELAY");
}
