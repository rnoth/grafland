#define g__x86_64__

/* constants */
#define CHAR_BITS    8

#ifdef g__x86_64__
#define GSIZE_MAX     (18446744073709551615UL)
#define GSIZE_MIN     0
#define GSSIZE_MAX    9223372036854775807
#define GSSIZE_MIN    -9223372036854775808
#define GUCHAR_MAX    255
#define GUCHAR_MIN    0
#define GCHAR_MAX     127
#define GCHAR_MIN     -128
#define GINT_MAX      2147483647
#define GINT_MIN      -2147483648
#define GLONG_MAX     9223372036854775807
#define GLONG_MIN     -9223372036854775808
#define GLLONG_MAX    9223372036854775807
#define GLLONG_MIN    -9223372036854775808
#endif

#ifdef g__aarch64__

#define GSIZE_MAX     (18446744073709551615UL)
#define GSIZE_MIN     0
#define GSSIZE_MAX    9223372036854775807
#define GSSIZE_MIN    -9223372036854775808
#define GUCHAR_MAX    255
#define GUCHAR_MIN    0
#define GCHAR_MAX     255
#define GCHAR_MIN     0
#define GINT_MAX      2147483647
#define GINT_MIN      -2147483648
#define GLONG_MAX     9223372036854775807
#define GLONG_MIN     -9223372036854775808
#define GLLONG_MAX    9223372036854775807
#define GLLONG_MIN    -9223372036854775808

#endif
