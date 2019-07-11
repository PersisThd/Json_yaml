#include "json.h"
#include "json_typedef.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


// 创建一个json对象
JSON* json_new(json_e type)
{
	JSON* json = (JSON*)malloc(sizeof(JSON));
	if (json == NULL)
	{
		printf("json_new分配内存失败！\n");
		return NULL;
	}

	memset(json, 0, sizeof(JSON));
	json->type = type;
	return json;
}

JSON* json_new_int(double val)
{
	JSON* json_int = json_new(JSON_INT);
	if (json_int == NULL)
	{
		printf("json_new_int内存分配失败！\n");
		return NULL;
	}
	//memset(json_int, 0, sizeof(JSON));
	json_int->type = JSON_INT;
	json_int->num = val;

	return json_int;
}

JSON* json_new_bool(BOOL val)
{
	JSON* json_bol = json_new(JSON_BOL);
	if (json_bol == NULL)
	{
		printf("json_new_bool内存分配失败！\n");
		return NULL;
	}
	//memset(json_bol, 0, sizeof(JSON));
	json_bol->type = JSON_BOL;
	json_bol->bol = val;
	return json_bol;
}

JSON* json_new_str(const char* str)
{
	assert(str != NULL);
	JSON* json_str = json_new(JSON_STR);
	if (json_str == NULL)
	{
		printf("json_new_str内存分配失败！\n");
		return NULL;
	}
	//memset(json_str, 0, sizeof(JSON));
	json_str->type = JSON_STR;
	json_str->str = strdup(str);
	return json_str;
}

JSON* json_add_member(JSON* json, const char* key, JSON* val)
{
	assert(json != NULL);
	assert(key != NULL);
	assert(val != NULL);

	int i = json->obj.count;

	json->obj.kvs = (keyvalue*)realloc(json->obj.kvs, (i + 1) * sizeof(keyvalue));

	if (json->obj.kvs == NULL)
	{
		printf("realloc分配内存失败！\n");
		return NULL;
	}

	json->obj.kvs[i].key = strdup(key);
	json->obj.kvs[i].val = val;

	json->obj.count++;

	return json;
}

JSON* json_add_index(JSON* json, U32 idx, JSON* val)
{
	assert(json != NULL);
	assert(val != NULL);
	assert(idx >= 0);

	if (json->type != JSON_ARR)
	{
		printf("非数组型JSON对象，无法添加索引！\n");
		return NULL;
	}

	int i = json->arr.count;

	if (i < idx)
	{
		printf("索引值越界！\n");
		return NULL;
	}

	json->arr.elems = (value * *)realloc(json->arr.elems, (i + 1) * sizeof(value));
	if (json->arr.elems == NULL)
	{
		printf("realloc内存分配失败！\n");
		return NULL;
	}

	json->arr.elems[idx] = val;

	json->arr.count++;

	return json;
}


JSON* json_get_member(const JSON* json, const char* key)
{
	U32 i;
	assert(json);
	if (json->type != JSON_OBJ)
		return NULL;
	assert(json->obj.count == 0 || json->obj.kvs);
	for (i = 0; i < json->obj.count; ++i) {
		if (strcmp(json->obj.kvs[i].key, key) == 0)
			return json->obj.kvs[i].val;
	}
	return NULL;
}

JSON* json_get_index(const JSON* json, U32 idx)
{
	assert(json);
	if (json->type != JSON_ARR)
		return NULL;
	if (idx >= json->arr.count)
		return NULL;
	return json->arr.elems[idx];
}


/*void Init_Json(JSON* json)
{
	memset(json, 0, sizeof(JSON));
}*/

void print_json(JSON* json)
{
	//strcpy(json->obj.kvs->key, "ABC");
	//printf("%s\n", json->obj.kvs[0].key);
	//printf("%d\n", json->obj.kvs[0].val->num);
	//printf("%s\n", json->obj.kvs[1].key);
	//if(json->obj.kvs[1].val->bol == true)
		//printf("true\n");
	//printf("%s\n", json->obj.kvs[2].key);
	//printf("%s\n", json->obj.kvs[2].val->str);
	//printf("%s\n", json->obj.kvs[3].key);
	//printf("%s\n", json->obj.kvs[3].val->arr.elems[0]->str);
	//printf("%s\n", json->obj.kvs[0].val->arr.elems[0]->obj.kvs[0].key);
	//printf("%s\n", json->obj.kvs[0].val->arr.elems[0]->obj.kvs[0].val->str);
	switch (json->type)
	{
	case JSON_INT:
		printf("%f\n", json->num);
		break;
	case JSON_STR:
		printf("%s\n", json->str);
		break;
	case JSON_BOL:
		if (json->bol == true)
			printf("true\n");
		else
			printf("false\n");

		break;
	default:
		break;
	}
}

