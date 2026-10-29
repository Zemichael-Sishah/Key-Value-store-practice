#include <kv.h>
#include <kv_test.h>

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define KV_ACTIONS_AMNT (1024 * 16) /* 16K actions */

/* The actions we're going to generate, and the constituent keys and values. */
struct kv_test_action actions[KV_ACTIONS_AMNT];
unsigned long keys[KV_ACTIONS_AMNT / 2];
char *vals[KV_ACTIONS_AMNT / 2];

int
main(void)
{
	int i;
	struct kv *kv = kv_create();
	assert(kv);

	/*
	 * This is a "fuzz" test. This adds a random factor to the
	 * tests, thus running more can uncover bugs that might only
	 * be reached with specific sequences of inputs. We are not
	 * doing as good a job with this as we might otherwise do as
	 * we're just randomizing between GET and PUT operations,
	 * rather than the full range of possible operations.
	 */
	srand(time(NULL));
	for (i = 0; i < KV_ACTIONS_AMNT / 2;) {
		/*
		 * Generate a random key. Unfortunately, `rand` is an
		 * expensive call, so this might take some time to
		 * execute.
		 */
		unsigned long r = rand();
		char value[128];
		int j;
		int try_again = 0;

		keys[i] = r;
		/*
		 * We don't want to re-use keys in the test, thus if
		 * we generate a random key that is already used by a
		 * previous PUT, lets roll the dice again.
		 */
		for (j = 0; j < i; j++) {
			if (keys[j] == keys[i]) try_again = 1;
		}
		if (try_again) continue;

		/* Generate a random value. */
		snprintf(value, 128, "%d", rand());
		vals[i] = strdup(value);
		i++;
	}
	/* Construct the actions. */
	for (i = 0; i < KV_ACTIONS_AMNT; i += 2) {
		unsigned int k;

		/* Odd actions are PUT operations  */
		actions[i] = (struct kv_test_action) {
			.type = PUT,
			.key  = keys[i/2],
			.val  = vals[i/2]
		};

		/* Even actions are GET operations */
		k = rand() % ((i / 2) + 1);
		actions[i + 1] = (struct kv_test_action) {
			.type = GET,
			.key  = keys[k],
			.val  = vals[k]
		};
	}

	kv_test_run(kv, "random", actions, sizeof(actions) / sizeof(struct kv_test_action), 0);

	kv_destroy(kv);

	return 0;
}
