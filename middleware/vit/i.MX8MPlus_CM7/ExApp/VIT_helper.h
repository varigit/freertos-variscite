/*
* Copyright 2020-2021 NXP
*
* NXP Confidential. This software is owned or controlled by NXP and may only
* be used strictly in accordance with the applicable license terms found in
* file LICENSE.txt
*/

#ifndef VIT_HELPER_H
#define VIT_HELPER_H
#include "PL_platformTypes_CortexM.h"
#include "VIT.h"

void VIT_SetupMemoryRegion(PL_MemoryTable_st *memorytable);

int VIT_Print_Error(VIT_ReturnStatus_en  status, const char * f);

#define CHECK(STATUS, F) \
    do { if (VIT_Print_Error((STATUS), (F)) == -1) \
        goto error;\
    } while(0)


#endif
