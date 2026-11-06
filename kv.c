#include <kv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/* Your implementation here! */

struct kv_entries {
	/* your struct fields here */
	unsigned long key;
	void *value;
	//void *prev;

};

struct kv{
	struct kv_entries *entries;
	size_t size;
	size_t capacity;
};


//struct kv *store;

struct kv *kv_create(void){
	printf("WAAAAAAAAAAAAAAAATHTTHAAAAAAP\n");

	printf("root is empty\n");

	struct kv *store = malloc(sizeof(struct kv));

	assert(store);

	store->entries = malloc(8 * sizeof(struct kv_entries));
	assert(store->entries);

	store->size = 0;
	store->capacity = 8;

	return store;
};


void kv_destroy(struct kv *store){
	printf("BYEEEE\n");
	if(store == NULL){
		return;
	}

	size_t SIZE = store->size;
	for(size_t i = 0; i < SIZE; i++){
		free(store->entries[i].value);
	}
	//store->key = NULL;
	store->size = 0;
	store->capacity = 0;
	
	free(store->entries);
	free(store);

	return;

}

int compare( const void *a, const void *b){
	struct kv_entries *kv1 = (struct kv_entries *)a;
	struct kv_entries *kv2 = (struct kv_entries *)b;

	if(kv1->key > kv2->key) return 1;
	else if (kv1->key < kv2->key) return -1;
	return 0;
}

void *kv_get(struct kv *store, unsigned long key){
	if(!store || !store->entries){
		return NULL;
	}

	struct kv_entries *kv_pair = bsearch(&key, store->entries, store->size, sizeof(struct kv_entries), compare);
	if(kv_pair == NULL){
		printf("\nkv_pair is null\n");
		return NULL;
	};

	printf("\nkv_pair is not null\n");
	return kv_pair->value;
}

int kv_put(struct kv *store, unsigned long key, void *value, void **prev){
	assert(key);
	if(!store || !value || !key || !prev){
		return -2;
	}

	

	struct kv_entries *kv_pair = bsearch(&key, store->entries, store->size, sizeof(struct kv_entries), compare);
	
	//assert(kv_pair);
	if(kv_pair){
		*prev = strdup((char *)(&(kv_pair->value)));
		kv_pair->value = strdup((char *)value);
		if(prev == NULL){
			return -2;
		}
		return 0;
	}

	*prev = NULL;

	if(store->size >= (store->capacity)){
		store->entries = realloc(store->entries, (store->capacity + 8) * sizeof(struct kv_entries));
		if(store->entries == NULL){
			return -1;
		};
		store->capacity += 8;
	}
	
	struct kv_entries *new_entry = &(store->entries[store->size]);
	new_entry->key = key;
	new_entry->value = strdup( (char *) value); 

	(store->size)++;

	qsort(store->entries, store->size, sizeof(struct kv_entries), compare);
	return 0;
}