#include <kv.h>
#include <kv_test.h>

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "03_simple2.test.h"

int main(void)
{
	struct kv *kv = kv_create();
	assert(kv);

	struct kv_test_action actions[INPUT_SIZE];
	for (size_t i = 0; i < INPUT_SIZE; i++) {
		actions[i].key = (unsigned long)keys[i];
		actions[i].val = NULL;
		if (strcmp(operations[i], "put") == 0) {
			actions[i].type = PUT;
			char *buf = malloc(16);
			if (buf) {
				snprintf(buf, 16, "%u", keys[i]);
			}
			actions[i].val = buf;
		} else if (strcmp(operations[i], "get") == 0) {
			actions[i].type = GET;
		}
	}

	kv_test_run(kv, "simple2", actions, INPUT_SIZE, 1);

	kv_destroy(kv);

	return 0;
}
