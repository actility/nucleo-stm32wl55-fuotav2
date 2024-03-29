/**
  ******************************************************************************
  * @file    kms_platf_objects_config.h
  * @author  MCD Application Team
  * @brief   This file contains definitions for Key Management Services (KMS)
  *          module platform objects management configuration
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in
  * the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef KMS_PLATF_OBJECTS_CONFIG_H
#define KMS_PLATF_OBJECTS_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "kms_platf_objects_interface.h"
#include "app_sfu.h"
#include "Commissioning.h"
#include "lorawan_conf.h" /* KEY_EXTRACTABLE */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Key_Management_Services Key Management Services (KMS)
  * @{
  */

/** @addtogroup KMS_PLATF Platform Objects
  * @{
  */

/* Exported constants --------------------------------------------------------*/

/** @addtogroup KMS_PLATF_Exported_Constants Exported Constants
  * @note KMS support different type of objects, their respective ranges are
  *       defined here
  * @{
  */

/* We consider that the ORDER (static = lower ids) will be kept. */
#define KMS_INDEX_MIN_EMBEDDED_OBJECTS       1UL   /*!< Embedded objects min ID. Must be > 0 as '0' is never a
                                                        valid key index */
#define KMS_INDEX_MAX_EMBEDDED_OBJECTS       (KMS_INDEX_MIN_EMBEDDED_OBJECTS+19UL)    /*!< Embedded objects max ID */
#define KMS_INDEX_MIN_NVM_STATIC_OBJECTS     (KMS_INDEX_MAX_EMBEDDED_OBJECTS+1UL)     /*!< NVM static objects min ID */
#define KMS_INDEX_MAX_NVM_STATIC_OBJECTS     (KMS_INDEX_MIN_NVM_STATIC_OBJECTS+19UL)  /*!< NVM static objects max ID */

#define KMS_INDEX_MIN_NVM_DYNAMIC_OBJECTS    (KMS_INDEX_MAX_NVM_STATIC_OBJECTS+1UL)   /*!< NVM dynamic objects min ID */
#define KMS_INDEX_MAX_NVM_DYNAMIC_OBJECTS    (KMS_INDEX_MIN_NVM_DYNAMIC_OBJECTS+19UL) /*!< NVM dynamic objects max ID */

/* Blob import key index */
#define KMS_INDEX_BLOBIMPORT_VERIFY       (1U)      /*!< Index in @ref KMS_PlatfObjects_EmbeddedList
                                                         where the blob verification key is stored */
#define KMS_INDEX_BLOBIMPORT_DECRYPT      (2U)      /*!< Index in @ref KMS_PlatfObjects_EmbeddedList
                                                         where the blob decryption key is stored */

#define RAW_TO_INT32A(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) \
  0x##a##b##c##d, 0x##e##f##g##h, 0x##i##j##k##l, 0x##m##n##o##p
#define RAW_TO_DEVJOINKEY_STRUCT(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x) \
  0x##a##b##c##d, 0x##e##f##g##h, 0x##i##j##k##l, 0x##m##n##o##p, 0x##t##s##r##q, 0x##x##w##v##u

#define FORMAT_KEY_32(...) RAW_TO_INT32A(__VA_ARGS__)
#define FORMAT_DEVJOINKEY(...) RAW_TO_DEVJOINKEY_STRUCT(__VA_ARGS__)
/**
  * @}
  */

/*
 * Embedded objects definition
 *
 */
#ifdef KMS_PLATF_OBJECTS_C
/** @addtogroup KMS_PLATF_Private_Variables Private Variables
  * @{
  */
/* Place code in a specific section*/
#if defined(__ICCARM__)
#pragma default_variable_attributes = @ ".SE_embedded_Keys"
#elif defined(__CC_ARM)
#pragma arm section rodata = ".SE_embedded_Keys"
#endif

KMS_DECLARE_BLOB_STRUCT(, 24);
KMS_DECLARE_BLOB_STRUCT(, 30);
KMS_DECLARE_BLOB_STRUCT(, 256);

/* This object is used for KMS blob header signature                 */
#if defined(__GNUC__)
__attribute__((section(".SE_embedded_Keys")))
#endif
static const kms_obj_keyhead_30_t   KMS_Blob_ECDSA_Verify =
{
  KMS_ABI_VERSION_CK_2_40,         /*  uint32_t version; */
  KMS_ABI_CONFIG_KEYHEAD,          /*  uint32_t configuration; */
  120,                             /*  uint32_t blobs_size; */
  4,                               /*  uint32_t blobs_count; */
  1,                               /*  uint32_t object_id; */
  {
    CKA_CLASS,        sizeof(CK_OBJECT_CLASS), CKO_PUBLIC_KEY,
    CKA_KEY_TYPE,     sizeof(CK_KEY_TYPE),     CKK_EC,
    CKA_EC_PARAMS,    10, 0x06082a86U, 0x48ce3d03U, 0x0107U,
    CKA_EC_POINT,     67, 0x044104baU, 0xf297f83eU, 0xe307dc16U, 0xc371781dU, 0xf1b03ef0U, 0x95b04454U, 0x128148fbU, 0x2c66b954U, 0x3da54ae8U, 0x260476b7U, 0x378b3c46U, 0xd8fd6a63U, 0x617c46c3U, 0x7de94644U, 0x316ed7e1U, 0x6dba70edU, 0x44ba02U,
  }
};

/* This object is used for KMS blob encryption                    */
#if defined(__GNUC__)
__attribute__((section(".SE_embedded_Keys")))
#endif
static const kms_obj_keyhead_24_t   KMS_Blob_AES_CBC128_Decrypt =
{
  KMS_ABI_VERSION_CK_2_40,         /*  uint32_t version; */
  KMS_ABI_CONFIG_KEYHEAD,          /*  uint32_t configuration; */
  96,                              /*  uint32_t blobs_size; */
  7,                               /*  uint32_t blobs_count; */
  2,                               /*  uint32_t object_id; */
  {
    CKA_CLASS,        sizeof(CK_OBJECT_CLASS), CKO_SECRET_KEY,
    CKA_KEY_TYPE,     sizeof(CK_KEY_TYPE),     CKK_AES,
    CKA_VALUE,        16, 0x4f454d5fU, 0x4b45595fU, 0x434f4d50U, 0x414e5931U,
    CKA_ENCRYPT,      sizeof(CK_BBOOL), CK_FALSE,
    CKA_COPYABLE,     sizeof(CK_BBOOL), CK_FALSE,
    CKA_EXTRACTABLE,  sizeof(CK_BBOOL), CK_FALSE,
    CKA_DERIVE,       sizeof(CK_BBOOL), CK_FALSE,
  }
};


#if (SECBOOT_CRYPTO_SCHEME == SECBOOT_AES128_GCM_AES128_GCM_AES128_GCM) || (SECBOOT_CRYPTO_SCHEME == SECBOOT_ECCDSA_WITH_AES128_CBC_SHA256)
#if defined(__GNUC__)
__attribute__((section(".SE_embedded_Keys")))
#endif
static const kms_obj_keyhead_24_t   SBSFU_AES_1_128 =
{
  KMS_ABI_VERSION_CK_2_40,         /*  uint32_t version; */
  KMS_ABI_CONFIG_KEYHEAD,          /*  uint32_t configuration; */
  96,                              /*  uint32_t blobs_size; */
  7,                               /*  uint32_t blobs_count; */
  3,                               /*  uint32_t object_id; */
  {
    CKA_CLASS,        sizeof(CK_OBJECT_CLASS), CKO_SECRET_KEY,
    CKA_KEY_TYPE,     sizeof(CK_KEY_TYPE),     CKK_AES,
    CKA_VALUE,        16, 0x4f454d5fU, 0x4b45595fU, 0x434f4d50U, 0x414e5931U,
    CKA_ENCRYPT,      sizeof(CK_BBOOL), CK_FALSE,
    CKA_COPYABLE,     sizeof(CK_BBOOL), CK_FALSE,
    CKA_EXTRACTABLE,  sizeof(CK_BBOOL), CK_FALSE,
    CKA_DERIVE,       sizeof(CK_BBOOL), CK_FALSE,
  }
};
#if (SFU_NB_MAX_ACTIVE_IMAGE > 1U)
#if defined(__GNUC__)
__attribute__((section(".SE_embedded_Keys")))
#endif
static const kms_obj_keyhead_24_t   SBSFU_AES_2_128 =
{
  KMS_ABI_VERSION_CK_2_40,         /*  uint32_t version; */
  KMS_ABI_CONFIG_KEYHEAD,          /*  uint32_t configuration; */
  96,                              /*  uint32_t blobs_size; */
  7,                               /*  uint32_t blobs_count; */
  4,                               /*  uint32_t object_id; */
  {
    CKA_CLASS,        sizeof(CK_OBJECT_CLASS), CKO_SECRET_KEY,
    CKA_KEY_TYPE,     sizeof(CK_KEY_TYPE),     CKK_AES,
    CKA_VALUE,        @AES_SBSFU_KEY_2@
    CKA_ENCRYPT,      sizeof(CK_BBOOL), CK_FALSE,
    CKA_COPYABLE,     sizeof(CK_BBOOL), CK_FALSE,
    CKA_EXTRACTABLE,  sizeof(CK_BBOOL), CK_FALSE,
    CKA_DERIVE,       sizeof(CK_BBOOL), CK_FALSE,
  }
};
#endif /*(SFU_NB_MAX_ACTIVE_IMAGE > 1U)*/

#if (SFU_NB_MAX_ACTIVE_IMAGE > 2U)
#if defined(__GNUC__)
__attribute__((section(".SE_embedded_Keys")))
#endif
static const kms_obj_keyhead_24_t   SBSFU_AES_3_128 =
{
  KMS_ABI_VERSION_CK_2_40,         /*  uint32_t version; */
  KMS_ABI_CONFIG_KEYHEAD,          /*  uint32_t configuration; */
  96,                              /*  uint32_t blobs_size; */
  7,                               /*  uint32_t blobs_count; */
  5,                               /*  uint32_t object_id; */
  {
    CKA_CLASS,        sizeof(CK_OBJECT_CLASS), CKO_SECRET_KEY,
    CKA_KEY_TYPE,     sizeof(CK_KEY_TYPE),     CKK_AES,
    CKA_VALUE,        @AES_SBSFU_KEY_3@
    CKA_ENCRYPT,      sizeof(CK_BBOOL), CK_FALSE,
    CKA_COPYABLE,     sizeof(CK_BBOOL), CK_FALSE,
    CKA_EXTRACTABLE,  sizeof(CK_BBOOL), CK_FALSE,
    CKA_DERIVE,       sizeof(CK_BBOOL), CK_FALSE,
  }
};
#endif /* (SFU_NB_MAX_ACTIVE_IMAGE > 2U) */
#endif /* (SECBOOT_CRYPTO_SCHEME == SECBOOT_AES128_GCM_AES128_GCM_AES128_GCM) || (SECBOOT_CRYPTO_SCHEME == SECBOOT_ECCDSA_WITH_AES128_CBC_SHA256) */

#if (SECBOOT_CRYPTO_SCHEME == SECBOOT_ECCDSA_WITH_AES128_CBC_SHA256) || (SECBOOT_CRYPTO_SCHEME == SECBOOT_ECCDSA_WITHOUT_ENCRYPT_SHA256)
#if defined(__GNUC__)
__attribute__((section(".SE_embedded_Keys")))
#endif
static const kms_obj_keyhead_30_t   SBSFU_ECDSA_1_Verify =
{
  KMS_ABI_VERSION_CK_2_40,         /*  uint32_t version; */
  KMS_ABI_CONFIG_KEYHEAD,          /*  uint32_t configuration; */
  120,                             /*  uint32_t blobs_size; */
  4,                               /*  uint32_t blobs_count; */
  6,                               /*  uint32_t object_id; */
  {
    CKA_CLASS,        sizeof(CK_OBJECT_CLASS), CKO_PUBLIC_KEY,
    CKA_KEY_TYPE,     sizeof(CK_KEY_TYPE),     CKK_EC,
    CKA_EC_PARAMS,    10, 0x06082a86U, 0x48ce3d03U, 0x0107U,   /* EC OIDs */
    CKA_EC_POINT,     67, 0x044104baU, 0xf297f83eU, 0xe307dc16U, 0xc371781dU, 0xf1b03ef0U, 0x95b04454U, 0x128148fbU, 0x2c66b954U, 0x3da54ae8U, 0x260476b7U, 0x378b3c46U, 0xd8fd6a63U, 0x617c46c3U, 0x7de94644U, 0x316ed7e1U, 0x6dba70edU, 0x44ba02U,
  }
};

#if (SFU_NB_MAX_ACTIVE_IMAGE > 1U)
#if defined(__GNUC__)
__attribute__((section(".SE_embedded_Keys")))
#endif
static const kms_obj_keyhead_30_t   SBSFU_ECDSA_2_Verify =
{
  KMS_ABI_VERSION_CK_2_40,         /*  uint32_t version; */
  KMS_ABI_CONFIG_KEYHEAD,          /*  uint32_t configuration; */
  120,                             /*  uint32_t blobs_size; */
  4,                               /*  uint32_t blobs_count; */
  7,                               /*  uint32_t object_id; */
  {
    CKA_CLASS,        sizeof(CK_OBJECT_CLASS), CKO_PUBLIC_KEY,
    CKA_KEY_TYPE,     sizeof(CK_KEY_TYPE),     CKK_EC,
    CKA_EC_PARAMS,    10, 0x06082a86U, 0x48ce3d03U, 0x0107U,   /* EC OIDs */
    CKA_EC_POINT,     @ECDSA_SBSFU_KEY_2@
  }
};
#endif /* (SFU_NB_MAX_ACTIVE_IMAGE > 1U) */

#if (SFU_NB_MAX_ACTIVE_IMAGE > 2U)
#if defined(__GNUC__)
__attribute__((section(".SE_embedded_Keys")))
#endif
static const kms_obj_keyhead_30_t   SBSFU_ECDSA_3_Verify =
{
  KMS_ABI_VERSION_CK_2_40,         /*  uint32_t version; */
  KMS_ABI_CONFIG_KEYHEAD,          /*  uint32_t configuration; */
  120,                             /*  uint32_t blobs_size; */
  4,                               /*  uint32_t blobs_count; */
  8,                               /*  uint32_t object_id; */
  {
    CKA_CLASS,        sizeof(CK_OBJECT_CLASS), CKO_PUBLIC_KEY,
    CKA_KEY_TYPE,     sizeof(CK_KEY_TYPE),     CKK_EC,
    CKA_EC_PARAMS,    10, 0x06082a86U, 0x48ce3d03U, 0x0107U,
    CKA_EC_POINT,     @ECDSA_SBSFU_KEY_3@
  }
};
#endif /* (SFU_NB_MAX_ACTIVE_IMAGE > 2U) */
#endif /* (SECBOOT_CRYPTO_SCHEME == SECBOOT_ECCDSA_WITH_AES128_CBC_SHA256) || (SECBOOT_CRYPTO_SCHEME == SECBOOT_ECCDSA_WITHOUT_ENCRYPT_SHA256) */

/* Stop placing data in specified section*/
#if defined(__ICCARM__)
#pragma default_variable_attributes =
#elif defined(__CC_ARM)
#pragma arm section code
#endif

#if defined(__ICCARM__)
#pragma default_variable_attributes = @ ".USER_embedded_Keys"
#elif defined(__CC_ARM)
#pragma arm section rodata = ".USER_embedded_Keys"
#endif

KMS_DECLARE_BLOB_STRUCT(, 21);
KMS_DECLARE_BLOB_STRUCT(, 27);
KMS_DECLARE_BLOB_STRUCT(, 29);

/* These objects are used by user tKMS application                 */
#if defined(__GNUC__)
#pragma GCC push_options
#pragma GCC optimize ("O0")
#endif
#if ( LORAMAC_CLASSB_ENABLED == 1 )
#if defined(__GNUC__)
__attribute__((section(".USER_embedded_Keys")))
#endif
static const kms_obj_keyhead_27_t   Lorawan_Zero_Key =
{
  KMS_ABI_VERSION_CK_2_40,         /*  uint32_t version; */
  KMS_ABI_CONFIG_KEYHEAD,          /*  uint32_t configuration; */
  108,                             /*  uint32_t blobs_size; */
  8,                               /*  uint32_t blobs_count; */
  13,                              /*  uint32_t object_id; */
  {
    CKA_CLASS,        sizeof(CK_OBJECT_CLASS), (uint8_t)CKO_SECRET_KEY,
    CKA_KEY_TYPE,     sizeof(CK_KEY_TYPE),     CKK_AES,
    CKA_VALUE,        16UL,                    0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U,
    CKA_DERIVE,       sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_DECRYPT,      sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_COPYABLE,     sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_EXTRACTABLE,  sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_LABEL,        4UL,                     0x5F45524CU /* 'LRE_' */
  }
};
#endif /* LORAMAC_CLASSB_ENABLED == 1 */

#if defined(__GNUC__)
__attribute__((section(".USER_embedded_Keys")))
#endif
static const kms_obj_keyhead_27_t   Lorawan_App_Key =
{
  KMS_ABI_VERSION_CK_2_40,         /*  uint32_t version; */
  KMS_ABI_CONFIG_KEYHEAD,          /*  uint32_t configuration; */
  108,                             /*  uint32_t blobs_size; */
  8,                               /*  uint32_t blobs_count; */
  14,                              /*  uint32_t object_id; */
  {
    CKA_CLASS,        sizeof(CK_OBJECT_CLASS), (uint8_t)CKO_SECRET_KEY,
    CKA_KEY_TYPE,     sizeof(CK_KEY_TYPE),     CKK_AES,
    CKA_VALUE,        16UL,                    FORMAT_KEY_32(LORAWAN_APP_KEY),
    CKA_ENCRYPT,      sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_DECRYPT,      sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_COPYABLE,     sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
#if (!defined (KEY_EXTRACTABLE) || (KEY_EXTRACTABLE == 0))
    CKA_EXTRACTABLE,  sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
#else
    CKA_EXTRACTABLE,  sizeof(CK_BBOOL),        (uint8_t)CK_TRUE,
#endif /* KEY_EXTRACTABLE */
    CKA_LABEL,        4UL,                     0x5F45524CU /* 'LRE_' */
  }
};

#if defined(__GNUC__)
__attribute__((section(".USER_embedded_Keys")))
#endif
static const kms_obj_keyhead_27_t   Lorawan_Nwk_Key =
{
  KMS_ABI_VERSION_CK_2_40,         /*  uint32_t version; */
  KMS_ABI_CONFIG_KEYHEAD,          /*  uint32_t configuration; */
  108,                             /*  uint32_t blobs_size; */
  8,                               /*  uint32_t blobs_count; */
  15,                              /*  uint32_t object_id; */
  {
    CKA_CLASS,        sizeof(CK_OBJECT_CLASS), (uint8_t)CKO_SECRET_KEY,
    CKA_KEY_TYPE,     sizeof(CK_KEY_TYPE),     CKK_AES,
    CKA_VALUE,        16UL,                    FORMAT_KEY_32(LORAWAN_NWK_KEY),
    CKA_ENCRYPT,      sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_DECRYPT,      sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_COPYABLE,     sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
#if (!defined (KEY_EXTRACTABLE) || (KEY_EXTRACTABLE == 0))
    CKA_EXTRACTABLE,  sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
#else
    CKA_EXTRACTABLE,  sizeof(CK_BBOOL),        (uint8_t)CK_TRUE,
#endif /* KEY_EXTRACTABLE */
    CKA_LABEL,        4UL,                     0x5F45524CU /* 'LRE_' */
  }
};

#if defined(__GNUC__)
__attribute__((section(".USER_embedded_Keys")))
#endif
static const kms_obj_keyhead_29_t   Lorawan_DevJoinEuiAddr_Key =
{
  KMS_ABI_VERSION_CK_2_40,         /*  uint32_t version; */
  KMS_ABI_CONFIG_KEYHEAD,          /*  uint32_t configuration; */
  116,                             /*  uint32_t blobs_size; */
  8,                               /*  uint32_t blobs_count; */
  16,                              /*  uint32_t object_id; */
  {
    CKA_CLASS,        sizeof(CK_OBJECT_CLASS), (uint8_t)CKO_SECRET_KEY,
    CKA_KEY_TYPE,     sizeof(CK_KEY_TYPE),     CKK_AES,
    CKA_VALUE,        24UL,                    FORMAT_DEVJOINKEY(LORAWAN_DEVICE_EUI,LORAWAN_JOIN_EUI,LORAWAN_DEVICE_ADDRESS,LORAWAN_DEVICE_ADDRESS),
    CKA_ENCRYPT,      sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_DECRYPT,      sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_COPYABLE,     sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
    CKA_EXTRACTABLE,  sizeof(CK_BBOOL),        (uint8_t)CK_TRUE,
    CKA_LABEL,        4UL,                     0x5F45524CU /* 'LRE_' */
  }
};

#if defined(__GNUC__)
__attribute__((section(".USER_embedded_Keys")))
#endif
static const kms_obj_keyhead_21_t   Lorawan_Nwk_S_Key =
{
  KMS_ABI_VERSION_CK_2_40,         /*  uint32_t version; */
  KMS_ABI_CONFIG_KEYHEAD,          /*  uint32_t configuration; */
  84,                              /*  uint32_t blobs_size; */
  6,                               /*  uint32_t blobs_count; */
  17,                              /*  uint32_t object_id; */
  {
    CKA_CLASS,        sizeof(CK_OBJECT_CLASS), (uint8_t)CKO_SECRET_KEY,
    CKA_KEY_TYPE,     sizeof(CK_KEY_TYPE),     CKK_AES,
    CKA_VALUE,        16UL,                    FORMAT_KEY_32(LORAWAN_NWK_S_KEY),
    CKA_COPYABLE,     sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
#if (!defined (KEY_EXTRACTABLE) || (KEY_EXTRACTABLE == 0))
    CKA_EXTRACTABLE,  sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
#else
    CKA_EXTRACTABLE,  sizeof(CK_BBOOL),        (uint8_t)CK_TRUE,
#endif /* KEY_EXTRACTABLE */
    CKA_LABEL,        4UL,                     0x5F45524CU /* 'LRE_' */
  }
};

#if defined(__GNUC__)
__attribute__((section(".USER_embedded_Keys")))
#endif
static const kms_obj_keyhead_21_t   Lorawan_App_S_Key =
{
  KMS_ABI_VERSION_CK_2_40,         /*  uint32_t version; */
  KMS_ABI_CONFIG_KEYHEAD,          /*  uint32_t configuration; */
  84,                              /*  uint32_t blobs_size; */
  6,                               /*  uint32_t blobs_count; */
  18,                              /*  uint32_t object_id; */
  {
    CKA_CLASS,        sizeof(CK_OBJECT_CLASS), (uint8_t)CKO_SECRET_KEY,
    CKA_KEY_TYPE,     sizeof(CK_KEY_TYPE),     CKK_AES,
    CKA_VALUE,        16UL,                    FORMAT_KEY_32(LORAWAN_APP_S_KEY),
    CKA_COPYABLE,     sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
#if (!defined (KEY_EXTRACTABLE) || (KEY_EXTRACTABLE == 0))
    CKA_EXTRACTABLE,  sizeof(CK_BBOOL),        (uint8_t)CK_FALSE,
#else
    CKA_EXTRACTABLE,  sizeof(CK_BBOOL),        (uint8_t)CK_TRUE,
#endif /* KEY_EXTRACTABLE */
    CKA_LABEL,        4UL,                     0x5F45524CU /* 'LRE_' */
  }
};
#if defined(__ICCARM__)
#pragma default_variable_attributes =
#elif defined(__CC_ARM)
#pragma arm section code
#elif defined(__GNUC__)
#pragma GCC pop_options
#endif

/**
  * @brief  KMS embedded objects definition
  * @note   Must contains KMS blob verification and decryption keys
  */
static const kms_obj_keyhead_t *const KMS_PlatfObjects_EmbeddedList[KMS_INDEX_MAX_EMBEDDED_OBJECTS -
                                                                    KMS_INDEX_MIN_EMBEDDED_OBJECTS + 1] =
{
#if defined(KMS_IMPORT_BLOB)
  /* KMS Blob import keys */
  (kms_obj_keyhead_t *)(uint32_t) &KMS_Blob_ECDSA_Verify,       /* Index = 1 */
  (kms_obj_keyhead_t *)(uint32_t) &KMS_Blob_AES_CBC128_Decrypt, /* Index = 2 */
#else
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 1 */
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 2 */
#endif /* KMS_IMPORT_BLOB */
  /* SBSFU keys */
#if (SECBOOT_CRYPTO_SCHEME == SECBOOT_AES128_GCM_AES128_GCM_AES128_GCM) || (SECBOOT_CRYPTO_SCHEME == SECBOOT_ECCDSA_WITH_AES128_CBC_SHA256)
  (kms_obj_keyhead_t *)(uint32_t) &SBSFU_AES_1_128,             /* Index = 3 */
#if (SFU_NB_MAX_ACTIVE_IMAGE > 1U)
  (kms_obj_keyhead_t *)(uint32_t) &SBSFU_AES_2_128,             /* Index = 4 */
#else
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 4 */
#endif /* (SFU_NB_MAX_ACTIVE_IMAGE > 1U) */
#if (SFU_NB_MAX_ACTIVE_IMAGE > 2U)
  (kms_obj_keyhead_t *)(uint32_t) &SBSFU_AES_3_128,             /* Index = 5 */
#else
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 5 */
#endif /* (SFU_NB_MAX_ACTIVE_IMAGE > 2U) */
#else /* (SECBOOT_CRYPTO_SCHEME == SECBOOT_AES128_GCM_AES128_GCM_AES128_GCM) || (SECBOOT_CRYPTO_SCHEME == SECBOOT_ECCDSA_WITH_AES128_CBC_SHA256) */
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 3 */
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 4 */
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 5 */
#endif /* (SECBOOT_CRYPTO_SCHEME == SECBOOT_AES128_GCM_AES128_GCM_AES128_GCM) || (SECBOOT_CRYPTO_SCHEME == SECBOOT_ECCDSA_WITH_AES128_CBC_SHA256) */

#if (SECBOOT_CRYPTO_SCHEME == SECBOOT_ECCDSA_WITH_AES128_CBC_SHA256) || (SECBOOT_CRYPTO_SCHEME == SECBOOT_ECCDSA_WITHOUT_ENCRYPT_SHA256)
  (kms_obj_keyhead_t *)(uint32_t) &SBSFU_ECDSA_1_Verify,        /* Index = 6 */
#if (SFU_NB_MAX_ACTIVE_IMAGE > 1U)
  (kms_obj_keyhead_t *)(uint32_t) &SBSFU_ECDSA_2_Verify,        /* Index = 7 */
#else
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 7 */
#endif /* (SFU_NB_MAX_ACTIVE_IMAGE > 1U) */
#if (SFU_NB_MAX_ACTIVE_IMAGE > 2U)
  (kms_obj_keyhead_t *)(uint32_t) &SBSFU_ECDSA_3_Verify,        /* Index = 8 */
#else
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 8 */
#endif /* (SFU_NB_MAX_ACTIVE_IMAGE > 2U) */
#else /* (SECBOOT_CRYPTO_SCHEME == SECBOOT_ECCDSA_WITH_AES128_CBC_SHA256) || (SECBOOT_CRYPTO_SCHEME == SECBOOT_ECCDSA_WITHOUT_ENCRYPT_SHA256) */
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 6 */
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 7 */
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 8 */
#endif /* (SECBOOT_CRYPTO_SCHEME == SECBOOT_ECCDSA_WITH_AES128_CBC_SHA256) || (SECBOOT_CRYPTO_SCHEME == SECBOOT_ECCDSA_WITHOUT_ENCRYPT_SHA256) */
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 9 */
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 10 */
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 11 */
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 12 */
  /* UserApp example keys */
#if ( LORAMAC_CLASSB_ENABLED == 1 )
  (kms_obj_keyhead_t *) &Lorawan_Zero_Key,                      /* Index = 13 */
#else
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 13 */
#endif /* LORAMAC_CLASSB_ENABLED == 1 */
  (kms_obj_keyhead_t *) &Lorawan_App_Key,                       /* Index = 14 */
  (kms_obj_keyhead_t *) &Lorawan_Nwk_Key,                       /* Index = 15 */
  (kms_obj_keyhead_t *) &Lorawan_DevJoinEuiAddr_Key,            /* Index = 16 */
  (kms_obj_keyhead_t *) &Lorawan_Nwk_S_Key,                     /* Index = 17 */
  (kms_obj_keyhead_t *) &Lorawan_App_S_Key,                     /* Index = 18 */
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 19 */
  (kms_obj_keyhead_t *) NULL,                                   /* Index = 20 */
};

/**
  * @}
  */
#endif /* KMS_PLATF_OBJECTS_C */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* KMS_PLATF_OBJECTS_CONFIG_H */