/*int json_get_int(const JSON *json, int def);
{
	assert(json);
	if(json->type != JSON_INT)
		return NULL;
	if()
}*/
/*
BOOL json_get_bool(const JSON *json)
{
	assert(json);
	if(json->type != JSON_BOL)
		return NULL;

	return json->bol;
}*/



void create_json(JSON* json)
{
	//JSON *json = json_new(JSON_OBJ);
	JSON* basic = json_new(JSON_OBJ);
	JSON* advance = json_new(JSON_OBJ);

	json_add_member(basic, "enable", json_new_bool(true));
	json_add_member(basic, "ip", json_new_str("200.200.3.61"));
	json_add_member(basic, "port", json_new_int(389));
	json_add_member(basic, "timeout", json_new_int(10));
	json_add_member(basic, "basedn", json_new_str("aaa"));
	json_add_member(basic, "fd", json_new_int(-1));
	json_add_member(basic, "maxcnt", json_new_int(100000000000001));
	JSON* str_arr = json_new(JSON_ARR);
	json_add_member(basic, "dns", str_arr);
	json_add_index(str_arr, 0, json_new_str("200.200.0.1"));
	json_add_index(str_arr, 1, json_new_str("200.0.0.245"));


	JSON* dns_arr = json_new(JSON_ARR);
	JSON* dns_0 = json_new(JSON_OBJ);
	JSON* dns_1 = json_new(JSON_OBJ);
	json_add_member(dns_0, "name", json_new_str("huanan"));
	json_add_member(dns_0, "ip", json_new_str("200.200.0.1"));
	json_add_member(dns_1, "name", json_new_str("huabei"));
	json_add_member(dns_1, "ip", json_new_str("200.0.0.254"));
	json_add_index(dns_arr, 0, dns_0);
	json_add_index(dns_arr, 1, dns_1);
	json_add_member(advance, "dns", dns_arr);
	JSON* por_arr = json_new(JSON_ARR);
	json_add_index(por_arr, 0, json_new_int(130));
	json_add_index(por_arr, 1, json_new_int(131));
	json_add_index(por_arr, 2, json_new_int(132));
	json_add_member(advance, "portpool", por_arr);
	json_add_member(advance, "url", json_new_str("http://200.200.0.4/main"));
	json_add_member(advance, "path", json_new_str("/etc/sanfors"));
	json_add_member(advance, "value", json_new_int(3.14));

	json_add_member(json, "basic", basic);
	json_add_member(json, "advance", advance);

}

void test_json_basic(JSON* json)
{
	printf("***********basi test************\n");
	JSON* basic_test = json_get_member(json, "basic");

	JSON* basic_test_enable = json_get_member(basic_test, "enable");
	printf("enable: ");
	print_json(basic_test_enable);
	printf("\n");

	JSON* basic_test_ip = json_get_member(basic_test, "ip");
	printf("ip: ");
	print_json(basic_test_ip);
	printf("\n");

	JSON* basic_test_timeout = json_get_member(basic_test, "timeout");
	printf("timeout: ");
	print_json(basic_test_timeout);
	printf("\n");

	JSON* basic_fd = json_get_member(basic_test, "fd");
	printf("fd: ");
	print_json(basic_fd);
	printf("\n");

	JSON* basic_test_dns = json_get_member(basic_test, "dns");
	printf("dns:\n");
	JSON* basic_test_dns_0 = json_get_index(basic_test_dns, 0);
	print_json(basic_test_dns_0);
	JSON* basic_test_dns_1 = json_get_index(basic_test_dns, 1);
	print_json(basic_test_dns_1);
	printf("\n");


}

void test_json_advance(JSON* json)
{
	printf("**************advance test**************\n");

	JSON* advance_test = json_get_member(json, "advance");
	JSON* advance_test_dns = json_get_member(advance_test, "dns");
	printf("dns: \n");
	JSON* advance_test_dns0 = json_get_index(advance_test_dns, 0);
	JSON* advance_test_dns0_name = json_get_member(advance_test_dns0, "name");
	print_json(advance_test_dns0_name);
	JSON* advance_test_dns0_ip = json_get_member(advance_test_dns0, "ip");
	print_json(advance_test_dns0_ip);

	JSON* advance_test_dns1 = json_get_index(advance_test_dns, 1);
	JSON* advance_test_dns1_name = json_get_member(advance_test_dns1, "name");
	print_json(advance_test_dns1_name);
	JSON* advance_test_dns1_ip = json_get_member(advance_test_dns1, "ip");
	print_json(advance_test_dns1_ip);
}

void json_destroy(JSON** json)
{
	assert(json != NULL);
	json_clear(*json);
	free(*json);
	*json = NULL;
}

void json_clear(JSON* json)
{
	assert(json != NULL);
	switch (json->type)
	{
	case JSON_ARR:
		json_free_array(&json->arr);
		break;
	case JSON_STR:
		json_free_str(&json->str);
		break;
	case JSON_OBJ:
		json_free_object(&json->obj);
		break;
	default:
		break;
	}
}

