#include <kv.h>
#include <kv_test.h>

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

int
main(void)
{
	struct kv *kv = kv_create();

	assert(kv);

	/* Insert in order; no qsort required! */
	struct kv_test_action actions[] = {
		{ .type = PUT, .key = 1 },
		{ .type = PUT, .key = 2 },
		{ .type = PUT, .key = 3 },
		{ .type = PUT, .key = 4 },
	};

	kv_test_run(kv, "simple1", actions, sizeof(actions) / sizeof(struct kv_test_action), 0);

	kv_destroy(kv);

	return 0;
}
