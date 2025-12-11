#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned char buffer[256*1024];

void generate_sparse_arrays(const char* input_file, const char* output_file, const char* array_prefix, size_t min_zero_block) {
    FILE* infile = fopen(input_file, "rb");
    if (!infile) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    FILE* outfile = fopen(output_file, "w");
    if (!outfile) {
        perror("Error opening output file");
        fclose(infile);
        exit(EXIT_FAILURE);
    }

    unsigned char buffer[256 * 1024];
    unsigned char temp_buffer[256 * 1024]; // buffer for zeros
    size_t bytes_read;
    size_t count = 0; // zeros counter

    unsigned long long array_index = 0;
    unsigned long long zero_index = 0;

    size_t zero_count = 0;

    // fprintf(outfile, "// Generated sparse arrays\n");

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), infile)) > 0) {
        for (size_t i = 0; i < bytes_read; ++i) {
            if (buffer[i] == 0) {
                zero_count++;
            }
            else {
                // Якщо зустріли ненульовий байт після нулів
                if (zero_count > 0) {
                    if (zero_count >= min_zero_block) {
                        // Додаємо великий блок нулів як окрему секцію
                        if (count > 0) {
                            // Записуємо поточний ненульовий масив
                            fprintf(outfile, "unsigned char %s_%llu[] = {\n    ", array_prefix, array_index++);
                            for (size_t j = 0; j < count; ++j) {
                                fprintf(outfile, "0x%02X,", temp_buffer[j]);
                                if ((j + 1) % 16 == 0) fprintf(outfile, "\n    ");
                            }
                            fprintf(outfile, "\n};\n");
                            fprintf(outfile, "#define %s_%llu_SIZE %zu\n\n", array_prefix, array_index - 1, count);
                            count = 0;
                        }

                        // Записуємо блок нулів
                        fprintf(outfile, "#define %s_ZEROS_%llu %zu\n\n", array_prefix, zero_index++, zero_count);
                    }
                    else {
                        // Якщо блок нулів менший за поріг, додаємо його до поточного масиву
                        for (size_t j = 0; j < zero_count; ++j) {
                            temp_buffer[count++] = 0;
                        }
                    }
                    zero_count = 0;
                }

                // Додаємо ненульовий байт до буфера
                temp_buffer[count++] = buffer[i];
            }
        }
    }

    // Обробляємо залишкові нулі
    if (zero_count > 0) {
        if (zero_count >= min_zero_block) {
            // Записуємо великий блок нулів
            fprintf(outfile, "#define %s_ZEROS_%llu %zu\n\n", array_prefix, zero_index++, zero_count);
        }
        else {
            // Додаємо залишкові нулі до поточного масиву
            for (size_t j = 0; j < zero_count; ++j) {
                temp_buffer[count++] = 0;
            }
        }
    }

    // Записуємо залишкові ненульові байти
    if (count > 0) {
        fprintf(outfile, "unsigned char %s_%llu[] = {\n    ", array_prefix, array_index++);
        for (size_t j = 0; j < count; ++j) {
            fprintf(outfile, "0x%02X,", temp_buffer[j]);
            if ((j + 1) % 16 == 0) fprintf(outfile, "\n    ");
        }
        fprintf(outfile, "\n};\n");
        fprintf(outfile, "#define %s_%llu_SIZE %zu\n\n", array_prefix, array_index - 1, count);
    }

    fprintf(outfile, "unsigned long long int %s_array_part_count = %llu;\n", array_prefix, array_index);
    fprintf(outfile, "unsigned char * %s[%llu] = {\n", array_prefix, array_index);
    for (unsigned long long int array_index_2 = 0; array_index_2 < array_index; ++array_index_2) {
        if (array_index_2) {
            fprintf(outfile, "    , ");
        }
        else {
            fprintf(outfile, "      ");
        }
        fprintf(outfile, "%s_%llu\n", array_prefix, array_index_2);
    }
    fprintf(outfile, "};\n");
    fprintf(outfile, "unsigned long long int %s_array_part_size[%llu] = {\n", array_prefix, array_index);
    for (unsigned long long int array_index_2 = 0; array_index_2 < array_index; ++array_index_2) {
        if (array_index_2) {
            fprintf(outfile, "    , ");
        }
        else {
            fprintf(outfile, "      ");
        }
        fprintf(outfile, "%s_%llu_SIZE\n", array_prefix, array_index_2);
    }
    fprintf(outfile, "};\n");

    fprintf(outfile, "\n");

    fprintf(outfile, "unsigned long long int %s_zero_part_count = %llu;\n", array_prefix, zero_index);
    fprintf(outfile, "unsigned long long int %s_zeros[%llu] = {\n", array_prefix, zero_index);
    for (unsigned long long int zero_index_2 = 0; zero_index_2 < zero_index; ++zero_index_2) {
        if (zero_index_2) {
            fprintf(outfile, "    , ");
        }
        else {
            fprintf(outfile, "      ");
        }
        fprintf(outfile, "%s_ZEROS_%llu\n", array_prefix, zero_index_2);
    }
    fprintf(outfile, "};\n");


    printf("Arrays and zero blocks written to %s.\n", output_file);

    fclose(infile);
    fclose(outfile);
}


