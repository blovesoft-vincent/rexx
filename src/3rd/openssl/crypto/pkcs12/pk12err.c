
#include <stdio.h>
#include <openssl/err.h>
#include <openssl/pkcs12.h>

/* BEGIN ERROR CODES */
#ifndef OPENSSL_NO_ERR

# define ERR_FUNC(func) ERR_PACK(ERR_LIB_PKCS12,func,0)
# define ERR_REASON(reason) ERR_PACK(ERR_LIB_PKCS12,0,reason)

static ERR_STRING_DATA PKCS12_str_functs[] = {
    {ERR_FUNC(PKCS12_F_PARSE_BAG), "PARSE_BAG"},
    {ERR_FUNC(PKCS12_F_PARSE_BAGS), "PARSE_BAGS"},
    {ERR_FUNC(PKCS12_F_PKCS12_ADD_FRIENDLYNAME), "PKCS12_ADD_FRIENDLYNAME"},
    {ERR_FUNC(PKCS12_F_PKCS12_ADD_FRIENDLYNAME_ASC),
     "PKCS12_add_friendlyname_asc"},
    {ERR_FUNC(PKCS12_F_PKCS12_ADD_FRIENDLYNAME_UNI),
     "PKCS12_add_friendlyname_uni"},
    {ERR_FUNC(PKCS12_F_PKCS12_ADD_LOCALKEYID), "PKCS12_add_localkeyid"},
    {ERR_FUNC(PKCS12_F_PKCS12_CREATE), "PKCS12_create"},
    {ERR_FUNC(PKCS12_F_PKCS12_GEN_MAC), "PKCS12_gen_mac"},
    {ERR_FUNC(PKCS12_F_PKCS12_INIT), "PKCS12_init"},
    {ERR_FUNC(PKCS12_F_PKCS12_ITEM_DECRYPT_D2I), "PKCS12_item_decrypt_d2i"},
    {ERR_FUNC(PKCS12_F_PKCS12_ITEM_I2D_ENCRYPT), "PKCS12_item_i2d_encrypt"},
    {ERR_FUNC(PKCS12_F_PKCS12_ITEM_PACK_SAFEBAG), "PKCS12_item_pack_safebag"},
    {ERR_FUNC(PKCS12_F_PKCS12_KEY_GEN_ASC), "PKCS12_key_gen_asc"},
    {ERR_FUNC(PKCS12_F_PKCS12_KEY_GEN_UNI), "PKCS12_key_gen_uni"},
    {ERR_FUNC(PKCS12_F_PKCS12_MAKE_KEYBAG), "PKCS12_MAKE_KEYBAG"},
    {ERR_FUNC(PKCS12_F_PKCS12_MAKE_SHKEYBAG), "PKCS12_MAKE_SHKEYBAG"},
    {ERR_FUNC(PKCS12_F_PKCS12_NEWPASS), "PKCS12_newpass"},
    {ERR_FUNC(PKCS12_F_PKCS12_PACK_P7DATA), "PKCS12_pack_p7data"},
    {ERR_FUNC(PKCS12_F_PKCS12_PACK_P7ENCDATA), "PKCS12_pack_p7encdata"},
    {ERR_FUNC(PKCS12_F_PKCS12_PARSE), "PKCS12_parse"},
    {ERR_FUNC(PKCS12_F_PKCS12_PBE_CRYPT), "PKCS12_pbe_crypt"},
    {ERR_FUNC(PKCS12_F_PKCS12_PBE_KEYIVGEN), "PKCS12_PBE_keyivgen"},
    {ERR_FUNC(PKCS12_F_PKCS12_SETUP_MAC), "PKCS12_setup_mac"},
    {ERR_FUNC(PKCS12_F_PKCS12_SET_MAC), "PKCS12_set_mac"},
    {ERR_FUNC(PKCS12_F_PKCS12_UNPACK_AUTHSAFES), "PKCS12_unpack_authsafes"},
    {ERR_FUNC(PKCS12_F_PKCS12_UNPACK_P7DATA), "PKCS12_unpack_p7data"},
    {ERR_FUNC(PKCS12_F_PKCS12_VERIFY_MAC), "PKCS12_verify_mac"},
    {ERR_FUNC(PKCS12_F_PKCS8_ADD_KEYUSAGE), "PKCS8_add_keyusage"},
    {ERR_FUNC(PKCS12_F_PKCS8_ENCRYPT), "PKCS8_encrypt"},
    {0, NULL}
};

static ERR_STRING_DATA PKCS12_str_reasons[] = {
    {ERR_REASON(PKCS12_R_CANT_PACK_STRUCTURE), "cant pack structure"},
    {ERR_REASON(PKCS12_R_CONTENT_TYPE_NOT_DATA), "content type not data"},
    {ERR_REASON(PKCS12_R_DECODE_ERROR), "decode error"},
    {ERR_REASON(PKCS12_R_ENCODE_ERROR), "encode error"},
    {ERR_REASON(PKCS12_R_ENCRYPT_ERROR), "encrypt error"},
    {ERR_REASON(PKCS12_R_ERROR_SETTING_ENCRYPTED_DATA_TYPE),
     "error setting encrypted data type"},
    {ERR_REASON(PKCS12_R_INVALID_NULL_ARGUMENT), "invalid null argument"},
    {ERR_REASON(PKCS12_R_INVALID_NULL_PKCS12_POINTER),
     "invalid null pkcs12 pointer"},
    {ERR_REASON(PKCS12_R_IV_GEN_ERROR), "iv gen error"},
    {ERR_REASON(PKCS12_R_KEY_GEN_ERROR), "key gen error"},
    {ERR_REASON(PKCS12_R_MAC_ABSENT), "mac absent"},
    {ERR_REASON(PKCS12_R_MAC_GENERATION_ERROR), "mac generation error"},
    {ERR_REASON(PKCS12_R_MAC_SETUP_ERROR), "mac setup error"},
    {ERR_REASON(PKCS12_R_MAC_STRING_SET_ERROR), "mac string set error"},
    {ERR_REASON(PKCS12_R_MAC_VERIFY_ERROR), "mac verify error"},
    {ERR_REASON(PKCS12_R_MAC_VERIFY_FAILURE), "mac verify failure"},
    {ERR_REASON(PKCS12_R_PARSE_ERROR), "parse error"},
    {ERR_REASON(PKCS12_R_PKCS12_ALGOR_CIPHERINIT_ERROR),
     "pkcs12 algor cipherinit error"},
    {ERR_REASON(PKCS12_R_PKCS12_CIPHERFINAL_ERROR),
     "pkcs12 cipherfinal error"},
    {ERR_REASON(PKCS12_R_PKCS12_PBE_CRYPT_ERROR), "pkcs12 pbe crypt error"},
    {ERR_REASON(PKCS12_R_UNKNOWN_DIGEST_ALGORITHM),
     "unknown digest algorithm"},
    {ERR_REASON(PKCS12_R_UNSUPPORTED_PKCS12_MODE), "unsupported pkcs12 mode"},
    {0, NULL}
};

#endif

void ERR_load_PKCS12_strings(void)
{
#ifndef OPENSSL_NO_ERR

    if (ERR_func_error_string(PKCS12_str_functs[0].error) == NULL) {
        ERR_load_strings(0, PKCS12_str_functs);
        ERR_load_strings(0, PKCS12_str_reasons);
    }
#endif
}
