#pragma once

#define INPUT_SIZE 8

// these two arrays are "aligned" with each other
// for instance, operations[0] corresponds to keys[0] 
// and so on...
char* operations[] = { "put", "put", "put", "put", "get", "get", "get", "get" } ;
unsigned int keys[] = { 4, 3, 2, 1, 1, 2, 3, 4 } ;
