#pragma once

#include <kv.h>

#include <stdlib.h>

struct kv_test_action {
	enum { GET, GETFAIL, PUT, PUTCOPY, PUTFAIL } type;
	unsigned long key;
	char* val;
};

void kv_test_run(struct kv *kv, char *name, 
				 struct kv_test_action *actions, 
				 size_t num_actions, int print_ops);
