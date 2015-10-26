#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

/**
 * This is the API description for your hashtable data-structure
 * that you'll need to implement in C.
 * The table maps strings to arbitrary data, described as a void* in C.
 * An equivalent type in Java would be declared as Hashtable<String, Object>.
 *
 * You will have to implement all the hash_* functions declared
 * in this header file. You are allowed to change/update the
 * struct definitions for hash_table and hash_elem if you need to,
 * but you should not change the API of the function declarations.
 */

// A user provided function that is able to correctly dispose stored
// hash table values
typedef void (* hash_data_free_fn)(void *);

struct hash_elem; // Forward declaration

/**
 * The hash table structure itself.
 */
struct hash_table {
    // number of buckets in the table.
    int num_buckets;

    // pointer to the buckets.
    struct hash_elem** buckets;

    // function that knows how to free inserted data resources
    hash_data_free_fn data_free;
};

/*
 * Structure of a hash table element.
 */
struct hash_elem {
    // Key of the element
    const char* key;
    // Data entry
    void* data;

    // Pointer that points to next hash_elem in case of collisions
    struct hash_elem* next;
};

/**
 * Creates a new hash table.
 * @param  t The pointer is either set to the new allocated hash table or NULL in case of an error.
 * @param  f User provided function that frees deleted hash table entries. Can be NULL.
 */
void  hash_create(struct hash_table **t, hash_data_free_fn f);

/**
 * Releases the entire hash table, including all its entries properly.
 * @param  t The hash table to dispose.
 */
void  hash_release(struct hash_table *t);

/**
 * Inserts a key/value pair into the hash-table.
 * @param  t    Insert into this hash-table.
 * @param  key  Corresponding key to insert, if the key already exists, overwrite and free old data.
 * @param  data Data for corresponding key.
 */
void  hash_insert(struct hash_table *t, const char* key, void *data);

/**
 * Finds an element in the hash-table.
 * @param t   Hash-table to find element in.
 * @param key Key of the corresponding element.
 * @returns Corresponding data entry or NULL in case the key does not exist.
 */
void* hash_find(struct hash_table *t, const char* key);

/**
 * Deletes an element in the hash-table. This function should also call the
 * registered function to free the data.
 * @param  t   Hash table to delete from.
 * @param  key Key to delete. Does nothing if key does not exist.
 */
void  hash_delete(struct hash_table *t, const char* key);

#endif
