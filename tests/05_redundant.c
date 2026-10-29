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

	/* Insert out of order */
	struct kv_test_action actions[] = {
		{ .type = PUT, .key = 4 },
		{ .type = PUT, .key = 3 },
		{ .type = PUT, .key = 2 },
		{ .type = PUT, .key = 1 },
		{ .type = PUTCOPY, .key = 3 },
		{ .type = GET, .key = 1 },
		{ .type = GET, .key = 2 },
		{ .type = PUTCOPY, .key = 4 },
		{ .type = GET, .key = 3 },
		{ .type = GET, .key = 4 },
	};

	kv_test_run(kv, "redundant", actions, sizeof(actions) / sizeof(struct kv_test_action), 0);

	kv_destroy(kv);

	return 0;
}
