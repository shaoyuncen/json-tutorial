#include "leptjson.h"
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */

#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)

typedef struct {
    const char* json;
}lept_context;/*json str*/

static void lept_parse_whitespace(lept_context* c) {/*去掉前面的空格及制表换行回车符*/
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

static int lept_parse_null(lept_context* c, lept_value* v) {/*解析null，若c->json为null，返回ok，并且c->json指向null后，否则返回invalid*/
    EXPECT(c, 'n');/*/确定c的第一个字符等于n，并且c指向地址++/*/
    /*printf("%s",c->json[2]); 存在bug，如c->json == nul时，c->json[*]可能访问未知区域*/
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;/*/c->json为null，指向null后的位置/*/

    v->type = LEPT_NULL;
    return LEPT_PARSE_OK;
}
static int lept_parse_false(lept_context* c, lept_value* v){
    EXPECT(c, 'f');
    if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's'|| c->json[3] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 4;/*/c->json为null，指向null后的位置/*/
    v->type = LEPT_FALSE;
    return LEPT_PARSE_OK;
}
static int lept_parse_true(lept_context* c, lept_value* v){
    EXPECT(c, 't');
    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;/*/c->json为null，指向null后的位置/*/
    v->type = LEPT_TRUE;
    return LEPT_PARSE_OK;
}
static int lept_parse_value(lept_context* c, lept_value* v) {/*/判断json str状态/*/
    switch (*c->json) {
        case 'n':  return lept_parse_null(c, v);
        case 'f':  return lept_parse_false(c, v);
        case 't':  return lept_parse_true(c, v);
        case '\0': return LEPT_PARSE_EXPECT_VALUE;/*/空的json str/*/
        default:   return LEPT_PARSE_INVALID_VALUE;/*/不合法/*/
    }
}

int lept_parse(lept_value* v, const char* json) {/*/返回json str的状态并把v->type置空/*/
    lept_context c;
    assert(v != NULL);/*/确定v不为空/*/
    c.json = json;
    v->type = LEPT_NULL;
    lept_parse_whitespace(&c);
    int ret;
    if ((ret = lept_parse_value(&c, v)) == LEPT_PARSE_OK) {
        lept_parse_whitespace(&c);
        if (*c.json != '\0')
        {
            v->type = LEPT_NULL;/*若不止一个值则置空，与answer不同*
            ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
        }
    }
    return ret;
}

lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}
