#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: machinecodegen_addon.cpp    *
*                                                  (draft!) *
*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#define DEBUG_RECONSTRUCT

unsigned char buffer[256 * 1024];

extern unsigned long long int a123_array_part_count;
extern unsigned char* a123[39];
extern unsigned long long int a123_array_part_size[39];
extern unsigned long long int a123_zero_part_count;
extern unsigned long long int a123_zeros[39];

extern unsigned long long int o123_array_part_count;
extern unsigned char* o123[5];
extern unsigned long long int o123_array_part_size[5];
extern unsigned long long int o123_zero_part_count;
extern unsigned long long int o123_zeros[4];

unsigned long long int buildTemplateForCodeObject(unsigned char* byteImage) {
    if (!byteImage) {
        exit(EXIT_FAILURE);
    }
    unsigned long long int byteIndex = 0;

    unsigned long long int totalByteCount = 0;

    unsigned long long int array_index = 0;
    unsigned long long int zero_index = 0;

    for (unsigned long long int i = 0; i < o123_array_part_count + o123_zero_part_count; ++i) {
        if (i % 2 == 0) {
            unsigned char* current_array = NULL;
            current_array = o123[array_index++];
            if (current_array) {
                //fwrite(current_array, 1, o123_array_part_size[array_index - 1]/*sizeof(current_array)*/, outfile);
                for (unsigned long long int localByteIndex = 0; localByteIndex < o123_array_part_size[array_index - 1]; ++localByteIndex) {
                    byteImage[byteIndex++] = current_array[localByteIndex];
                }
#ifdef DEBUG_RECONSTRUCT
                printf(": sizeof(current_array) = %llu\r\n", o123_array_part_size[array_index - 1]/*sizeof(current_array)*/);
#endif                
                totalByteCount += o123_array_part_size[array_index - 1];
            }
        }
        else {
            unsigned long long int zero_count = 0;
            zero_count = o123_zeros[zero_index++];
            if (zero_count > 0) {
                unsigned char* zeros = (unsigned char*)calloc(zero_count, sizeof(unsigned char));
                if (!zeros) {
                    perror("Memory allocation failed for zero block");
                    //fclose(outfile);
                    exit(EXIT_FAILURE);
                }
                //fwrite(zeros, 1, zero_count, outfile);
                for (unsigned long long int localByteIndex = 0; localByteIndex < zero_count; ++localByteIndex) {
                    byteImage[byteIndex++] = 0;
                }
#ifdef DEBUG_RECONSTRUCT
                printf("zero_count = %llu\r\n", zero_count);
#endif
                totalByteCount += zero_count;
                free(zeros);
            }
        }
    }

    //fclose(outfile);
#ifdef DEBUG_RECONSTRUCT
    printf("Image reconstructed.\n"/*, output_file*/);
#endif

    return byteIndex;
}

unsigned long long int buildTemplateForCodeImage(unsigned char* byteImage) {
    if (!byteImage) {
        exit(EXIT_FAILURE);
    }
    unsigned long long int byteIndex = 0;

    unsigned long long int totalByteCount = 0;

    unsigned long long int array_index = 0;
    unsigned long long int zero_index = 0;

    for (unsigned long long int i = 0; i < a123_array_part_count + a123_zero_part_count; ++i) {
        if (i % 2 == 0) {
            unsigned char* current_array = NULL;
            current_array = a123[array_index++];
            if (current_array) {
                //fwrite(current_array, 1, a123_array_part_size[array_index - 1]/*sizeof(current_array)*/, outfile);
                for (unsigned long long int localByteIndex = 0; localByteIndex < a123_array_part_size[array_index - 1]; ++localByteIndex) {
                    byteImage[byteIndex++] = current_array[localByteIndex];
                }
#ifdef DEBUG_RECONSTRUCT
                printf(": sizeof(current_array) = %llu\r\n", a123_array_part_size[array_index - 1]/*sizeof(current_array)*/);
#endif                
                totalByteCount += a123_array_part_size[array_index - 1];
            }
        }
        else {
            unsigned long long int zero_count = 0;
            zero_count = a123_zeros[zero_index++];
            if (zero_count > 0) {
                unsigned char* zeros = (unsigned char*)calloc(zero_count, sizeof(unsigned char));
                if (!zeros) {
                    perror("Memory allocation failed for zero block");
                    //fclose(outfile);
                    exit(EXIT_FAILURE);
                }
                //fwrite(zeros, 1, zero_count, outfile);
                for (unsigned long long int localByteIndex = 0; localByteIndex < zero_count; ++localByteIndex) {
                    byteImage[byteIndex++] = 0;
                }
#ifdef DEBUG_RECONSTRUCT
                printf("zero_count = %llu\r\n", zero_count);
#endif
                totalByteCount += zero_count;
                free(zeros);
            }
        }
    }

    //fclose(outfile);
#ifdef DEBUG_RECONSTRUCT
    printf("Image reconstructed.\n"/*, output_file*/);
#endif

    return byteIndex;
}

void writeBytesToFile(const char* output_file, unsigned char* byteImage, unsigned long long int imageSize) {
    if (!output_file || !byteImage) {
        perror("Error in write image to file");
        exit(EXIT_FAILURE);
    }
    
    FILE* outfile = fopen(output_file, "wb");
    if (!outfile) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    if (imageSize) {
        fwrite(byteImage, 1, imageSize, outfile);
    }

    fclose(outfile);
    printf("File \"%s\" saved.\n", output_file);
}