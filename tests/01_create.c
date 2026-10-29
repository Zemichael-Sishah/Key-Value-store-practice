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

	kv_destroy(kv);

	printf("Create tests SUCCESSFUL\n");

	return 0;
}
