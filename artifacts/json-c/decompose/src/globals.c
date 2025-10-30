static int _syslog = 0
/*** DEPENDENCIES:
***/


static int _debug = 0
/*** DEPENDENCIES:
***/


extern const char *json_hex_chars
/*** DEPENDENCIES:
***/


const char *json_number_chars = "0123456789.+-eE"
/*** DEPENDENCIES:
***/


static char *tls_serialization_float_format = 0
/*** DEPENDENCIES:
***/


static char *global_serialization_float_format = 0
/*** DEPENDENCIES:
***/


static const void *kObjectEndIterValue = 0
/*** DEPENDENCIES:
***/


static const char json_null_str[] = "null"
/*** DEPENDENCIES:
***/


static const int json_null_str_len = (sizeof(json_null_str)) - 1
/*** DEPENDENCIES:
***/


static const char json_inf_str[] = "Infinity"
/*** DEPENDENCIES:
***/


static const char json_inf_str_invert[] = "iNFINITY"
/*** DEPENDENCIES:
***/


static const unsigned int json_inf_str_len = (sizeof(json_inf_str)) - 1
/*** DEPENDENCIES:
***/


static const char json_nan_str[] = "NaN"
/*** DEPENDENCIES:
***/


static const int json_nan_str_len = (sizeof(json_nan_str)) - 1
/*** DEPENDENCIES:
***/


static const char json_true_str[] = "true"
/*** DEPENDENCIES:
***/


static const int json_true_str_len = (sizeof(json_true_str)) - 1
/*** DEPENDENCIES:
***/


static const char json_false_str[] = "false"
/*** DEPENDENCIES:
***/


static const int json_false_str_len = (sizeof(json_false_str)) - 1
/*** DEPENDENCIES:
***/


static const char *json_tokener_errors[] = {"success", "continue", "nesting too deep", "unexpected end of data", "unexpected character", "null expected", "boolean expected", "number expected", "array value separator ',' expected", "quoted object property name expected", "object property name separator ':' expected", "object value separator ',' expected", "invalid string sequence", "expected comment", "invalid utf-8 string", "buffer size overflow", "out of memory"}
/*** DEPENDENCIES:
***/


static unsigned char utf8_replacement_char[3] = {0xEF, 0xBF, 0xBD}
/*** DEPENDENCIES:
***/


static char _last_err[256] = ""
/*** DEPENDENCIES:
***/


static const char *json_type_name[] = {"null", "boolean", "double", "int", "object", "array", "string"}
/*** DEPENDENCIES:
***/


static struct 
{
  int errno_value;
  const char *errno_str;
} errno_list[] = {{EPERM, &"undef_EPERM"[6]}, {ENOENT, &"undef_ENOENT"[6]}, {ESRCH, &"undef_ESRCH"[6]}, {EINTR, &"undef_EINTR"[6]}, {EIO, &"undef_EIO"[6]}, {ENXIO, &"undef_ENXIO"[6]}, {E2BIG, &"undef_E2BIG"[6]}, {EBADF, &"undef_EBADF"[6]}, {ECHILD, &"undef_ECHILD"[6]}, {EDEADLK, &"undef_EDEADLK"[6]}, {ENOMEM, &"undef_ENOMEM"[6]}, {EACCES, &"undef_EACCES"[6]}, {EFAULT, &"undef_EFAULT"[6]}, {EBUSY, &"undef_EBUSY"[6]}, {EEXIST, &"undef_EEXIST"[6]}, {EXDEV, &"undef_EXDEV"[6]}, {ENODEV, &"undef_ENODEV"[6]}, {ENOTDIR, &"undef_ENOTDIR"[6]}, {EISDIR, &"undef_EISDIR"[6]}, {EINVAL, &"undef_EINVAL"[6]}, {ENFILE, &"undef_ENFILE"[6]}, {EMFILE, &"undef_EMFILE"[6]}, {ENOTTY, &"undef_ENOTTY"[6]}, {EFBIG, &"undef_EFBIG"[6]}, {ENOSPC, &"undef_ENOSPC"[6]}, {ESPIPE, &"undef_ESPIPE"[6]}, {EROFS, &"undef_EROFS"[6]}, {EMLINK, &"undef_EMLINK"[6]}, {EPIPE, &"undef_EPIPE"[6]}, {EDOM, &"undef_EDOM"[6]}, {ERANGE, &"undef_ERANGE"[6]}, {EAGAIN, &"undef_EAGAIN"[6]}, {0, (char *) 0}}
/*** DEPENDENCIES:
***/


