#include <stdio.h>
#include "json_typedef.h"

JSON* json_get_member(const JSON* json, const char* key);
JSON* json_get_index(const JSON* json, U32 idx);
JSON* json_new(json_e type);
void Init_Json(JSON* json);
void print_json(JSON* json);
JSON* json_add_member(JSON* json, const char* key, JSON* val);
JSON* json_add_index(JSON* json, U32 idx, JSON* val);
JSON* json_new_int(double val);
JSON* json_new_bool(BOOL val);
JSON* json_new_str(const char* str);
void json_free_array(array* arr);
void json_free_object(object* obj);
void json_free_str(char** str);
void json_clear(JSON* json);
void json_destroy(JSON** json);
void json_print_val(JSON* json, FILE* fp);
void json_print_val_deep(JSON* json, int deep, FILE* fp);
void json_print_num(double num, FILE* fp);
void json_print_bool(BOOL b, FILE* fp);
void json_print_arr(const array* arr, int* deep, FILE* fp);
void json_print_str(const char* str, FILE* fp);
void json_print_obj(const object* obj, int* deep, FILE* fp);
void format_print_tbl(int deep, FILE* fp);
void json_print_arr_obj(const object* obj, int* deep, FILE* fp);
