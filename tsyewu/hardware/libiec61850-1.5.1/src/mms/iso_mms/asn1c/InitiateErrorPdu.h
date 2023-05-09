/*
 * Generated by asn1c-0.9.21 (http://lionet.info/asn1c)
 * From ASN.1 module "MMS"
 * 	found in "../mms-extended.asn"
 * 	`asn1c -fskeletons-copy`
 */

#ifndef	_InitiateErrorPdu_H_
#define	_InitiateErrorPdu_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ServiceError.h"

#ifdef __cplusplus
extern "C" {
#endif

/* InitiateErrorPdu */
typedef ServiceError_t	 InitiateErrorPdu_t;

/* Implementation */
LIB61850_INTERNAL extern asn_TYPE_descriptor_t asn_DEF_InitiateErrorPdu;
LIB61850_INTERNAL asn_struct_free_f InitiateErrorPdu_free;
LIB61850_INTERNAL asn_struct_print_f InitiateErrorPdu_print;
LIB61850_INTERNAL asn_constr_check_f InitiateErrorPdu_constraint;
LIB61850_INTERNAL ber_type_decoder_f InitiateErrorPdu_decode_ber;
LIB61850_INTERNAL der_type_encoder_f InitiateErrorPdu_encode_der;
LIB61850_INTERNAL xer_type_decoder_f InitiateErrorPdu_decode_xer;
LIB61850_INTERNAL xer_type_encoder_f InitiateErrorPdu_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _InitiateErrorPdu_H_ */