static int _json_c_strerror_enable = 0
/*** DEPENDENCIES:
***/


static char errno_buf[128] = "ERRNO="
/*** DEPENDENCIES:
***/


static struct 
{
  const char *arg;
  int flag;
} format_args[] = {{"plain", 0}, {"spaced", 1 << 0}, {"pretty", 1 << 1}, {"pretty_tab", 1 << 3}}
/*** DEPENDENCIES:
***/


static const char *json_str1 = "{    \"glossary\": {        \"title\": \"example glossary\",        \"GlossDiv\": {            \"number\": 16446744073709551615,            \"title\": \"S\",            \"null_obj\": null,             \"exist\": false,            \"quantity\":20,            \"univalent\":19.8,            \"GlossList\": {                \"GlossEntry\": {                    \"ID\": \"SGML\",                    \"SortAs\": \"SGML\",                    \"GlossTerm\": \"Standard Generalized Markup Language\",                    \"Acronym\": \"SGML\",                    \"Abbrev\": \"ISO 8879:1986\",                    \"GlossDef\": {                        \"para\": \"A meta-markup language, used to create markup languages such as DocBook.\",                        \"GlossSeeAlso\": [\"GML\", \"XML\"]                    },                    \"GlossSee\": \"markup\"                }            }        }    }}"
/*** DEPENDENCIES:
***/


static const char *json_str2 = "{\"menu\": {    \"header\": \"SVG Viewer\",    \"items\": [        {\"id\": \"Open\"},        {\"id\": \"OpenNew\", \"label\": \"Open New\"},        null,        {\"id\": \"ZoomIn\", \"label\": \"Zoom In\"},        {\"id\": \"ZoomOut\", \"label\": \"Zoom Out\"},        {\"id\": \"OriginalView\", \"label\": \"Original View\"},        null,        {\"id\": \"Quality\", \"another_null\": null},        {\"id\": \"Pause\"},        {\"id\": \"Mute\"},        null,        {\"id\": \"Find\", \"label\": \"Find...\"},        {\"id\": \"FindAgain\", \"label\": \"Find Again\"},        {\"id\": \"Copy\"},        {\"id\": \"CopyAgain\", \"label\": \"Copy Again\"},        {\"id\": \"CopySVG\", \"label\": \"Copy SVG\"},        {\"id\": \"ViewSVG\", \"label\": \"View SVG\"},        {\"id\": \"ViewSource\", \"label\": \"View Source\"},        {\"id\": \"SaveAs\", \"label\": \"Save As\"},        null,        {\"id\": \"Help\"},        {\"id\": \"About\", \"label\": \"About Adobe CVG Viewer...\"}    ]}}"
/*** DEPENDENCIES:
***/


static const char *json_str3 = "{\"menu\": {  \"id\": \"file\",  \"value\": \"File\",  \"popup\": {    \"menuitem\": [      {\"value\": \"New\", \"onclick\": \"CreateNewDoc()\"},      {\"value\": \"Open\", \"onclick\": \"OpenDoc()\"},      {\"value\": \"Close\", \"onclick\": \"CloseDoc()\"}    ]  }}}"
/*** DEPENDENCIES:
***/


double zero_dot_zero = 0.0
/*** DEPENDENCIES:
***/


static int freeit_was_called = 0
/*** DEPENDENCIES:
***/


static const char *input_json_str = "{ 'foo': ['bar', 'baz'], '': 0, 'a/b': 1, 'c%d': 2, 'e^f': 3, 'g|h': 4, 'i\\\\j': 5, 'k\\\"l': 6, ' ': 7, 'm~n': 8 }"
/*** DEPENDENCIES:
***/


