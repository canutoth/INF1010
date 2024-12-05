#include <stdio.h>
#include <stdlib.h>

#define MAX_CPFS 1000

// funcoes hash
long long hash_function1(long long cpf, int prime_number, int table_size) {
	int part1 = (cpf / 10000) & 0xFFFF;
	int part2 = cpf % 10000;
	return ((part1 * prime_number + part2) % table_size);
}

int hash_function2(long long cpf, int prime_number2) {
	int step = prime_number2 - (cpf % prime_number2);
	return (step % 2 == 0) ? step + 1 : step;
}

int load_cpfs_from_file(const char* filename, long long cpfs[]) {
	FILE* file = fopen(filename, "r");
	if (!file) {
		printf("Erro ao abrir o arquivo\n");
		return -1;
	}

	int count = 0;
	while (count < MAX_CPFS && fscanf(file, "%lld", &cpfs[count]) == 1) {
		count++;
	}

	fclose(file);
	return count;
}

void initialize_table(long long* hash_table, int table_size) {
	for (int i = 0; i < table_size; i++) {
		hash_table[i] = -1;
	}
}

int insert_cpfs(long long cpfs[], long long cpf_count, long long* hash_table, int table_size, int prime_number1, int prime_number2) {
	int collisions = 0;
	int cpf_collisions[MAX_CPFS] = { 0 };

	for (int i = 0; i < cpf_count; i++) {
		int index = hash_function1(cpfs[i], prime_number1, table_size);
		int step = hash_function2(cpfs[i], prime_number2);
		int j = 0;

		while (hash_table[(index + j * step) % table_size] != -1) {
			collisions++;
			cpf_collisions[i]++;
			j++;
		}
		hash_table[(index + j * step) % table_size] = cpfs[i];
	}

	FILE* file = fopen("colisoes_por_cpf.txt", "w");
	if (file != NULL) {
		for (int i = 0; i < cpf_count; i++) {
			//fprintf(file, "index: %d\tCPF: %lld\tnum_collisions: %d\n\n", i, cpfs[i], cpf_collisions[i]);
			fprintf(file, "%d\t%d\n", i, cpf_collisions[i]);
		}
		fclose(file);
	}
	else {
		printf("Erro ao abrir o arquivo dados.txt\n");
	}

	return collisions;
}

int count_empty_positions(long long* hash_table, int table_size) {
	int empty_count = 0;
	for (int i = 0; i < table_size; i++) {
		if (hash_table[i] == -1) {
			empty_count++;
		}
	}
	return empty_count;
}

int main(void) {
	const char* filename = "cpfs.txt";
	long long cpfs[MAX_CPFS];
	long long cpf_count = load_cpfs_from_file(filename, cpfs);

	if (cpf_count == -1) {
		return 1;
	}

	int table_size = 1229;
	int prime_number1 = 1153;
	int prime_number2 = 409;

	long long* hash_table = (long long*)malloc(table_size * sizeof(long long));
	if (!hash_table) {
		printf("Erro de memoria\n");
		return 1;
	}

	initialize_table(hash_table, table_size);

	int collisions = insert_cpfs(cpfs, cpf_count, hash_table, table_size, prime_number1, prime_number2);

	int empty_positions = count_empty_positions(hash_table, table_size);
	int occupied_positions = table_size - empty_positions;
	double occupancy_factor = ((double)occupied_positions / table_size) * 100;

	printf("\n\tHashing:\n");
	printf("\tprimo 1: %d - primo 2: %d - tamanho da tabela: %d\n", prime_number1, prime_number2, table_size);
	printf("\tnumero de colisoes: %d\n", collisions);
	printf("\tnumero de posicoes vazias: %d\n", empty_positions);
	printf("\tfator de ocupacao: %.2f%%\n", occupancy_factor);
	
	printf("\nTabela Hash:\n\n");
	for (int i = 0; i < table_size; i++) {
		if (hash_table[i] != -1) {
			printf("posicao %d: %lld\n", i, hash_table[i]);
		}
		else {
			printf("posicao %d: Vazio\n", i);
		}
	}

	free(hash_table);

	return 0;
}