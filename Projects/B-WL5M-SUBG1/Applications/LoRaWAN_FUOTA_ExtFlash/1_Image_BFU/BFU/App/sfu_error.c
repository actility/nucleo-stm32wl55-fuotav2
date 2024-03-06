/**
  ******************************************************************************
  * @file    sfu_error.c
  * @author  MCD Application Team
  * @brief   SFU ERROR
  *          This file provides set of firmware functions for SB_SFU errors handling.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in
  * the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "sfu_fsm_states.h"
#include "sfu_error.h"
#include "sfu_low_level_security.h"
#include "sfu_trace.h"
#include "se_interface_bootloader.h"
#include "sfu_fwimg_services.h"
#include "sfu_boot.h"
#include "sfu_test.h"


/* Private variables ---------------------------------------------------------*/
#ifdef SFU_DEBUG_MODE
/**
  *  The following strings associated to the exceptions/errors are used for debugging purpose.
  *  WARNING: The string array must match perfectly with the @ref SFU_EXCPT_IdTypeDef.
  *  And the @ref SFU_EXCPT_IdTypeDef enum must be a sequence starting from 0
  */
static char *m_aErrorStrings[] ={  "No error. Success",
                                   "Memory fault",
                                   "Hard fault",
                                   "Tampering fault",
                                   "SE lock cannot be set",
#if (SECBOOT_LOADER == SECBOOT_USE_LOCAL_LOADER)
                                   "Fw too big",
                                   "File not correctly received",
#endif /* (SECBOOT_LOADER == SECBOOT_USE_LOCAL_LOADER) */
                                   "Fw header authentication error",
                                   "Fw decryption error",
                                   "Fw signature check error",
                                   "Flash error",
                                   "External flash configuration error.",
                                   "Header erasing error",
                                   "Header validation error",
                                   "Additional code detected beyond FW",
                                   "Error during swap process",
                                   "Error during rollback process",
                                   "Backed-up fw not identified",
                                   "Backup copy error",
                                   "Dwl slot erasing error",
                                   "Trailer erasing error",
                                   "Trailer update error",
                                   "Magic tag update error",
                                   "Fw version rejected (anti-rollback)",
                                   "Unknown error"
                                };

#endif /* SFU_DEBUG_MODE */

/* Private function prototypes -----------------------------------------------*/
static void SFU_EXCPT_RuntimeExceptionHandler(SFU_EXCPT_IdTypeDef eExceptionId);

/* Functions Definition ------------------------------------------------------*/
/**
  * @brief  Print relevant errpr message.
  * @param  Error Error code.
  * @retval None
  */
void SFU_EXCPT_SetError(SFU_EXCPT_IdTypeDef eExceptionId)
{
  if (eExceptionId <= SFU_EXCPT_UNKNOWN)
  {
#ifdef SFU_DEBUG_MODE
    TRACE("\r\n\t%s",m_aErrorStrings[(uint32_t) eExceptionId]);
#endif /* SFU_DEBUG_MODE */
  }
}


/**
  * @brief  Manage the Exception generated by an IRQ
  * @param  eExceptionId : Exception ID.
  *         This parameter can be a value of @ref SFU_EXCPT_ID_Structure_definition.
  * @note   Because of the interruption of the State Machine execution,
  *         it's not possible to continue without compromising the stability or
  *         the security of the solution. A System Reset is forced at the end.
  * @retval None
  */
void SFU_EXCPT_IrqExceptionHandler(SFU_EXCPT_IdTypeDef eExceptionId)
{
#ifdef SFU_DEBUG_MODE
  uint8_t message[150];
  uint32_t i = 0U;

  /* Avoid warning with cast frombetween char* and uint8_t* */
  while ((m_aErrorStrings[(uint32_t) eExceptionId][i] != 0u) && (i < 149U))
  {
    message[i] = m_aErrorStrings[(uint32_t) eExceptionId][i];
    i++;
  }
  message[i] = 0U;

  /* Print relevant error message */
  TRACE_IRQ((uint8_t *)"\r\n\t  ");
  TRACE_IRQ(message);
#endif /* SFU_DEBUG_MODE */

  /* Try to take an action */
  SFU_EXCPT_RuntimeExceptionHandler(eExceptionId);

  /* It's not possible to continue without compromising the stability or the security of the solution.
  The State Machine needs to be aborted and a Reset must be triggered */
  SFU_BOOT_ForceReboot();
}