void json_free_array(array* arr)
{
	assert(arr != NULL);
	for (int i = 0; i < arr->count; i++)
	{
		json_destroy(&arr->elems[i]);
	}
}

void json_free_str(char** str)
{
	assert(str != NULL);
	char* tmp = *str;
	if (tmp == NULL)
		return;
	printf("free memory: %s\n", *str);
	free(*str);
	*str = NULL;
}

void json_free_object(object* obj)
{
	assert(obj != NULL);
	for (int i = 0; i < obj->count; i++)
	{
		json_free_str(&obj->kvs[i].key);
		json_destroy(&obj->kvs[i].val);
	}
}

void json_print_val(JSON* json, FILE* fp)
{
	assert(json != NULL);
	int deep = 0;
	json_print_val_deep(json, deep, fp);

}

void json_print_val_deep(JSON* json, int deep, FILE* fp)
{
	assert(json != NULL);
	assert(deep >= 0);
	switch (json->type)
	{
	case JSON_INT:
		json_print_num(json->num, fp);
		break;
	case JSON_BOL:
		json_print_bool(json->bol, fp);
		break;
	case JSON_STR:
		json_print_str(json->str, fp);
		break;
	case JSON_ARR:
		json_print_arr(&json->arr, &deep, fp);
		break;
	case JSON_OBJ:
		json_print_obj(&json->obj, &deep, fp);
		break;
	default:
		break;
	}
	return;
}

void json_print_num(double num, FILE* fp)
{
	fprintf(fp, "%lf", num);
}

void json_print_bool(BOOL b, FILE* fp)
{
	if (b == true)
	{
		fprintf(fp, "true");
	}
	else
	{
		fprintf(fp, "false");
	}
}

void json_print_str(const char* str, FILE* fp)
{
	assert(str != NULL);
	fprintf(fp, "%s", str);
}

void json_print_arr(const array* arr, int* deep, FILE* fp)
{
	assert(arr != NULL);
	assert(deep != NULL);
	fprintf(fp, "\n");
	(*deep)++;
	for (int i = 0; i < arr->count; i++)
	{
		format_print_tbl(*deep - 1, fp);

		if (arr->elems[i]->type == JSON_OBJ)
		{
			if (i != arr->count - 1)
			{
				fprintf(fp, "- ");
				json_print_arr_obj(&arr->elems[i]->obj, deep, fp);
				//json_print_val_deep(arr->elems[i], *deep, NO_COMMA);
				fprintf(fp, "\n");
			}
			else
			{
				fprintf(fp, "- ");
				json_print_arr_obj(&arr->elems[i]->obj, deep, fp);
				//json_print_val_deep(arr->elems[i], *deep, NO_COMMA);
			}
		}
		else
		{
			if (i != arr->count - 1)
			{
				fprintf(fp, "- ");
				json_print_val_deep(arr->elems[i], *deep, fp);
				fprintf(fp, "\n");
			}
			else
			{
				fprintf(fp, "- ");
				json_print_val_deep(arr->elems[i], *deep, fp);
			}
		}
	}
	format_print_tbl(*deep - 2, fp);
	//printf("]");
}

void json_print_arr_obj(const object* obj, int* deep, FILE* fp)
{
	assert(obj != NULL);
	assert(deep != NULL);

	(*deep)++;

	for (int i = 0; i < obj->count; i++)
	{
		if (*deep > 1 && i > 0)
		{
			format_print_tbl(*deep - 1, fp);
		}
		fprintf(fp, "%s: ", obj->kvs[i].key);
		if (i == obj->count - 1)
		{
			json_print_val_deep(obj->kvs[i].val, *deep, fp);
			//printf("\n");
		}
		else
		{
			json_print_val_deep(obj->kvs[i].val, *deep, fp);
			fprintf(fp, "\n");
		}
	}
	format_print_tbl(*deep - 2, fp);
	(*deep)--;

}

void json_print_obj(const object* obj, int* deep, FILE* fp)
{
	assert(obj != NULL);
	assert(deep != NULL);
	if (*deep > 0)
	{
		fprintf(fp, "\n");
	}
	(*deep)++;

	for (int i = 0; i < obj->count; i++)
	{
		if (*deep > 1)
		{
			format_print_tbl(*deep - 1, fp);
		}
		fprintf(fp, "%s: ", obj->kvs[i].key);
		if (i == obj->count - 1)
		{
			json_print_val_deep(obj->kvs[i].val, *deep, fp);
			//printf("\n");
		}
		else
		{
			json_print_val_deep(obj->kvs[i].val, *deep, fp);
			fprintf(fp, "\n");
		}
	}
	format_print_tbl(*deep - 2, fp);
}

void format_print_tbl(int deep, FILE* fp)
{
	for (int i = 0; i < deep; i++)
	{
		fprintf(fp, "  ");
	}
}


/*void format_control(json_split flag)
{
	if(flag == WITH_COMMA)
	{
		printf(",\n");
	}
	else
	{
		//printf("\n");
	}
}*/

