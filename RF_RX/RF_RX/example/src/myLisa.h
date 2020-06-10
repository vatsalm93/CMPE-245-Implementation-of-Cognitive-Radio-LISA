#ifndef MYLISA_H
#define MYLISA_H

#define DATA_BITS					2048
#define SYNC_BITS                   256
#define BITS						8
#define BUFFER_BYTES 				DATA_BITS/BITS
#define SYNC_FIELD_BYTES            SYNC_BITS/BITS
#define WRITE_DATA_IN_TEXT_FILE		0
#define TEST_DATA_FILE				"myTestData.txt"

static const char payload_data[] = "CMPE245_AAKASH_5040";

static const char source_tag = 'X';
static const char destination_tag = 'Y';
static const char end_of_payload = '#';
void print_array(const char *array, int start, int end, const char* format);

void corrupt_sync_field(int corrupt_percentage, char *sync_field, int sync_field_size);

void convert_bytes_to_bits(const char *bytes, int size, char *bits);

char convert_8_bits_to_char(const char *bits);

void write_text_file(const char *filename, const char* file_mode, const char *data_to_write, int number_of_bytes_to_write);

void read_text_file(const char *filename, char *data_to_read);

void generate_junk_data(int junk_size, char *junk_data);

int get_corruption_level(int start, int end, const char *data, const char *sync);

int get_confidence_level(int start, int end, const char *data, const char* sync);

int get_start_location_of_payload(const char *data, int data_size, const char *lisa_sync_field, int sync_size, int confidence_level, int corrupt_level);

#endif // MYLISA_H
