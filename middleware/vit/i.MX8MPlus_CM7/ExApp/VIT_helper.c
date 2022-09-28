/*
* Copyright 2020-2021 NXP
*
* NXP Confidential. This software is owned or controlled by NXP and may only
* be used strictly in accordance with the applicable license terms found in
* file LICENSE.txt
*/

#include "VIT_helper.h"
#include "fsl_debug_console.h"

                                           //  use for leakage detection
static PL_INT8    *pMemory[PL_NR_MEMORY_REGIONS];
static PL_INT8    *pMemoryBefore[PL_NR_MEMORY_REGIONS];
static PL_INT8    *pMemoryAfter[PL_NR_MEMORY_REGIONS];

void VIT_SetupMemoryRegion(PL_MemoryTable_st *memorytable)
{
    PL_UINT32               i;
    for (i = 0; i < PL_NR_MEMORY_REGIONS; i++)
    {
        /* Log the memory size */
        PRINTF("Memory region %d, size %d in Bytes, %.2f kBytes \r\n",
                (int)i,
                (int)memorytable->Region[i].Size,
                (float)memorytable->Region[i].Size/1024);

        if (memorytable->Region[i].Size != 0)
        {
            // reserve memory space for Size + MEMORY_LEAK_SIZE
            pMemory[i] = malloc(memorytable->Region[i].Size);
            // Place the memory space pointer used by the code in
            // the midle of the memory region reserved
            memorytable->Region[i].pBaseAddress =
                (void *)(pMemory[i]);

            // fill the unused memory with 0x55 value for leakage detection
            pMemoryBefore[i] = (PL_INT8 *)pMemory[i];
            pMemoryAfter[i] = (PL_INT8 *)memorytable->Region[i].pBaseAddress +
                memorytable->Region[i].Size;
            PRINTF(" Memory region address 0x%p\r\n",
                    memorytable->Region[i].pBaseAddress);
        }
    }
}


int VIT_Print_Error(VIT_ReturnStatus_en  status, const char * f)
{
    switch (status)
    {
        case VIT_SUCCESS:
            return 0;
            break;
        case VIT_INVALID_BUFFER_MEMORY_ALIGNMENT:
            PRINTF("%s: %s\r\n",f, "VIT_INVALID_BUFFER_MEMORY_ALIGNMENT");
            break;
        case VIT_INVALID_NULLADDRESS:
            PRINTF("%s: %s\r\n",f, "VIT_INVALID_NULLADDRESS");
            break;
        case VIT_INVALID_ARGUMENT:
            PRINTF("%s: %s\r\n",f, "VIT_INVALID_ARGUMENT");
            break;
        case VIT_INVALID_PARAMETER_OUTOFRANGE:
            PRINTF("%s: %s\r\n",f, "VIT_INVALID_PARAMETER_OUTOFRANGE");
            break;
        case VIT_INVALID_SAMPLE_RATE:
            PRINTF("%s: %s\r\n",f, "VIT_INVALID_SAMPLE_RATE");
            break;
        case VIT_INVALID_FRAME_SIZE:
            PRINTF("%s: %s\r\n",f, "VIT_INVALID_FRAME_SIZE");
            break;
        case VIT_INVALID_MODEL:
            PRINTF("%s: %s\r\n",f, "VIT_INVALID_MODEL");
            break;
        case VIT_INVALID_AFE_CONFIG:
            PRINTF("%s: %s\r\n",f, "VIT_INVALID_AFE_CONFIG");
            break;
        case VIT_INVALID_STATE:
            PRINTF("%s: %s\r\n",f, "VIT_INVALID_STATE");
            break;
        case VIT_INVALID_DEVICE:
            PRINTF("%s: %s\r\n",f, "VIT_INVALID_DEVICE");
            break;
        case VIT_SYSTEM_ERROR:
            PRINTF("%s: %s\r\n",f, "VIT_SYSTEM_ERROR");
            break;
        case VIT_ERROR_UNDEFINED:
            PRINTF("%s: %s\r\n",f, "VIT_ERROR_UNDEFINED");
            break;
       case VIT_DUMMY_ERROR:
            PRINTF("%s: %s\r\n",f, "VIT_DUMMY_ERROR");
            break;
    }
    return -1;
}


