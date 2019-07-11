#include <stdio.h>
#include <string.h>
#include "json.h"
#include "json_typedef.h"

int main()
{
	JSON* json = json_new(JSON_OBJ);

	create_json(json);
	//test_json_basic(json);
	//test_json_advance(json);

	FILE* fp = fopen("json.yml", "w");
	if (fp == NULL)
	{
		perror("fopen: ");
	}

	json_print_val(json, fp);

	//printf("\n\n*******ÊÍ·ÅÄÚ´æ**********\n");
	//json_destroy(&json);

	return 0;
}