#if 1

extern unsigned long long int a123_array_part_count;
extern unsigned char* a123[39];
extern unsigned long long int a123_array_part_size[39];
extern unsigned long long int a123_zero_part_count;
extern unsigned long long int a123_zeros[39];

void reconstruct_file(const char* output_file) {
    FILE* outfile = fopen(output_file, "wb");
    if (!outfile) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    unsigned long long int totalByteCount = 0;

    unsigned long long int array_index = 0;
    unsigned long long int zero_index = 0;

    a123_array_part_count + a123_zero_part_count;
    a123_array_part_count + a123_zero_part_count;
    for (unsigned long long int i = 0; i < a123_array_part_count + a123_zero_part_count; ++i) {
        if (i % 2 == 0) { // Чергування: дані та нулі
            unsigned char* current_array = NULL;
            current_array = a123[array_index++];
            //switch (array_index++) {
            //case 0: current_array = a123_0; break;
            //case 1: current_array = a123_1; break;
            //case 2: current_array = a123_2; break;
            //    // Додайте інші масиви
            //}
            if (current_array) {
                fwrite(current_array, 1, a123_array_part_size[array_index - 1]/*sizeof(current_array)*/, outfile);
                printf(": sizeof(current_array) = %llu\r\n", a123_array_part_size[array_index - 1]/*sizeof(current_array)*/);
                totalByteCount += a123_array_part_size[array_index - 1];
            }
        }
        else {
            unsigned long long int zero_count = 0;
            zero_count = a123_zeros[zero_index++];
            //switch (zero_index++) {
            //case 0: zero_count = a123_zeros_0; break;
            //case 1: zero_count = a123_zeros_1; break;
            //    // Додайте інші блоки
            //}
            if (zero_count > 0) {
                unsigned char* zeros = calloc(zero_count, sizeof(unsigned char));
                if (!zeros) {
                    perror("Memory allocation failed for zero block");
                    fclose(outfile);
                    exit(EXIT_FAILURE);
                }
                fwrite(zeros, 1, zero_count, outfile);
                printf("zero_count = %llu\r\n", zero_count);
                totalByteCount += zero_count;
                free(zeros);
            }
        }
    }

    fclose(outfile);
    printf("File reconstructed as %s.\n", output_file);
}

int main123() {
    const char* output_file = "reconstructed.bin";
    reconstruct_file(output_file);
    return 0;
}
#endif



int main(int argc, char* argv[]) {
    //if (argc != 5) {
    //    printf("Usage: %s <input file> <output file> <array prefix> <min zero block size>\n", argv[0]);
    //    return EXIT_FAILURE;
    //}

//
//    reconstruct_file("Project60_2.exe");
//
//    return EXIT_SUCCESS;
//

//    const char* input_file = "Project60.exe"; // "AsmForCode.exe"; //= argv[1];
//    const char* output_file = "AsmForCode.c";//= argv[2];
//    const char* input_file = "source.obj"; // "AsmForCode.exe"; //= argv[1];
//    const char* output_file = "obj.c";//= argv[2];
    const char* array_prefix = "a123";//= argv[3];

    const char* input_file = "Project60.exe";
    const char* output_file = "AsmForCode.c";//= argv[2];

    size_t min_zero_block = strtoul("20", NULL, 10);//size_t min_zero_block = strtoul(argv[4], NULL, 10);

    generate_sparse_arrays(input_file, output_file, array_prefix, min_zero_block);
    return EXIT_SUCCESS;
}
