/**
  ******************************************************************************
  * @file    PKA/PKA_ModularExponentiationCRT/Src/ciphertext.c
  * @author  MCD Application Team
  * @brief   This file reflect the content of ciphertext.bin.
  *          It has been created using xxd external tool in version V1.10 27oct98.
  *          Command line: 
  *            xxd -i ciphertext.bin
  *          Additional modification for easier usage:
  *           Replaced unsigned char by const uint8_t
  *           Replaced unsigned int by const uin32_t
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/*
This file reflect the content of ciphertext.bin

ciphertext.bin has been created using openssl 1.0.2k  26 Jan 2017:
  openssl rsautl -pubin -raw -inkey rsa_pub_2048.pem -encrypt -in plaintext.bin -out ciphertext.bin
*/

const uint8_t ciphertext_bin[] = {
  0x2e, 0x38, 0x2e, 0x62, 0x58, 0xce, 0x80, 0x3e, 0x16, 0x73, 0x53, 0xce,
  0x36, 0x4b, 0x0d, 0x8b, 0xe1, 0xd9, 0x68, 0xbb, 0x8c, 0x69, 0x13, 0xfc,
  0x9e, 0x5e, 0x43, 0x56, 0x21, 0xb1, 0x32, 0xf5, 0xb1, 0x9e, 0xb2, 0xad,
  0xf5, 0xc4, 0x2e, 0x14, 0xfc, 0x94, 0xfc, 0x6a, 0x4b, 0xb1, 0x41, 0x10,
  0x23, 0x3b, 0x6b, 0x21, 0x09, 0xa0, 0xf3, 0xfc, 0x04, 0x8d, 0x1b, 0x89,
  0x8d, 0x88, 0xdc, 0xd6, 0xe4, 0xf0, 0xa6, 0xe0, 0x85, 0xeb, 0x71, 0x8f,
  0xdc, 0x18, 0xa1, 0xc0, 0x9d, 0xe9, 0xa3, 0x67, 0xd0, 0x61, 0x69, 0xfd,
  0x82, 0xdd, 0x26, 0xc1, 0xfe, 0x7f, 0x85, 0xea, 0x64, 0x79, 0xc9, 0xbd,
  0x40, 0x74, 0xb7, 0x0b, 0x02, 0x67, 0xf4, 0x50, 0x60, 0x01, 0xa1, 0x47,
  0x19, 0xd8, 0x18, 0x92, 0xe0, 0xb0, 0xe4, 0xac, 0xea, 0x86, 0xcc, 0x85,
  0x71, 0xdc, 0xa4, 0x40, 0x1e, 0xd5, 0x5b, 0x99, 0x27, 0x64, 0x45, 0x8e,
  0xcd, 0xdf, 0x0b, 0x52, 0xa4, 0x1f, 0xaa, 0x78, 0xe4, 0x6d, 0xb9, 0x42,
  0x36, 0x2d, 0x9a, 0x38, 0xc5, 0xf9, 0xbf, 0xfe, 0xdc, 0x96, 0x96, 0xd1,
  0x3b, 0x3b, 0x97, 0xef, 0x83, 0x64, 0x72, 0x35, 0x3f, 0x0c, 0x65, 0x1d,
  0xac, 0x2d, 0xed, 0x95, 0x03, 0xa0, 0xfc, 0xbd, 0x44, 0x09, 0x14, 0x4c,
  0xb5, 0x6a, 0xb0, 0x36, 0xf4, 0xef, 0xd4, 0x52, 0xbc, 0xc5, 0x57, 0xcf,
  0x21, 0x98, 0x4d, 0x67, 0x9f, 0xc9, 0x62, 0x01, 0xa8, 0xf1, 0x9b, 0xe5,
  0x65, 0x18, 0x06, 0xa0, 0xdf, 0x7d, 0xab, 0x4b, 0x4a, 0x73, 0x71, 0x22,
  0xe1, 0xb9, 0x7f, 0xd1, 0x67, 0x5f, 0x4f, 0xa6, 0x6c, 0x58, 0xe8, 0x4b,
  0xb2, 0xcf, 0x18, 0x7d, 0x2e, 0xd8, 0xcc, 0xa1, 0xae, 0xc9, 0x0d, 0xba,
  0xe0, 0xbf, 0x2c, 0x4e, 0x48, 0xfc, 0x09, 0x92, 0xe1, 0x17, 0x04, 0x92,
  0x85, 0xeb, 0xae, 0x23
};
const uint32_t ciphertext_bin_len = 256;