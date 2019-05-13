#ifndef LEPTJSON_H__
#define LEPTJSON_H__
/*lept_value.type == lept_type -> JSON type*/
typedef enum { LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT } lept_type;

typedef struct {
    lept_type type;
}lept_value; 

enum {
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,/*只有空白   1*/
    LEPT_PARSE_INVALID_VALUE,/*值不是那三种字面值(null, false, true)   2*/
    LEPT_PARSE_ROOT_NOT_SINGULAR/*在一个值之后还有其他字符   3*/
};/*解析后返回的状态*/

int lept_parse(lept_value* v, const char* json);/*解析*/

lept_type lept_get_type(const lept_value* v);/*获取树的节点的json类型*/

#endif /* LEPTJSON_H__ */
