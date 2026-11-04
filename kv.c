#include <kv.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/* Your implementation here! */

struct kv_entries {
	/* your struct fields here */
	unsigned long key;
	void *value;
	void *prev;

};

struct kv{
	struct kv_entries *entries;
	size_t size;
	size_t capacity;
};
int compare(int a, int b){
	if(a<b){
		return -1;
	}
	else if(a>b){
		return 1;
	}
	return 0;
}

//struct kv *store;

struct kv *kv_create(void){
	printf("WAAAAAAAAAAAAAAAATHTTHAAAAAAP\n");

	printf("root is empty\n");

	struct kv *store = malloc(sizeof(struct kv));

	if(store == NULL){
		return NULL;
	}

	store->entries = malloc(sizeof(struct kv_entries));
	if(store->entries == NULL){
		return NULL;
	}

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
		free(store->entries);
	}
	//store->key = NULL;
	store->size = 0;
	store->capacity = 0;
	
	//free(store->entries);
	free(store);

	return;

}


void *kv_get(struct kv *store, unsigned long key){
	if(!store || !store->entries){
		return NULL;
	}

	//void *value = bsearch(key, store->entries, store->size, sizeof(kv_entries), compare);
	if(!key){
		return NULL;
	}
	//return *value;
	return NULL;
}

int kv_put(struct kv *store, unsigned long key, void *value, void **prev){
	if(!store || !value){
		return 0;
	}
	
	
	//struct kv *kv_entry = *bsearch(&key, *store, )
	assert(store);
	assert(value);
	assert(prev);
	if(key == 0) return 0;
	return 0;
}