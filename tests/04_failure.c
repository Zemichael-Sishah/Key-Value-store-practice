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
		{ .type = GETFAIL, .key = 4 },
		{ .type = PUTFAIL, .key = 4 },
	};

	kv_test_run(kv, "failure", actions, sizeof(actions) / sizeof(struct kv_test_action), 0);

	kv_destroy(kv);

	return 0;
}
