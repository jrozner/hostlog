#include <stddef.h>
#include <syslog.h>
#include <netdb.h>
#include <nss.h>
#include <arpa/inet.h>

enum nss_status _nss_hostlog_gethostbyname4_r(const char *, struct gaih_addrtuple **, char *, size_t, int *, int *, int32_t*);
enum nss_status _nss_hostlog_gethostbyname3_r(const char *, int, struct hostent *, char *, size_t, int *, int *, int32_t *, char **);
enum nss_status _nss_hostlog_gethostbyname2_r(const char *, int, struct hostent *, char *, size_t, int *, int *);
enum nss_status _nss_hostlog_gethostbyname_r(const char *, struct hostent *, char *, size_t, int *, int *);
enum nss_status _nss_hostlog_gethostbyaddr_r(const void *, int, int, struct hostent *, char *, size_t, int *, int *);

enum nss_status _nss_hostlog_gethostbyname4_r(const char* name, struct gaih_addrtuple **pat, char *buffer, size_t buflen, int *errnop, int *h_errnop, int32_t *ttlp) {
  syslog(LOG_INFO, "looked up hostname: %s", name);

  return NSS_STATUS_NOTFOUND;
}

enum nss_status _nss_hostlog_gethostbyname3_r(const char *name, int af, struct hostent *result, char *buffer, size_t buflen, int *errnop, int *h_errnop, int32_t *ttlp, char **canonp) {
  syslog(LOG_INFO, "looked up hostname: %s", name);

  return NSS_STATUS_NOTFOUND;
}

enum nss_status _nss_hostlog_gethostbyname2_r(const char *name, int af, struct hostent *result, char *buffer, size_t buflen, int *errnop, int *h_errnop) {
  syslog(LOG_INFO, "looked up hostname: %s", name);

  return NSS_STATUS_NOTFOUND;
}

enum nss_status _nss_hostlog_gethostbyname_r(const char *name, struct hostent *result, char *buffer, size_t buflen, int *errnop, int *h_errnop) {
  syslog(LOG_INFO, "looked up hostname: %s", name);

  return NSS_STATUS_NOTFOUND;
}

enum nss_status _nss_hostlog_gethostbyaddr_r(const void *addr, int len, int af, struct hostent *result, char *buffer, size_t buflen, int *errnop, int *h_errnop) {
  char addr_string[INET6_ADDRSTRLEN] = {0};
  if (inet_ntop(af, addr, addr_string, INET6_ADDRSTRLEN) == NULL) {
    return NSS_STATUS_NOTFOUND;
  }

  syslog(LOG_INFO, "looked up address: %s", addr_string);

  return NSS_STATUS_NOTFOUND;
}
