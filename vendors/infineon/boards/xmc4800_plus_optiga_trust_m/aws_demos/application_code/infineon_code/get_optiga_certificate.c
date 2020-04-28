/*
 * FreeRTOS V202002.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */


/**
 * @file get_optiga_certificate.c
 * @brief Get the per-provisioned certificate from your SE using PKCS #11
 *
 * A simple example to extract pre-provisioned certificate from the chip and print it out
 */

/* Standard includes. */
#include <stdio.h>
#include <string.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* PKCS#11 includes. */
#include "iot_pkcs11_config.h"
#include "iot_pkcs11.h"
#include "iot_logging_task.h"

/* Client credential includes. */
#include "aws_clientcredential.h"
#include "aws_clientcredential_keys.h"
#include "iot_default_root_certificates.h"

/* Cert extraction include. */
#include "get_optiga_certificate.h"

/* Utilities include. */
#include "iot_pki_utils.h"

/* mbedTLS includes. */
#include "mbedtls/base64.h"

/* Default FreeRTOS API for console logging. */
#define GET_OPTIGA_CERTIFICATE_PRINT( X )    vLoggingPrintf X




static CK_RV prvGetCertificateHandle( CK_FUNCTION_LIST_PTR pxFunctionList,
                                      CK_SESSION_HANDLE xSession,
                                      const char * pcLabelName,
                                      CK_OBJECT_HANDLE_PTR pxCertHandle );


static CK_RV prvGetCertificateHandle( CK_FUNCTION_LIST_PTR pxFunctionList,
                                      CK_SESSION_HANDLE xSession,
                                      const char * pcLabelName,
                                      CK_OBJECT_HANDLE_PTR pxCertHandle )
{
    CK_ATTRIBUTE xTemplate;
    CK_RV xResult = CKR_OK;
    CK_ULONG ulCount = 0;
    CK_BBOOL xFindInit = CK_FALSE;

    /* Get the certificate handle. */
    if( 0 == xResult )
    {
        xTemplate.type = CKA_LABEL;
        xTemplate.ulValueLen = strlen( pcLabelName ) + 1;
        xTemplate.pValue = ( char * ) pcLabelName;
        xResult = pxFunctionList->C_FindObjectsInit( xSession, &xTemplate, 1 );
    }

    if( 0 == xResult )
    {
        xFindInit = CK_TRUE;
        xResult = pxFunctionList->C_FindObjects( xSession,
                                                 ( CK_OBJECT_HANDLE_PTR ) pxCertHandle,
                                                 1,
                                                 &ulCount );
    }

    if( CK_TRUE == xFindInit )
    {
        xResult = pxFunctionList->C_FindObjectsFinal( xSession );
    }

    return xResult;
}

/*-----------------------------------------------------------*/

/* Attempt to extract the certificate out of the default certificate slot and convert it to PEM */
CK_RV xExtractOptigaCertificate( CK_SESSION_HANDLE xSession,
								 CK_BYTE_PTR * ppucCertificate,
								 CK_ULONG * pulCertificateLength )
{
    CK_RV xResult;
    CK_FUNCTION_LIST_PTR pxFunctionList;
    CK_OBJECT_HANDLE xHandle = 0;
    CK_ATTRIBUTE xTemplate = { 0 };
    CK_ULONG xCount = 1;
    CK_BYTE_PTR pucCert = NULL;

    xResult = C_GetFunctionList( &pxFunctionList );

    if( CKR_OK == xResult )
	{
		xResult = prvGetCertificateHandle( pxFunctionList, xSession, pkcs11configLABEL_DEVICE_CERTIFICATE_FOR_TLS, &xHandle );
	}

    if( ( xHandle != 0 ) && ( xResult == CKR_OK ) ) /* 0 is an invalid handle */
	{
		/* Get the length of the certificate */
		xTemplate.type = CKA_VALUE;
		xTemplate.pValue = NULL;
		xResult = pxFunctionList->C_GetAttributeValue( xSession, xHandle, &xTemplate, xCount );

		if( xResult == CKR_OK )
		{
			pucCert = pvPortMalloc( xTemplate.ulValueLen );
		}

		if( ( xResult == CKR_OK ) && ( pucCert == NULL ) )
		{
			xResult = CKR_HOST_MEMORY;
		}

		if( xResult == CKR_OK )
		{
			xTemplate.pValue = pucCert;
			xResult = pxFunctionList->C_GetAttributeValue( xSession, xHandle, &xTemplate, xCount );

			if( xResult == CKR_OK )
			{
				*ppucCertificate = pucCert;
				*pulCertificateLength = xTemplate.ulValueLen;
			}
			else
			{
				vPortFree( pucCert );
			}
		}
	}
	else /* Certificate was not found. */
	{
		*ppucCertificate = NULL;
		*pulCertificateLength = 0;
	}


    return xResult;
}

CK_RV xDerToPemAndPrint( CK_BYTE_PTR pDerCertificate, CK_ULONG ulDerCertificateLength )
{
	CK_RV xResult = CKR_OK;
	CK_BYTE_PTR pPemCertificate;
	CK_ULONG ulPemCertificateLength = 1124;
	CK_ULONG ulReadOffset = 0;

	if ( 0 != ulDerCertificateLength )
	{

		pPemCertificate = pvPortMalloc( ulPemCertificateLength );

		if( ( xResult == CKR_OK ) && ( pPemCertificate == NULL ) )
		{
			xResult = CKR_HOST_MEMORY;
		}
		else
		{

			mbedtls_base64_encode(pPemCertificate, ulPemCertificateLength,
											(size_t *)&ulPemCertificateLength,
											pDerCertificate, ulDerCertificateLength);

			printf("-----BEGIN CERTIFICATE-----\n");
			//Properly copy certificate and format it as pkcs expects
			for (ulReadOffset = 0; ulReadOffset < ulPemCertificateLength; ulReadOffset += 64)
			{

				printf("%.64s\n",pPemCertificate + ulReadOffset);
			}
			ulReadOffset-=64;
			printf("%.64", pPemCertificate + ulReadOffset);
			printf("-----END CERTIFICATE-----\n");
		}
	}


	return xResult;
}


/*-----------------------------------------------------------*/

/* Perform PKCS#1 initialisation and certificate extraction */
CK_RV vGetOptigaCertificate( void )
{
    CK_RV xResult = CKR_OK;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SESSION_HANDLE xSession = 0;
    CK_BYTE_PTR pCertificate;
	CK_ULONG ulCertificateLength;

    xResult = C_GetFunctionList( &pxFunctionList );

    /* Initialize the PKCS Module */
    if( xResult == CKR_OK )
    {
        xResult = xInitializePkcs11Token();
    }

    if( xResult == CKR_OK )
    {
        xResult = xInitializePkcs11Session( &xSession );
    }

    if( xResult == CKR_OK )
    {
        xResult = xExtractOptigaCertificate( xSession, &pCertificate, &ulCertificateLength);

        xResult = xDerToPemAndPrint( pCertificate, ulCertificateLength );

        pxFunctionList->C_CloseSession( xSession );
    }

    return xResult;
}

