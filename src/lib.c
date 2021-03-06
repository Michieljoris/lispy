#include "lib.h"

// https://en.wikibooks.org/wiki/C_Programming/String_manipulation#The_more_commonly-used_string_functions

/* strlen */
zize_t _strlen(const char *s) {
  const char *p = s; /* pointer to character constant */
  /* Loop over the data in s.  */
  while (*p != '\0') p++;
  return (zize_t)(p - s);
}

/* strcpy */
char *(_strcpy)(char *restrict dst, const char *restrict src) {
  char *_dst = dst;
  const char *_src = src;
  /* Do the copying in a loop.  */
  while ((*_dst++ = *_src++) != '\0')
    ; /* The body of this loop is left empty. */
  /* Return the destination string.  */
  return dst;
}

/* strcat */
char *(_strcat)(char *restrict s1, const char *restrict s2) {
  char *s = s1;
  /* Move s so that it points to the end of s1.  */
  while (*s != '\0') s++;
  /* Copy the contents of s2 into the space at the end of s1.  */
  _strcpy(s, s2);
  return s1;
}

/* strchr */
char *(_strchr)(const char *s, int c) {
  char ch = c;
  /* Scan s for the character.  When this loop is finished,
     s will either point to the end of the string or the
     character we were looking for.  */
  while (*s != '\0' && *s != ch) s++;
  return (*s == ch) ? (char *)s : NULL;
}

/* strcmp */
int(_strcmp)(const char *s1, const char *s2) {
  unsigned char uc1, uc2;
  /* Move s1 and s2 to the first differing characters
     in each string, or the ends of the strings if they
     are identical.  */
  while (*s1 != '\0' && *s1 == *s2) {
    s1++;
    s2++;
  }
  /* Compare the characters as unsigned char and
     return the difference.  */
  uc1 = (*(unsigned char *)s1);
  uc2 = (*(unsigned char *)s2);
  return ((uc1 < uc2) ? -1 : (uc1 > uc2));
}

/* int strcmp2(const char *p1, const char *p2) { */
/*   const unsigned char *s1 = (const unsigned char *)p1; */
/*   const unsigned char *s2 = (const unsigned char *)p2; */
/*   unsigned char c1, c2; */
/*   do { */
/*     c1 = (unsigned char)*s1++; */
/*     c2 = (unsigned char)*s2++; */
/*     if (c1 == '\0') return c1 - c2; */
/*   } while (c1 == c2); */
/*   return c1 - c2; */
/* } */

/* strncat */
char *(_strncat)(char *restrict s1, const char *restrict s2, zize_t n) {
  char *s = s1;
  /* Loop over the data in s1.  */
  while (*s != '\0') s++;
  /* s now points to s1's trailing null character, now copy
     up to n bytes from s2 into s stopping if a null character
     is encountered in s2.
     It is not safe to use strncpy here since it copies EXACTLY n
     characters, NULL padding if necessary.  */
  while (n != 0 && (*s = *s2++) != '\0') {
    n--;
    s++;
  }
  if (*s != '\0') *s = '\0';
  return s1;
}

/* strncmp */
int(_strncmp)(const char *s1, const char *s2, zize_t n) {
  unsigned char uc1, uc2;
  /* Nothing to compare?  Return zero.  */
  if (n == 0) return 0;
  /* Loop, comparing bytes.  */
  while (n-- > 0 && *s1 == *s2) {
    /* If we've run out of bytes or hit a null, return zero
       since we already know *s1 == *s2.  */
    if (n == 0 || *s1 == '\0') return 0;
    s1++;
    s2++;
  }
  uc1 = (*(unsigned char *)s1);
  uc2 = (*(unsigned char *)s2);
  return ((uc1 < uc2) ? -1 : (uc1 > uc2));
}

/* memset */
void *(memset)(void *s, int c, unsigned long n) {
  unsigned char *us = s;
  unsigned char uc = c;
  while (n-- != 0) *us++ = uc;
  return s;
}

/* strncpy */
char *(_strncpy)(char *restrict s1, const char *restrict s2, zize_t n) {
  char *dst = s1;
  const char *src = s2;
  /* Copy bytes, one at a time.  */
  while (n > 0) {
    n--;
    if ((*dst++ = *src++) == '\0') {
      /* If we get here, we found a null character at the end
         of s2, so use memset to put null bytes at the end of
         s1.  */
      memset(dst, '\0', n);
      break;
    }
  }
  return s1;
}
/* strrchr */
char *(_strrchr)(const char *s, int c) {
  const char *last = NULL;
  /* If the character we're looking for is the terminating null,
     we just need to look for that character as there's only one
     of them in the string.  */
  if (c == '\0') return _strchr(s, c);
  /* Loop through, finding the last match before hitting NULL.  */
  while ((s = _strchr(s, c)) != NULL) {
    last = s;
    s++;
  }
  return (char *)last;
}
/* memcmp */
int(memcmp)(const void *s1, const void *s2, unsigned long n) {
  const unsigned char *us1 = (const unsigned char *)s1;
  const unsigned char *us2 = (const unsigned char *)s2;
  while (n-- != 0) {
    if (*us1 != *us2) return (*us1 < *us2) ? -1 : +1;
    us1++;
    us2++;
  }
  return 0;
}

