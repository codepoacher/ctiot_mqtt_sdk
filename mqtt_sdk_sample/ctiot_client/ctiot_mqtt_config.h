#ifndef CONNECT_MODE
#define CONNECT_MODE 1
#endif

/*TLS*/
/*TLS双向认证*/
#define SSL_CERTIFICATE_DUAL
/*TLS单向认证*/
//#define SSL_CERTIFICATE_MONO
/*TLS加密通道*/
//#define SSL_CERTIFICATE_NONE

#if defined(USE_MBEDTLS)
#ifndef ca_crt
/*TLS 根证书路径*/
#define ca_crt "./root.cer"
#endif
#ifndef client_crt
/*TLS 客户端证书路径*/
#define client_crt "./clientpublic.cer"
#endif
#ifndef client_key
/*TLS 客户端私钥路径*/
#define client_key "./clientprivate.key"
#endif
#endif
