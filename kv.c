#include <kv.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/* Your implementation here! */

struct kv {
	/* your struct fields here */
	unsigned long key;
	void *value;
	void **prev;
};

struct kv *store;

struct kv *kv_create(void){
	printf("WAAAAAAAAAAAAAAAATHTTHAAAAAAP\n");

	printf("root is empty\n");
	struct kv *store = malloc(sizeof(struct kv));
	if(store == NULL){
		return NULL;
	}
	store->value = NULL;
	store->prev = NULL;

	return store;
};


void kv_destroy(struct kv *store){
	printf("BYEEEE\n");
	if(store == NULL){
		return;
	}
	free(store->value);
	free(store->prev);
	free(store);

	return;

}


void *kv_get(struct kv *store, unsigned long key){
	if(!store){
		return;
	}

	assert(store);
	if(key == 0)return NULL;
	return NULL;
}

int kv_put(struct kv *store, unsigned long key, void *value, void **prev){
	if(!store){
		return 0;
	}
	if(!value || !prev){
		return 0;
	}
	struct kv *kv_entry = *bsearch(&key, *store, )
	assert(store);
	assert(value);
	assert(prev);
	if(key == 0) return 0;
	return 0;
}