/* strstr */
char *(_strstr)(const char *haystack, const char *needle) {
  zize_t needlelen;
  /* Check for the null needle case.  */
  if (*needle == '\0') return (char *)haystack;
  needlelen = _strlen(needle);
  for (; (haystack = _strchr(haystack, *needle)) != NULL; haystack++)
    if (memcmp(haystack, needle, needlelen) == 0) return (char *)haystack;
  return NULL;
}

char *strsubst(char *s, char c1, char c2) {
  char *s0 = s;
  while (*s != '\0') {
    if (*s == c1) *s = c2;
    s++;
  }
  return s0;
}

/* memmove */
void *(_memmove)(void *s1, const void *s2, zize_t n) {
  /* note: these don't have to point to unsigned chars */
  char *p1 = s1;
  const char *p2 = s2;
  /* test for overlap that prevents an ascending copy */
  if (p2 < p1 && p1 < p2 + n) {
    /* do a descending copy */
    p2 += n;
    p1 += n;
    while (n-- != 0) *--p1 = *--p2;
  } else
    while (n-- != 0) *p1++ = *p2++;
  return s1;
}

/* #include <ctype.h> */

int merrno2 = 0;
int *merrno = &merrno2;
/* int errno = 0; */

int isalpha(int c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

int isupper(int c) { return c >= 'A' && c <= 'Z'; }

int isdigit(int c) { return (c >= '0' && c <= '9'); }

int isspace(int c) {
  return c == ' ' || c == '\t';  // || whatever other char you consider space
}

/* int tolower(int c) */
/* { */
/*    if ( !isalpha(c) ) return c; */
/*    return (c >= 'A' && c <= 'Z') ? c - 'A' : c; */
/* } */

/*
 * Convert a string to a long integer.
 *
 * Ignores `locale' stuff.  Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */
long _strtol(const char *nptr, char **endptr, int base) {
  const char *s;
  long acc, cutoff;
  int c;
  int neg, any, cutlim;
  /*
   * Skip white space and pick up leading +/- sign if any.
   * If base is 0, allow 0x for hex and 0 for octal, else
   * assume decimal; if base is already 16, allow 0x.
   */
  s = nptr;
  do {
    c = (unsigned char)*s++;
  } while (isspace(c));
  if (c == '-') {
    neg = 1;
    c = *s++;
  } else {
    neg = 0;
    if (c == '+') c = *s++;
  }
  if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
    c = s[1];
    s += 2;
    base = 16;
  }
  if (base == 0) base = c == '0' ? 8 : 10;
  /*
   * Compute the cutoff value between legal numbers and illegal
   * numbers.  That is the largest legal value, divided by the
   * base.  An input number that is greater than this value, if
   * followed by a legal input character, is too big.  One that
   * is equal to this value may be valid or not; the limit
   * between valid and invalid numbers is then based on the last
   * digit.  For instance, if the range for longs is
   * [-2147483648..2147483647] and the input base is 10,
   * cutoff will be set to 214748364 and cutlim to either
   * 7 (neg==0) or 8 (neg==1), meaning that if we have accumulated
   * a value > 214748364, or equal but the next digit is > 7 (or 8),
   * the number is too big, and we will return a range error.
   *
   * Set any if any `digits' consumed; make it negative to indicate
   * overflow.
   */
  cutoff = neg ? LONG_MIN : LONG_MAX;
  cutlim = cutoff % base;
  cutoff /= base;
  if (neg) {
    if (cutlim > 0) {
      cutlim -= base;
      cutoff += 1;
    }
    cutlim = -cutlim;
  }
  for (acc = 0, any = 0;; c = (unsigned char)*s++) {
    if (isdigit(c))
      c -= '0';
    else if (isalpha(c))
      c -= isupper(c) ? 'A' - 10 : 'a' - 10;
    else
      break;
    if (c >= base) break;
    if (any < 0) continue;
    if (neg) {
      if (acc < cutoff || (acc == cutoff && c > cutlim)) {
        any = -1;
        acc = LONG_MIN;
        *merrno = ERANGE;
      } else {
        any = 1;
        acc *= base;
        acc -= c;
      }
    } else {
      if (acc > cutoff || (acc == cutoff && c > cutlim)) {
        any = -1;
        acc = LONG_MAX;
        *merrno = ERANGE;
      } else {
        any = 1;
        acc *= base;
        acc += c;
      }
    }
  }
  if (endptr != 0) *endptr = (char *)(any ? s - 1 : nptr);
  return (acc);
}