static const char *rec_input_json_str = "{'arr' : [{'obj': [{},{},{'obj1': 0,'obj2': \"1\"}]}],'obj' : {'obj': {'obj': [{'obj1': 0,'obj2': \"1\"}]}}}"
/*** DEPENDENCIES:
***/


static int formatted_output = 1 << 0
/*** DEPENDENCIES:
***/


static int show_output = 1
/*** DEPENDENCIES:
***/


static int strict_mode = 0
/*** DEPENDENCIES:
***/


static int color = 0
/*** DEPENDENCIES:
***/


static const char *fname = 0
/*** DEPENDENCIES:
***/


extern json_object_delete_fn json_object_free_userdata
/*** DEPENDENCIES:
None
----------------------------
***/


extern json_object_to_json_string_fn json_object_userdata_to_json_string
/*** DEPENDENCIES:
None
----------------------------
***/


extern json_c_shallow_copy_fn json_c_shallow_copy_default
/*** DEPENDENCIES:
typedef int json_c_shallow_copy_fn(json_object *src, json_object *parent, const char *key, size_t index, json_object **dst)
----------------------------
***/


static json_object_to_json_string_fn json_object_object_to_json_string
/*** DEPENDENCIES:
None
----------------------------
***/


static json_object_to_json_string_fn json_object_boolean_to_json_string
/*** DEPENDENCIES:
None
----------------------------
***/


static json_object_to_json_string_fn json_object_double_to_json_string_default
/*** DEPENDENCIES:
None
----------------------------
***/


static json_object_to_json_string_fn json_object_int_to_json_string
/*** DEPENDENCIES:
None
----------------------------
***/


static json_object_to_json_string_fn json_object_string_to_json_string
/*** DEPENDENCIES:
None
----------------------------
***/


static json_object_to_json_string_fn json_object_array_to_json_string
/*** DEPENDENCIES:
None
----------------------------
***/


static json_object_to_json_string_fn _json_object_userdata_to_json_string
/*** DEPENDENCIES:
None
----------------------------
***/


static lh_hash_fn *char_hash_fn = lh_char_hash
/*** DEPENDENCIES:
typedef unsigned long lh_hash_fn(const void *k)
----------------------------
***/


json_object_to_json_string_fn my_custom_serializer
/*** DEPENDENCIES:
None
----------------------------
***/


json_c_shallow_copy_fn my_shallow_copy
/*** DEPENDENCIES:
typedef int json_c_shallow_copy_fn(json_object *src, json_object *parent, const char *key, size_t index, json_object **dst)
----------------------------
***/


static json_c_visit_userfunc clear_serializer
/*** DEPENDENCIES:
typedef int json_c_visit_userfunc(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
----------------------------
***/


