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
    for (int i = 0; i < cpf_count; i++) {
        int index = hash_function1(cpfs[i], prime_number1, table_size);
        int step = hash_function2(cpfs[i], prime_number2);
        int j = 0;
        while (hash_table[(index + j* step) % table_size] != -1) {
            collisions++;
            j++;
        }
        hash_table[(index + j * step) % table_size] = cpfs[i];
    }
    return collisions;
}

int test_combinations(long long cpfs[], long long cpf_count, int table_size) {
    int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
                101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193,
                197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307,
                311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421,
                431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547,
                557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
                661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797,
                809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929,
                937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, 1031, 1033, 1039,
                1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153,
                1163, 1171, 1181, 1187, 1193, 1201, 1213 };
    int prime_count = sizeof(primes) / sizeof(primes[0]);

    FILE* file = fopen("combinacoes_resultados.txt", "w");

    if (!file) {
        printf("Erro ao abrir o arquivo de resultados\n");
        return -1;
    }

    long long* hash_table = (long long*)malloc(table_size * sizeof(long long));
    if (!hash_table) {
        printf("Erro de memoria\n");
        return -1;
    }

    for (int i = 0; i < prime_count; i++) {
        for (int j = 0; j < prime_count; j++) {
            initialize_table(hash_table, table_size);
            int collisions = insert_cpfs(cpfs, cpf_count, hash_table, table_size, primes[i], primes[j]);
            fprintf(file, "Tabela tamanho:\t%d\tPrimo1:\t%d\tPrimo2:\t%d\tColisoes:\t%d\n", table_size, primes[i], primes[j], collisions);
            //printf("Tabela tamanho:\t%d\tPrimo1:\t%d\tPrimo2:\t%d\tColisoes:\t%d\n",table_size, primes[i], primes[j], collisions);
        }
    }

    free(hash_table);
    fclose(file);
    return 0;
}

int main(void) {
    const char* filename = "cpfs.txt";
    long long cpfs[MAX_CPFS];
    long long cpf_count = load_cpfs_from_file(filename, cpfs);

    if (cpf_count == -1) {
        return 1;
    }

    int table_sizes[] = { 1223, 1229 };
    int table_count = sizeof(table_sizes) / sizeof(table_sizes[0]);

    for (int k = 0; k < table_count; k++) {
        test_combinations(cpfs, cpf_count, table_sizes[k]);
    }

    printf("teste de combinacoes concluido. Resultados salvos em 'combinacoes_resultados.txt'.\n");
    return 0;
}