int _strtoi(const char *nptr, char **endptr, int base) {
  const char *s;
  long acc, cutoff;
  int c;
  int neg, any, cutlim;
  /*
   * Skip white space and pick up leading +/- sign if any.
   * If base is 0, allow 0x for hex and 0 for octal, else
   * assume decimal; if base is already 16, allow 0x.
   */
  s = nptr;
  do {
    c = (unsigned char)*s++;
  } while (isspace(c));
  if (c == '-') {
    neg = 1;
    c = *s++;
  } else {
    neg = 0;
    if (c == '+') c = *s++;
  }
  if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
    c = s[1];
    s += 2;
    base = 16;
  }
  if (base == 0) base = c == '0' ? 8 : 10;
  /*
   * Compute the cutoff value between legal numbers and illegal
   * numbers.  That is the largest legal value, divided by the
   * base.  An input number that is greater than this value, if
   * followed by a legal input character, is too big.  One that
   * is equal to this value may be valid or not; the limit
   * between valid and invalid numbers is then based on the last
   * digit.  For instance, if the range for longs is
   * [-2147483648..2147483647] and the input base is 10,
   * cutoff will be set to 214748364 and cutlim to either
   * 7 (neg==0) or 8 (neg==1), meaning that if we have accumulated
   * a value > 214748364, or equal but the next digit is > 7 (or 8),
   * the number is too big, and we will return a range error.
   *
   * Set any if any `digits' consumed; make it negative to indicate
   * overflow.
   */
  cutoff = neg ? INT_MIN : INT_MAX;
  cutlim = cutoff % base;
  cutoff /= base;
  if (neg) {
    if (cutlim > 0) {
      cutlim -= base;
      cutoff += 1;
    }
    cutlim = -cutlim;
  }
  for (acc = 0, any = 0;; c = (unsigned char)*s++) {
    if (isdigit(c))
      c -= '0';
    else if (isalpha(c))
      c -= isupper(c) ? 'A' - 10 : 'a' - 10;
    else
      break;
    if (c >= base) break;
    if (any < 0) continue;
    if (neg) {
      if (acc < cutoff || (acc == cutoff && c > cutlim)) {
        any = -1;
        acc = INT_MIN;
        *merrno = ERANGE;
      } else {
        any = 1;
        acc *= base;
        acc -= c;
      }
    } else {
      if (acc > cutoff || (acc == cutoff && c > cutlim)) {
        any = -1;
        acc = INT_MAX;
        *merrno = ERANGE;
      } else {
        any = 1;
        acc *= base;
        acc += c;
      }
    }
  }
  if (endptr != 0) *endptr = (char *)(any ? s - 1 : nptr);
  return (acc);
}

char *itostr(char str[], long int num) {
  long int i, rem, len = 0, n;

  n = num;
  while (n != 0) {
    len++;
    n /= 10;
  }
  for (i = 0; i < len; i++) {
    rem = num % 10;
    num = num / 10;
    str[len - (i + 1)] = rem + '0';
  }
  str[len] = '\0';
  return str;
}

int power(int x, uint y) {
  int temp;
  if (y == 0) return 1;
  temp = power(x, y / 2);
  temp *= temp;
  if (y % 2 == 0)
    return temp;
  else
    return x * temp;
}

int ipow(int base, int exp) {
  int result = 1;
  for (;;) {
    if (exp & 1) result *= base;
    exp >>= 1;
    if (!exp) break;
    base *= base;
  }

  return result;
}

long logical_rshift(long x, int n) {
  long mask = (1 << (sizeof(long) * 8 - n)) - 1;
  return x >> n & mask;
}

int is_eq_str(void *k1, void *k2) { return _strcmp(k1, k2) == 0; }

int number_len(int n) {
  int len = n < 0 ? 2 : 1;
  while (1) {
    n = n / 10;
    if (n)
      len++;
    else
      return len;
  }
}

#define CHAR_BIT 8
#define BITS (CHAR_BIT * sizeof(int) - 1)

int max(int a, int b) {
  int rets[] = {a, b};
  return rets[(unsigned)(a - b) >> BITS];
}

int min(int a, int b) {
  int rets[] = {b, a};
  return rets[(unsigned)(a - b) >> BITS];
}
