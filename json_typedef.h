#pragma once
#define true 1
#define false 0
typedef unsigned int BOOL;
typedef unsigned int U32;

typedef enum json_e {
	JSON_NONE,
	JSON_BOL,
	JSON_STR,
	JSON_ARR,
	JSON_OBJ,
	JSON_INT,
}json_e;

typedef struct value JSON;
typedef struct array array;
typedef struct object object;
typedef struct value value;
typedef struct keyvalue keyvalue;

struct array {
	JSON** elems;
	U32 count;
};

struct keyvalue {
	char* key;
	JSON* val;
};


struct object {
	keyvalue* kvs;
	U32 count;
};

struct value {
	json_e type;
	union {
		double num;
		BOOL bol;
		char* str;
		array arr;
		object obj;
	};
};

void create_json(JSON* json);
void test_json_basic(JSON* json);
void test_json_advance(JSON* json);

