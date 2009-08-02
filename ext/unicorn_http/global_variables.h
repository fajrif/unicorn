#ifndef global_variables_h
#define global_variables_h
static VALUE mUnicorn;
static VALUE cHttpParser;
static VALUE eHttpParserError;
static VALUE sym_http_body;

static VALUE g_rack_url_scheme;
static VALUE g_request_method;
static VALUE g_request_uri;
static VALUE g_fragment;
static VALUE g_query_string;
static VALUE g_http_version;
static VALUE g_request_path;
static VALUE g_path_info;
static VALUE g_server_name;
static VALUE g_server_port;
static VALUE g_server_protocol;
static VALUE g_server_protocol_value;
static VALUE g_http_host;
static VALUE g_http_x_forwarded_proto;
static VALUE g_port_80;
static VALUE g_port_443;
static VALUE g_localhost;
static VALUE g_http;

/** Defines common length and error messages for input length validation. */
#define DEF_MAX_LENGTH(N, length) \
  static const size_t MAX_##N##_LENGTH = length; \
  static const char * const MAX_##N##_LENGTH_ERR = \
    "HTTP element " # N  " is longer than the " # length " allowed length."

/**
 * Validates the max length of given input and throws an HttpParserError
 * exception if over.
 */
#define VALIDATE_MAX_LENGTH(len, N) do { \
  if (len > MAX_##N##_LENGTH) \
    rb_raise(eHttpParserError, MAX_##N##_LENGTH_ERR); \
} while (0)

/** Defines global strings in the init method. */
#define DEF_GLOBAL(N, val) do { \
  g_##N = rb_obj_freeze(rb_str_new(val, sizeof(val) - 1)); \
  rb_global_variable(&g_##N); \
} while (0)

/* Defines the maximum allowed lengths for various input elements.*/
DEF_MAX_LENGTH(FIELD_NAME, 256);
DEF_MAX_LENGTH(FIELD_VALUE, 80 * 1024);
DEF_MAX_LENGTH(REQUEST_URI, 1024 * 12);
DEF_MAX_LENGTH(FRAGMENT, 1024); /* Don't know if this length is specified somewhere or not */
DEF_MAX_LENGTH(REQUEST_PATH, 1024);
DEF_MAX_LENGTH(QUERY_STRING, (1024 * 10));
DEF_MAX_LENGTH(HEADER, (1024 * (80 + 32)));

#endif /* global_variables_h */