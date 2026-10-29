#pragma once

/***
 * A key-value store implementation with a simple API based on `get`
 * and `put`, along with means of allocation and deallocation. Stores
 * items of a generic type (`void *`).
 *
 * This implementation uses `qsort` to ensure that the keys are sorted
 * when new data is `put` into the store, and `bsearch` to do a binary
 * search on the data during a `get`. To support a dynamic number of
 * key-value entries, this implementation uses `realloc` to "grow" the
 * store. Specifically, if the allocated memory for an array of
 * key-value entries is to small to support another `put`, `realloc`
 * is used to effectively grow the key-value store. I suggest that you
 * grow the array by a factor of two.
 *
 * This function includes the public API of the implementation. The
 * *function declarations can not be modified*.
 *
 * Note that when an *assumption* is made, it means that this
 * implementation can assume that the client always adheres to the
 * assumption. Thus, they don't need to be checked, or (more
 * reasonably) can be `assert`ions.
 */

/**
 * The core, externally visible structure for the `kv`. This should
 * only be accessed/operated on using the functions below.
 */
struct kv;

/**
 * `kv_create` will dynamically allocate a new key-value store, and
 * return it.
 *
 * - `@return` - the newly allocated store, or `NULL` on error (e.g.
 *     `malloc` returns `NULL`).
 */
struct kv *kv_create(void);

/**
 * `kv_destroy` takes a store and deallocates all key/value pairs, then
 * deallocates the store. Note that there is no `kv_delete` function so
 * this is the only way to deallocate
 *
 * - `@store` - The store to destroy. Assume that `store != NULL`.
 */
void kv_destroy(struct kv *store);

/**
 * `kv_get` retrieves a value associated with the `key`. Calls `bsearch`
 * to search for the key.
 *
 * - `@store` - store to add the key/value into, we assume that `store
 *     != NULL`
 * - `@key` - The `key` who's value is returned (should it exist). The
 *     store enables the caller to borrow the value, but the caller must
 *     not maintain references to it after the `kv_destroy` is called.
 * - `@return` - return `NULL` if the `key` doesn't exist in the store.
 *     Return the value otherwise. Enables the caller to *borrow* the
 *     value.
 */
void *kv_get(struct kv *store, unsigned long key);

/**
 * `kv_put` inserts a key/value pair into the store. Calls `qsort` if a
 * new key-value entry is added, and sorts by key. Sorting here ensures
 * that `kv_get` is O(log n).
 *
 * - If the key already exists in the store, its value is updated to
 *     the `value` argument, and the previous value is returned into
 *     the pointer referenced by `prev`.
 * - If the key does not exist, the `key` and `value` are added to the
 *     store.
 *
 * Arguments and returns:
 *
 * - `@store` - store to add the key/value into, we assume that `store
 *     != NULL`
 * - `@key` - the key to associate with the `value`.
 * - `@value` - the value to store with the `key`. Pass ownership to
 *     the store. If `value` is `NULL` return an error.
 * - `@prev` - the previous value is returned in `prev` if the key
 *     being `put` already exists, and ownership is passed to the
 *     caller
 * - `@return` - returns `0` in absence of error. Otherwise, errors:
 *
 *     - `-1` - If a memory allocation fails.
 *     - `-2` - If `value` or `prev` are `NULL`.
 */
int kv_put(struct kv *store, unsigned long key, void *value, void **prev);