struct incremental_step
{
  const char *string_to_parse;
  int length;
  int char_offset;
  enum json_tokener_error expected_error;
  int reset_tokener;
  int tok_flags;
} incremental_steps[] = {{"{ \"foo\": 123 }", -1, -1, json_tokener_success, 0, 0}, {"{ \"foo\": 456 }", -1, -1, json_tokener_success, 1, 0}, {"{ \"foo\": 789 }", -1, -1, json_tokener_success, 1, 0}, {"/* hello */{ \"foo\"", -1, -1, json_tokener_continue, 0, 0}, {"/* hello */:/* hello */", -1, -1, json_tokener_continue, 0, 0}, {"\"bar\"/* hello */", -1, -1, json_tokener_continue, 0, 0}, {"}/* hello */", -1, -1, json_tokener_success, 1, 0}, {"/ hello ", -1, 1, json_tokener_error_parse_comment, 1, 0}, {"/* hello\"foo\"", -1, -1, json_tokener_continue, 1, 0}, {"/* hello*\"foo\"", -1, -1, json_tokener_continue, 1, 0}, {"// hello\"foo\"", -1, -1, json_tokener_continue, 1, 0}, {"{ \"foo", -1, -1, json_tokener_continue, 0, 0}, {"\": {\"bar", -1, -1, json_tokener_continue, 0, 0}, {"\":13}}", -1, -1, json_tokener_success, 1, 0}, {"\"\\", -1, -1, json_tokener_continue, 0, 0}, {"u", -1, -1, json_tokener_continue, 0, 0}, {"d", -1, -1, json_tokener_continue, 0, 0}, {"8", -1, -1, json_tokener_continue, 0, 0}, {"3", -1, -1, json_tokener_continue, 0, 0}, {"4", -1, -1, json_tokener_continue, 0, 0}, {"\\", -1, -1, json_tokener_continue, 0, 0}, {"u", -1, -1, json_tokener_continue, 0, 0}, {"d", -1, -1, json_tokener_continue, 0, 0}, {"d", -1, -1, json_tokener_continue, 0, 0}, {"1", -1, -1, json_tokener_continue, 0, 0}, {"e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\u", -1, -1, json_tokener_continue, 0, 0}, {"d8", -1, -1, json_tokener_continue, 0, 0}, {"34", -1, -1, json_tokener_continue, 0, 0}, {"\\u", -1, -1, json_tokener_continue, 0, 0}, {"dd", -1, -1, json_tokener_continue, 0, 0}, {"1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\ud834", -1, -1, json_tokener_continue, 0, 0}, {"\\udd1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\ud834\\", -1, -1, json_tokener_continue, 0, 0}, {"udd1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\ud834\\u", -1, -1, json_tokener_continue, 0, 0}, {"dd1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"fff \\ud834\\ud", -1, -1, json_tokener_continue, 0, 0}, {"d1e bar\"", -1, -1, json_tokener_success, 1, 0}, {"\"fff \\ud834\\udd", -1, -1, json_tokener_continue, 0, 0}, {"1e bar\"", -1, -1, json_tokener_success, 1, 0}, {"\"fff \\ud83d\\ude", -1, -1, json_tokener_continue, 0, 0}, {"00 bar\"", -1, -1, json_tokener_success, 1, 0}, {"\"\xc3\xa4\"", -1, -1, json_tokener_success, 1, 0}, {"\"\xc3\xa4\"", -1, -1, json_tokener_success, 1, 0x01}, {"{ \"foo", -1, -1, json_tokener_continue, 1, 0}, {": \"bar\"}", -1, 0, json_tokener_error_parse_unexpected, 1, 0}, {"{ \"foo", -1, -1, json_tokener_continue, 0, 0}, {"\": {\"bar", -1, -1, json_tokener_continue, 0, 0}, {"\":13}}XXXX", 10, 6, json_tokener_success, 0, 0}, {"XXXX", 4, 0, json_tokener_error_parse_unexpected, 1, 0}, {"{\"x\": 123 }\"X\"", -1, 11, json_tokener_success, 0, 0}, {"\"Y\"", -1, -1, json_tokener_success, 1, 0}, {"{\"foo\":9}{\"bar\":8}", -1, 9, json_tokener_error_parse_unexpected, 1, 0x01}, {"{\"foo\":9}{\"bar\":8}", -1, 9, json_tokener_success, 0, 0x01 | 0x02}, {"{\"b\":8}ignored garbage", -1, 7, json_tokener_success, 1, 0x01 | 0x02}, {"1", 1, 1, json_tokener_continue, 0, 0}, {"2", 2, 1, json_tokener_success, 0, 0}, {"12{", 3, 2, json_tokener_success, 1, 0}, {"[02]", -1, 3, json_tokener_error_parse_number, 1, 0x01}, {"0e+0", 5, 4, json_tokener_success, 1, 0}, {"[0e+0]", -1, -1, json_tokener_success, 1, 0}, {"0e", 2, 2, json_tokener_continue, 1, 0}, {"0e", 3, 2, json_tokener_success, 1, 0}, {"0e", 3, 2, json_tokener_error_parse_eof, 1, 0x01}, {"[0e]", -1, -1, json_tokener_success, 1, 0}, {"[0e]", -1, 3, json_tokener_error_parse_number, 1, 0x01}, {"0e+", 3, 3, json_tokener_continue, 1, 0}, {"0e+", 4, 3, json_tokener_success, 1, 0}, {"0e+", 4, 3, json_tokener_error_parse_eof, 1, 0x01}, {"[0e+]", -1, -1, json_tokener_success, 1, 0}, {"[0e+]", -1, 4, json_tokener_error_parse_number, 1, 0x01}, {"0e-", 3, 3, json_tokener_continue, 1, 0}, {"0e-", 4, 3, json_tokener_success, 1, 0}, {"0e-", 4, 3, json_tokener_error_parse_eof, 1, 0x01}, {"[0e-]", -1, -1, json_tokener_success, 1, 0}, {"[0e-]", -1, 4, json_tokener_error_parse_number, 1, 0x01}, {"0e+-", 5, 3, json_tokener_success, 1, 0}, {"0e+-", 5, 3, json_tokener_error_parse_number, 1, 0x01}, {"[0e+-]", -1, 4, json_tokener_error_parse_number, 1, 0}, {"false", 5, 5, json_tokener_continue, 1, 0}, {"false", 6, 5, json_tokener_success, 1, 0}, {"true", 4, 4, json_tokener_continue, 1, 0}, {"true", 5, 4, json_tokener_success, 1, 0}, {"null", 4, 4, json_tokener_continue, 1, 0}, {"null", 5, 4, json_tokener_success, 1, 0}, {"Infinity", 9, 8, json_tokener_success, 1, 0}, {"infinity", 9, 8, json_tokener_success, 1, 0}, {"infinity", 9, 0, json_tokener_error_parse_unexpected, 1, 0x01}, {"-infinity", 10, 9, json_tokener_success, 1, 0}, {"-infinity", 10, 1, json_tokener_error_parse_unexpected, 1, 0x01}, {"inf", 3, 3, json_tokener_continue, 0, 0}, {"inity", 6, 5, json_tokener_success, 1, 0}, {"-inf", 4, 4, json_tokener_continue, 0, 0}, {"inity", 6, 5, json_tokener_success, 1, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"n", 1, 1, json_tokener_continue, 0, 0}, {"f", 1, 1, json_tokener_continue, 0, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"n", 1, 1, json_tokener_continue, 0, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"t", 1, 1, json_tokener_continue, 0, 0}, {"y", 1, 1, json_tokener_continue, 0, 0}, {"", 1, 0, json_tokener_success, 1, 0}, {"-", 1, 1, json_tokener_continue, 0, 0}, {"inf", 3, 3, json_tokener_continue, 0, 0}, {"ini", 3, 3, json_tokener_continue, 0, 0}, {"ty", 3, 2, json_tokener_success, 1, 0}, {"-", 1, 1, json_tokener_continue, 0, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"nfini", 5, 5, json_tokener_continue, 0, 0}, {"ty", 3, 2, json_tokener_success, 1, 0}, {"-i", 2, 2, json_tokener_continue, 0, 0}, {"nfinity", 8, 7, json_tokener_success, 1, 0}, {"InfinityX", 10, 8, json_tokener_success, 0, 0}, {"X", 1, 0, json_tokener_error_parse_unexpected, 1, 0}, {"Infinity1234", 13, 8, json_tokener_success, 0, 0}, {"1234", 5, 4, json_tokener_success, 1, 0}, {"Infinity9999", 8, 8, json_tokener_continue, 0, 0}, {"1234", 5, 0, json_tokener_success, 0, 0}, {"1234", 5, 4, json_tokener_success, 1, 0}, {"[9223372036854775807]", 22, 21, json_tokener_success, 1, 0}, {"[9223372036854775808]", 22, 21, json_tokener_success, 1, 0}, {"[-9223372036854775808]", 23, 22, json_tokener_success, 1, 0}, {"[-9223372036854775809]", 23, 22, json_tokener_success, 1, 0}, {"[-9223372036854775809]", 23, 21, json_tokener_error_parse_number, 1, 0x01}, {"[18446744073709551615]", 23, 22, json_tokener_success, 1, 0}, {"[18446744073709551616]", 23, 22, json_tokener_success, 1, 0}, {"[18446744073709551616]", 23, 21, json_tokener_error_parse_number, 1, 0x01}, {"18446744073709551616", 21, 20, json_tokener_success, 1, 0}, {"18446744073709551616", 21, 20, json_tokener_error_parse_eof, 1, 0x01}, {"[9223372036854775808.0]", 24, 23, json_tokener_success, 1, 0}, {"[-9223372036854775809.0]", 25, 24, json_tokener_success, 1, 0}, {"[-9223372036854775809.0]", 25, 24, json_tokener_success, 1, 0x01}, {"[18446744073709551615.0]", 25, 24, json_tokener_success, 1, 0}, {"[18446744073709551616.0]", 25, 24, json_tokener_success, 1, 0}, {"[18446744073709551616.0]", 25, 24, json_tokener_success, 1, 0x01}, {"noodle", 7, 1, json_tokener_error_parse_null, 1, 0}, {"naodle", 7, 2, json_tokener_error_parse_null, 1, 0}, {"track", 6, 2, json_tokener_error_parse_boolean, 1, 0}, {"fail", 5, 2, json_tokener_error_parse_boolean, 1, 0}, {"null123", 8, 4, json_tokener_success, 0, 0}, {&"null123"[4], 4, 3, json_tokener_success, 1, 0}, {"nullx", 6, 4, json_tokener_success, 0, 0}, {&"nullx"[4], 2, 0, json_tokener_error_parse_unexpected, 1, 0}, {"{\"a\":1}{\"b\":2}", 15, 7, json_tokener_success, 0, 0}, {&"{\"a\":1}{\"b\":2}"[7], 8, 7, json_tokener_success, 1, 0}, {&"2015-01-15"[0], 11, 4, json_tokener_success, 1, 0}, {&"2015-01-15"[4], 7, 3, json_tokener_success, 1, 0}, {&"2015-01-15"[7], 4, 3, json_tokener_success, 1, 0}, {&"2015 01 15"[0], 11, 5, json_tokener_success, 1, 0}, {&"2015 01 15"[4], 7, 4, json_tokener_success, 1, 0}, {&"2015 01 15"[7], 4, 3, json_tokener_success, 1, 0}, {"\"blue\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\\"\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\\\\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\b\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\f\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\n\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\r\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\t\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\/\"", -1, -1, json_tokener_success, 0, 0}, {"\"/\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\a\"", -1, 2, json_tokener_error_parse_string, 1, 0}, {"\'foo\'", -1, 5, json_tokener_success, 1, 0}, {"\'foo\'", -1, 0, json_tokener_error_parse_unexpected, 1, 0x01}, {"[1,2,3]", -1, -1, json_tokener_success, 0, 0}, {"[1,2,3}", -1, 6, json_tokener_error_parse_array, 1, 0}, {"{\"a\"}", -1, 4, json_tokener_error_parse_object_key_sep, 1, 0}, {"{\"a\":1]", -1, 6, json_tokener_error_parse_object_value_sep, 1, 0}, {"{\"a\"::1}", -1, 5, json_tokener_error_parse_unexpected, 1, 0}, {"{\"a\":}", -1, 5, json_tokener_error_parse_unexpected, 1, 0}, {"{\"a\":1,\"a\":2}", -1, -1, json_tokener_success, 1, 0}, {"\"a\":1}", -1, 3, json_tokener_success, 1, 0}, {"{\"a\":1", -1, -1, json_tokener_continue, 1, 0}, {"[,]", -1, 1, json_tokener_error_parse_unexpected, 1, 0}, {"[,1]", -1, 1, json_tokener_error_parse_unexpected, 1, 0}, {"[1,2,3,]", -1, -1, json_tokener_success, 0, 0}, {"[1,2,3,]", -1, 7, json_tokener_error_parse_unexpected, 1, 0x01}, {"[1,2,,3,]", -1, 5, json_tokener_error_parse_unexpected, 0, 0}, {"[1,2,,3,]", -1, 5, json_tokener_error_parse_unexpected, 0, 0x01}, {"{\"a\":1,}", -1, 7, json_tokener_error_parse_unexpected, 1, 0x01}, {"\x22\x31\x32\x33\x61\x73\x63\x24\x25\x26\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\x31\x32\x33\x61\x73\x63\x24\x25\x26\x22", -1, -1, json_tokener_success, 1, 0}, {"\x22\xe4\xb8\x96\xe7\x95\x8c\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\xe4\xb8", -1, 3, json_tokener_error_parse_utf8_string, 0, 0x10}, {"\x96\xe7\x95\x8c\x22", -1, 0, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\xe4\xb8\x96\xe7\x95\x8c\x22", -1, -1, json_tokener_success, 1, 0}, {"\x22\xcf\x80\xcf\x86\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\xf0\xa5\x91\x95\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\xe6\x9d\x4e\x22", -1, 3, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\xe6\x9d\x4e\x22", -1, 5, json_tokener_success, 1, 0}, {"\x22\xc0\xee\xc5\xf4\x22", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\xc0\xee\xc5\xf4\x22", -1, 6, json_tokener_success, 1, 0}, {"\x20\x20\x22\xe4\xb8\x96\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x20\x20\x81\x22\xe4\xb8\x96\x22", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x5b\x20\x81\x31\x5d", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x49\x6e\x66\x69\x6e\x69\x74\x79", 9, 8, json_tokener_success, 1, 0}, {"\x49\x6e\x66\x81\x6e\x69\x74\x79", -1, 3, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\x5c\x75\x64\x38\x35\x35\x5c\x75\x64\x63\x35\x35\x22", 15, 14, json_tokener_success, 1, 0x10}, {"\x22\x5c\x75\x64\x38\x35\x35\xc0\x75\x64\x63\x35\x35\x22", -1, 8, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\x5c\x75\x64\x30\x30\x33\x31\xc0\x22", -1, 9, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x31\x31\x81\x31\x31", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x7b\x22\x31\x81\x22\x3a\x31\x7d", -1, 3, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\"0\x01\x02\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\"", -1, -1, json_tokener_success, 1, 0}, {"\"\x01\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x02\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x03\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x04\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x05\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x06\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x07\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x08\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x09\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0a\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0b\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0c\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0d\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0e\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0f\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x10\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x11\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x12\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x13\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x14\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x15\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x16\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x17\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x18\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x19\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1a\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1b\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1c\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1d\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1e\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1f\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {0, -1, -1, json_tokener_success, 0, 0}}
/*** DEPENDENCIES:
enum json_tokener_error
{
  json_tokener_success,
  json_tokener_continue,
  json_tokener_error_depth,
  json_tokener_error_parse_eof,
  json_tokener_error_parse_unexpected,
  json_tokener_error_parse_null,
  json_tokener_error_parse_boolean,
  json_tokener_error_parse_number,
  json_tokener_error_parse_array,
  json_tokener_error_parse_object_key_name,
  json_tokener_error_parse_object_key_sep,
  json_tokener_error_parse_object_value_sep,
  json_tokener_error_parse_string,
  json_tokener_error_parse_comment,
  json_tokener_error_parse_utf8_string,
  json_tokener_error_size,
  json_tokener_error_memory
}
----------------------------
***/


static json_c_visit_userfunc emit_object
/*** DEPENDENCIES:
typedef int json_c_visit_userfunc(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
----------------------------
***/


static json_c_visit_userfunc skip_arrays
/*** DEPENDENCIES:
typedef int json_c_visit_userfunc(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
----------------------------
***/


static json_c_visit_userfunc pop_and_stop
/*** DEPENDENCIES:
typedef int json_c_visit_userfunc(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
----------------------------
***/


static json_c_visit_userfunc err_on_subobj2
/*** DEPENDENCIES:
typedef int json_c_visit_userfunc(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
----------------------------
***/


static json_c_visit_userfunc pop_array
/*** DEPENDENCIES:
typedef int json_c_visit_userfunc(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
----------------------------
***/


static json_c_visit_userfunc stop_array
/*** DEPENDENCIES:
typedef int json_c_visit_userfunc(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
----------------------------
***/


static json_c_visit_userfunc err_return
/*** DEPENDENCIES:
typedef int json_c_visit_userfunc(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
----------------------------
***/