/**
  * @brief  Stop in case of security error
  * @param  eExceptionId : Exception ID.
  *         This parameter can be a value of @ref SFU_EXCPT_ID_Structure_definition.
  * @retval SFU_ErrorStatus SFU_SUCCESS if successful, SFU_ERROR otherwise.
  */

void SFU_EXCPT_Security_Error(void)
{
  TRACE("\r\n= [SBOOT] Security issue : execution stopped !");
  HAL_Delay(1000);
  /* This is the last operation executed. Force a System Reset. */
  NVIC_SystemReset();
}

/**
  * @brief  SFU Exception Initialization.
  * @param  None.
  * @retval SFU_ErrorStatus SFU_SUCCESS if successful, SFU_ERROR otherwise.
  */
SFU_ErrorStatus SFU_EXCPT_Init(void)
{
  SFU_ErrorStatus e_ret_status;

  /* ADD SRC CODE HERE
       ...
  */
  e_ret_status = SFU_SUCCESS;

  return e_ret_status;
}

/**
  * @brief  SFU Exception DeInitialization.
  * @param  None.
  * @retval SFU_ErrorStatus SFU_SUCCESS if successful, SFU_ERROR otherwise.
  */
SFU_ErrorStatus SFU_EXCPT_DeInit(void)
{
  SFU_ErrorStatus e_ret_status;
  /* ADD SRC CODE HERE
      ...
  */
  e_ret_status = SFU_SUCCESS;

  return e_ret_status;
}

/**
  * @brief  Manage the Exception/Errors/Fault at runtime, when detected
  * @param  eExceptionId : Exception ID.
  *         This parameter can be a value of @ref SFU_EXCPT_ID_Structure_definition.
  * @note   A System Reset is forced at the end by the caller of this function.
  *         WARNING: Be aware that this function can be called by an IRQ while
  *         using the printf, since the printf is not a reentrant function, and using
  *         the printf inside this function as well, a fault will likely occur.
  * @retval SFU_ErrorStatus SFU_SUCCESS if successful, SFU_ERROR otherwise.
  */
static void SFU_EXCPT_RuntimeExceptionHandler(SFU_EXCPT_IdTypeDef eExceptionId)
{
  switch (eExceptionId)
  {
    case SFU_EXCPT_TAMPERING_FAULT:
      /* WARNING: This might be generated by an attempted attack, a bug or your code!
         Add your code here in order to implement a custom action for this event,
         e.g. trigger a mass erase or take any other action in order to
         protect your system.
         ...
         ...
      */
      break;

    case SFU_EXCPT_MEMORY_FAULT:
      /* WARNING: This might be generated by an attempted attack, a bug or your code!
         Add your code here in order to implement a custom action for this event,
         e.g. trigger a mass erase or take any other action in order to
         protect your system.
         ...
         ...
      */
      break;

    case SFU_EXCPT_HARD_FAULT:
      /* WARNING: This might be generated by an attempted attack, a bug or your code!
         Add your code here in order to implement a custom action for this event,
         e.g. trigger a mass erase or take any other action in order to
         protect your system.
         ...
         ...
      */
#ifdef SFU_TEST_PROTECTION
      /* On STM32WLXX : Hard fault IT is generated instead of memory fault when MPU accessed
         ==> this is not an error */
#endif /* SFU_TEST_PROTECTION */
      break;

    default:
      /* WARNING: This might be generated by an attempted attack, a bug or your code!
         Add your code here in order to implement a custom action for this event,
         e.g. trigger a mass erase or take any other  action in order to
         protect your system.
         ...
         ...
      */
      break;
  }

}
