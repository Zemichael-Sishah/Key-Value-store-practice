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

	struct kv_test_action actions[] = {
		{ .type = PUT, .key = 1 },
		{ .type = PUTCOPY, .key = 1 },
		{ .type = PUT, .key = 2 },
		{ .type = PUT, .key = 4 },
		{ .type = PUT, .key = 3 },
		{ .type = PUT, .key = 8 },
		{ .type = GET, .key = 2 },
		{ .type = GET, .key = 4 },
		{ .type = GET, .key = 3 },
		{ .type = GET, .key = 8 },
		{ .type = PUT, .key = 7 },
		{ .type = PUT, .key = 9 },
		{ .type = PUTCOPY, .key = 8 },
		{ .type = PUT, .key = 6 },
		{ .type = PUT, .key = 5 },
		{ .type = PUT, .key = 10 },
		{ .type = GET, .key = 1 },
		{ .type = PUTFAIL, .key = 10 },
		{ .type = GETFAIL, .key = 1 },
		{ .type = GET, .key = 7 },
		{ .type = GET, .key = 9 },
		{ .type = GET, .key = 6 },
		{ .type = GET, .key = 5 },
		{ .type = GET, .key = 10 },
	};

	kv_test_run(kv, "operation", actions, sizeof(actions) / sizeof(struct kv_test_action), 0);

	kv_destroy(kv);

	return 0;
}
