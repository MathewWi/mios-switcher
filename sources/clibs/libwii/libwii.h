#ifndef _LIBWII_H_
#define _LIBWII_H_
#include "../ctypes.h"
#define ES_SIG_RSA4096 0x00000100
#define ES_SIG_RSA2048 0x01000100
#define ES_SIG_ECDSA 0x02000100
typedef u32 sigtype;
typedef sigtype sig_header;
typedef sig_header signed_blob;
typedef u8 sha1[20];
typedef u8 aeskey[16];
typedef char sig_issuer[0x40];
typedef struct _sig_rsa2048 {
	sigtype type;
	u8 sig[256];
	u8 fill[60];
} __attribute__((packed)) sig_rsa2048;
typedef struct _sig_rsa4096 {
	sigtype type;
	u8 sig[512];
	u8 fill[60];
}  __attribute__((packed)) sig_rsa4096;
typedef struct _sig_ecdsa {
	sigtype type;
	u8 sig[60];
	u8 fill[64];
}  __attribute__((packed)) sig_ecdsa;
typedef struct _tiklimit {
	u32 tag;
	u32 value;
} __attribute__((packed)) tiklimit;
typedef struct _tik {
	sig_issuer issuer;
	u8 fill[63];
	aeskey cipher_title_key;
	u8 fill2;
	u64 ticketid;
	u32 devicetype;
	u64 titleid;
	u16 access_mask;
	u8 reserved[0x3c];
	u8 cidx_mask[0x40];
	u16 padding;
	tiklimit limits[8];
} __attribute__((packed)) tik;
typedef struct _tmd_content {
	u32 cid;
	u16 index;
	u16 type;
	u64 size;
	sha1 hash;
}  __attribute__((packed)) tmd_content;
typedef struct _tmd {
	sig_issuer issuer;
	u8 version;
	u8 ca_crl_version;
	u8 signer_crl_version;
	u8 fill2;
	u64 sys_version;
	u64 title_id;
	u32 title_type;
	u16 group_id;
	u16 zero;
	u16 region;
	u8 ratings[16];
	u8 reserved[12];
	u8 ipc_mask[12];
	u8 reserved2[18];
	u32 access_rights;
	u16 title_version;
	u16 num_contents;
	u16 boot_index;
	u16 fill3;
	tmd_content contents[];
} __attribute__((packed)) tmd;
#define SIGNATURE_SIZE(x) (((*(x))==ES_SIG_RSA2048)?sizeof(sig_rsa2048):(((*(x))==ES_SIG_RSA4096)?sizeof(sig_rsa4096):(((*(x))==ES_SIG_ECDSA)?sizeof(sig_ecdsa):0)))
#define IS_VALID_SIGNATURE(x) (((*(x))==ES_SIG_RSA2048) || ((*(x))==ES_SIG_RSA4096) || ((*(x))==ES_SIG_ECDSA))
#define SIGNATURE_PAYLOAD(x) ((void *)(((u8*)(x))+SIGNATURE_SIZE(x)))
#endif
