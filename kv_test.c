#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <kv_test.h>
#include <kv.h>

/*
 * The actions we're going to test are passed in. When testing your
 * code, you often want to make your tests as simple to create and add
 * to as possible. Codifying the sequence of actions you want your
 * tests to take in a data-structure makes it much easier to
 * understand the sequence, easier to change the testing code, and
 * easier to update your tests.
 */

void kv_test_run(struct kv *kv, char *name, struct kv_test_action *actions, size_t num_actions, int print_ops)
{
	size_t i;

	printf("%s tests starting...\n", name);
	for (i = 0; i < num_actions; i++) {
		struct kv_test_action *a = &actions[i]; /* we're using this a lot, so lets use a variable */
		char value[128];
		void *prev;
		int allocated = 0;

		if (a->val == NULL) {
			/* construct a string that is a replica of the key */
			snprintf(value, 128, "%ld", a->key);
			/* Lets make sure we have a heap-allocated value */
			a->val = strdup(value);
			allocated = 1;
		}

		/* Do the appropriate action */
		switch (a->type) {
		case GET: {
			char *ret;

			if (print_ops) printf("GET %ld, expecting %s", a->key, a->val);
			ret = kv_get(kv, a->key);
			if (print_ops) printf(", returned %s\n", ret);
			assert(ret && strcmp(ret, a->val) == 0);
			if (allocated) free(a->val);
			break;
		}
		case GETFAIL: {
			char *ret;

			if (print_ops) printf("GETFAIL -1, expecting NULL");
			ret = kv_get(kv, -1);
			if (print_ops) printf(", returned %s\n", ret);
			assert(!ret);
			if (allocated) free(a->val);
			break;
		}
		case PUT:{
			if (print_ops) printf("PUT %ld, %s\n", a->key, a->val);
			assert(kv_put(kv, a->key, a->val, &prev) == 0 && prev == NULL);
			break;
		}
		case PUTCOPY: {
			if (print_ops) printf("PUTCOPY %ld, %s\n", a->key, a->val);
			assert(kv_put(kv, a->key, a->val, &prev) == 0 && prev != NULL && strcmp(prev, a->val) == 0);
			free(prev);
			break;
		}
		case PUTFAIL:{
			if (print_ops) printf("PUTFAIL\n");
			assert(kv_put(kv, a->key, a->val, NULL) == -2);
			assert(kv_put(kv, a->key, NULL, &prev) == -2);
			if (allocated) free(a->val);
			break;
		}
		default: {
			assert(0);
		}}
	}

	printf("%s tests SUCCESSFUL\n", name);

	return;
}
