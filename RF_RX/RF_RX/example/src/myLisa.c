#include "myLisa.h"
#include <stdlib.h>
#include <math.h>
#include "syncField.h"
#include <stdio.h>
#include <string.h>
#include <time.h>


static const char alphabets[] =
{
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
    'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
    'y', 'z'
};

static const int powerOfTwo[] =
{
    1, 2, 4, 8, 16, 32, 64
};


/**
 * @brief getSetBits
 * @param c
 * @return
 */
int get_set_bits(char c) {
    int result = 0;
    for (int i = 0; i < 8; i++)
    {
        result += (c >> i) & 1;
    }
    return result;
}


void print_array(const char *array, int start, int end, const char* format) {
    for (int i = start; i < end; i++) {
        printf(format, array[i]);
    }
    printf("\n");
}

void corrupt_sync_field(int corrupt_percentage, char *sync_field, int sync_field_size) {
    int to_Corrupt = (int)(ceil(((double)(corrupt_percentage) * sync_field_size * 8.0)/100));
    srand(time(NULL));
    char temp[SYNC_FIELD_BYTES] = {0};
    strncpy(temp, sync_field, sync_field_size);

    while (to_Corrupt) {
        size_t byte_index= (size_t)((size_t)(rand())%sync_field_size);
        int bit_Index= rand()%8;

        if ((sync_field[byte_index] ^ (1 << bit_Index)) != temp[byte_index])
        {
            sync_field[byte_index] ^= (1 << bit_Index);
            to_Corrupt--;
        }
    }
}

void convert_bytes_to_bits(const char *bytes, int size, char *bits) {
    int bit_pos = 0;
    for (int byte = 0; byte < size; byte++) {
        for (int bit = 7; bit >= 0; bit--) {
            bits[bit_pos] = (bytes[byte] & (1 << bit)) ? '1' : '0';
            bit_pos++;
        }
    }
}

/**
 * @brief convertBitsToByte: This function shall convert binary hex value to a byte of type char
 * @param bits: Input string of 8 chars only i.e 01010000 -> Shall return char 'P'
 * @return: Returns char corresponding to the input
 */
char convert_8_bits_to_char(const char *bits) {
    int byte = 0;
    int count = 7;
    for (int i = 0; i < 8; i++) {
        byte += (bits[i] - 48) * powerOfTwo[count--];
    }
    return (char)(byte);
}

void write_text_file(const char *filename, const char* file_mode, const char *data_to_write, int number_of_bytes_to_write) {
    FILE *fp;
    fp = fopen(filename, file_mode);
    if (fp == NULL) {
        printf("Error writing file\n");
        exit(1);
    }
    fwrite(data_to_write, number_of_bytes_to_write, 1, fp);
    fclose(fp);
}

void read_text_file(const char *filename, char *data_to_read) {
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error reading file\n");
        exit(1);
    }
    fseek(fp, 0l, SEEK_END);
    int bytes_to_read = (int)ftell(fp);
    fseek(fp, 0l, SEEK_SET);
    fread(data_to_read, bytes_to_read, 1, fp);

    printf("File size: %d\n", bytes_to_read);
    fclose(fp);
}

void generate_junk_data(int junk_size, char *junk_data) {
    int i = 0;
    while ((junk_size--) && (junk_size != 0)) {
        junk_data[i++] = alphabets[rand()%26];
    }
}

/**
 * @brief getCorruptLevelFromTestData
 * @param start
 * @param end
 * @param data
 * @param sync
 * @return
 */
int get_corruption_level(int start, int end, const char *data, const char *sync) {
    int corruption_level = 0;
    for (int i = start, j = 0; i < end; i++, j++) {
        char c = (data[i] ^ sync[j]);
        if (c != 0){
            corruption_level += get_set_bits(c);
        }
    }
    return corruption_level;
}

int get_confidence_level(int start, int end, const char *data, const char* sync) {
#define BIT_MODE 0
#if BIT_MODE
    int confidence_level = 0;
    for (int i = start, j = 0; i < end; i++, j++) {
        char c = data[i] ^ sync[j];
        if (c == 0) {
            confidence_level++;
        }
    }
    return confidence_level;
#else
    int confidence_level = 0;
    int number_of_matched_bits = 0;
    for (int i = 0, bit_num = start; bit_num < end; i++, bit_num++) {
        // Iterate over each bit within a byte
        if ((data[bit_num] ^ sync[i]) == 0) {
            number_of_matched_bits++;
            if (number_of_matched_bits == 8) {
                confidence_level++;
                number_of_matched_bits = 0;
            }
        }
        else {
            number_of_matched_bits = 0;
        }
    }
    return confidence_level;
#endif

}

int get_start_location_of_payload(const char *data, int data_size, const char *lisa_sync_field, int sync_size, int confidence_level, int corrupt_level) {
    (void)corrupt_level;
    int start_position_of_sync_field = -1;
    int start_bit_of_payload = -1;
    int actual_Confidence = (int)(ceil((double)(confidence_level * (sync_size/8))/100));
    int max_confidence = 0;
    for (int j = 0; j < data_size - sync_size; j++) {
        int level = get_confidence_level(j, j+SYNC_BITS, data, lisa_sync_field);
        if (max_confidence < level) {
            max_confidence = level;
        }
        if (max_confidence >= actual_Confidence)
        {
            start_position_of_sync_field = j;
            start_bit_of_payload = start_position_of_sync_field + SYNC_BITS;
            break;
        }
    }

    return start_bit_of_payload;
}

