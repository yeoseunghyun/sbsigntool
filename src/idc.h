/*
 * Copyright (C) 2012 Jeremy Kerr <jeremy.kerr@canonical.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
 * USA.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the OpenSSL
 * library under certain conditions as described in each individual source file,
 * and distribute linked combinations including the two.
 *
 * You must obey the GNU General Public License in all respects for all
 * of the code used other than OpenSSL. If you modify file(s) with this
 * exception, you may extend this exception to your version of the
 * file(s), but you are not obligated to do so. If you do not wish to do
 * so, delete this exception statement from your version. If you delete
 * this exception statement from all source files in the program, then
 * also delete it here.
 */
#ifndef IDC_H
#define IDC_H

#include "image.h"

#include <openssl/pkcs7.h>
#include <openssl/asn1t.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/x509.h>

#include <ccan/talloc/talloc.h>


#define SHA1_DIGEST_LENGTH 20

typedef struct idc_type_value {
	ASN1_OBJECT		*type;
	ASN1_TYPE		*value;
} IDC_TYPE_VALUE;

typedef struct idc_string {
	int type;
	union {
		ASN1_BMPSTRING	*unicode;
		ASN1_IA5STRING	*ascii;
	} value;
} IDC_STRING;

typedef struct idc_link {
	int type;
	union {
		ASN1_NULL	*url;
		ASN1_NULL	*moniker;
		IDC_STRING	*file;
	} value;
} IDC_LINK;

typedef struct idc_pe_image_data {
        ASN1_BIT_STRING		*flags;
        IDC_LINK		*file;
} IDC_PEID;

typedef struct idc_digest {
        X509_ALGOR              *alg;
        ASN1_OCTET_STRING       *digest;
} IDC_DIGEST;

typedef struct idc {
        IDC_TYPE_VALUE  *data;
        IDC_DIGEST      *digest;
} IDC;


int IDC_set(PKCS7 *p7, PKCS7_SIGNER_INFO *si, struct image *image, uint8_t *pcr_val);
struct idc *IDC_get(PKCS7 *p7, BIO *bio);
int IDC_check_hash(struct idc *idc, struct image *image);

#endif /* IDC_H */

