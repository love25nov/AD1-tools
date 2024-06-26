#ifndef LIBAD1_DEF_H
#define LIBAD1_DEF_H

#include <stdint.h>

#define AD1_LOGICAL_MARGIN   512

#define AD1_FOLDER_SIGNATURE 0x05

typedef struct ad1_metadata {
    unsigned long next_metadata_addr;
    unsigned int category;
    unsigned int key;
    unsigned int data_length;

    char* data;

    struct ad1_metadata* next_metadata;

} ad1_metadata;

typedef struct ad1_item_header {
    unsigned long next_item_addr;
    unsigned long first_child_addr;

    unsigned long first_metadata_addr;

    unsigned long zlib_metadata_addr;

    unsigned long decompressed_size;
    unsigned int item_type;

    unsigned int item_name_length;

    unsigned long parent_folder;

    char* item_name;

    struct ad1_item_header* next_item;
    struct ad1_item_header* first_child;
    struct ad1_item_header* parent;

    struct ad1_metadata* first_metadata;

} ad1_item_header;

typedef struct ad1_segment_header {

    char signature[16];
    unsigned int segment_index;
    unsigned int segment_number;
    unsigned int fragments_size;
    unsigned int header_size;
} ad1_segment_header;

typedef struct ad1_logical_header {

    char signature[16];
    unsigned int image_version;

    unsigned int some_data;

    unsigned int zlib_chunk_size;

    unsigned long logical_metadata_addr;
    unsigned long first_item_addr;

    unsigned int data_source_name_length;

    char ad_signature[4];
    unsigned long data_source_name_addr;

    unsigned long attrguid_footer_addr;
    unsigned long locsguid_footer_addr;

    char* data_source_name;

    struct ad1_item_header* first_item;
    struct ad1_metadata* logical_metadata;

} ad1_logical_header;

enum category { HASH_INFO = 0x01, ITEM_TYPE = 0x02, ITEM_SIZE = 0x03, WINDOWS_FLAGS = 0x04, TIMESTAMP = 0x05 };

enum ad_hash_key { MD5_HASH = 0x5001, SHA1_HASH = 0x5002, DATA_SOURCE_NAME = 0x10002 };

enum ad_item_type_key { UNKNOWN = 0x01, CHAR_ITEM_TYPE = 0x02 };

enum ad_item_type_value {
    REFULAR_FILE = 0x31,
    PLACEHOLDER = 0x32,
    REGULAR_FOLDER = 0x33,
    FILESYSTEM_METADATA = 0x34,
    FILESLACK = 0x36,
    SYMLINK = 0x39
};

enum ad_item_size_key { FILE_SIZE = 0x03, MAX_SIZE = 0x04, UNKNOWN_1 = 0x2002, UNKNOWN_2 = 0x2003 };

enum ad_windows_flag_key {
    ENCRYPTED = 0x0D,
    COMPRESSED = 0x0E,
    UNKNOWN_FLAG_1 = 0x1E,
    HIDDEN = 0x1002,
    UNKNOWN_FLAG_2 = 0x1003,
    READ_ONLY = 0x1004,
    READY_TO_ARCHIVE = 0x1005
};

enum ad_timestamp_key { ACCESS = 0x07, MODIFIED = 0x08, CHANGE = 0x09 };

#endif
