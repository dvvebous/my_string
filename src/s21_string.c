#include "s21_string.h"

#include <stdarg.h>
#include <stdio.h>

#include "s21_sprintf.h"

#define size 50
#if defined(__APPLE__)
#define MAX_LEN 107
#define MIN_LEN -1
static const char *errors[] = {
    "Undefined error: 0",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "Device not configured",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource deadlock avoided",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "Operation not supported by device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Result too large",
    "Resource temporarily unavailable",
    "Operation now in progress",
    "Operation already in progress",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol family",
    "Address already in use",
    "Can't assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is already connected",
    "Socket is not connected",
    "Can't send after socket shutdown",
    "Too many references: can't splice",
    "Operation timed out",
    "Connection refused",
    "Too many levels of symbolic links",
    "File name too long",
    "Host is down",
    "No route to host",
    "Directory not empty",
    "Too many processes",
    "Too many users",
    "Disc quota exceeded",
    "Stale NFS file handle",
    "Too many levels of remote in path",
    "RPC struct is bad",
    "RPC version wrong",
    "RPC prog. not avail",
    "Program version wrong",
    "Bad procedure for program",
    "No locks available",
    "Function not implemented",
    "Inappropriate file type or format",
    "Authentication error",
    "Need authenticator",
    "Device power is off",
    "Device error",
    "Value too large to be stored in data type",
    "Bad executable (or shared library)",
    "Bad CPU type in executable",
    "Shared library version mismatch",
    "Malformed Mach-o file",
    "Operation canceled",
    "Identifier removed",
    "No message of desired type",
    "Illegal byte sequence",
    "Attribute not found",
    "Bad message",
    "EMULTIHOP (Reserved)",
    "No message available on STREAM",
    "ENOLINK (Reserved)",
    "No STREAM resources",
    "Not a STREAM",
    "Protocol error",
    "STREAM ioctl timeout",
    "Operation not supported on socket",
    "Policy not found",
    "State not recoverable",
    "Previous owner died",
    "Interface output queue is full"};
#endif
#if defined(__linux__)
#define MAX_LEN 133
#define MIN_LEN -1

static const char *errors[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"};
#endif

void *s21_memchr(const void *str, int c, s21_size_t n) {
  if (str == s21_NULL) return s21_NULL;
  s21_size_t i = 0;
  int *result = s21_NULL;
  while (i < n) {
    if (*(unsigned char *)(str + i) == c) {
      result = (int *)(str + i);
      break;
    }
    i++;
  }
  return (void *)result;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int res = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (*((unsigned char *)str1 + i) != *((unsigned char *)str2 + i)) {
      res = *((unsigned char *)str1 + i) - *((unsigned char *)str2 + i);
      break;
    }
  }
  return res;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++)
    *((unsigned char *)dest + i) = *((unsigned char *)src + i);
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) *((unsigned char *)str + i) = c;

  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *tmp = dest;
  while (*tmp != '\0') {
    tmp++;
  }
  while (*src != '\0' && n > 0) {
    *tmp++ = *src++;
    n--;
  }
  *tmp = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *s = s21_NULL;

  for (s21_size_t i = 0; i <= s21_strlen(str); i++) {
    if (str[i] == c) {
      s = ((char *)str) + i;
      break;
    }
  }

  return s;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  for (s21_size_t i = 0; i < n && res == 0; i++) {
    res = str1[i] - str2[i];
  }
  return res;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  int srcLen = s21_strlen(src);
  int copyLen = n;
  if (copyLen > srcLen) copyLen = srcLen + 1;

  for (int i = 0; i < copyLen; i++) {
    dest[i] = src[i];
  }

  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t count = 0;
  for (; count < s21_strlen(str1) + 1; count++) {
    if (s21_strchr(str2, str1[count])) break;
  }
  return count;
}

char *s21_strerror(int errnum) {
  static char result[512] = {'\0'};
  if (errnum < 107 && errnum > -1)
    s21_sprintf(result, "%s", errors[errnum]);
  else {
    s21_sprintf(result, "%s%d", "Unknown error: ", errnum);
  }
  return result;
}

s21_size_t s21_strlen(const char *str) {
  unsigned int count = 0;
  while (*str != '\0') {
    count++;
    str++;
  }
  return count;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  s21_size_t len1 = s21_strlen(str1);
  s21_size_t len2 = s21_strlen(str2);
  char *result = NULL;
  for (int i = (int)len1 - 1; i >= 0; i--) {
    for (int j = 0; j < (int)len2; j++) {
      if (str1[i] == str2[j]) {
        result = (char *)str1 + (int)i;
      }
    }
  }

  return result;
}

char *s21_strrchr(const char *str, int c) {
  const char *result = NULL;
  for (int i = 0; i < (int)s21_strlen(str) + 1; i++) {
    if (str[i] == c) {
      result = str + i;
    }
  }

  return (char *)result;
}

char *s21_strstr(const char *haystack, const char *needle) {
  unsigned int i = 0;
  int flag = 1;
  for (i = 0; haystack[i] != '\0' && flag == 1; i++) {
    flag = 0;
    for (unsigned int j = 0; needle[j] != '\0' && flag == 0; j++) {
      if ((haystack[i + j] == '\0') || (haystack[i + j] != needle[j])) {
        flag = 1;
      }
    }
  }
  i--;
  return flag ? s21_NULL : (char *)&haystack[i];
}

char *s21_strtok(char *str, const char *delim) {
  static char *last_end = NULL;
  char *start = str;

  if (str == NULL) start = last_end;

  int stop_flag = 0;
  for (int i = 0; start != NULL && start[i] != '\0' && !stop_flag; i++) {
    for (int j = 0; delim[j] != '\0'; j++) {
      if (start[i] == delim[j]) {
        start[i] = '\0';
        stop_flag = 1;
        break;
      }
    }
    last_end = start + i + 1;
    if (*last_end == '\0') last_end = NULL;
  }

  return start;
}
