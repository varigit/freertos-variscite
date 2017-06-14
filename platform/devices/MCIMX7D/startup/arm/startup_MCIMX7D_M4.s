; * ---------------------------------------------------------------------------------------
; *  @file:    startup_MCIMX7D_M4.s
; *  @purpose: CMSIS Cortex-M4 Core Device Startup File
; *            MCIMX7D_M4
; *  @version: 1.0
; *  @date:    2015-5-27
; *  @build:   b150527
; * ---------------------------------------------------------------------------------------
; *
; * Copyright (c) 2015 , Freescale Semiconductor, Inc.
; * All rights reserved.
; *
; * Redistribution and use in source and binary forms, with or without modification,
; * are permitted provided that the following conditions are met:
; *
; * o Redistributions of source code must retain the above copyright notice, this list
; *   of conditions and the following disclaimer.
; *
; * o Redistributions in binary form must reproduce the above copyright notice, this
; *   list of conditions and the following disclaimer in the documentation and/or
; *   other materials provided with the distribution.
; *
; * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
; *   contributors may be used to endorse or promote products derived from this
; *   software without specific prior written permission.
; *
; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
; * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
; * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
; * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
; * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
; * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
; *
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; *****************************************************************************/


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size
                IMPORT |Image$$ARM_LIB_STACK$$ZI$$Limit|

__Vectors       DCD     |Image$$ARM_LIB_STACK$$ZI$$Limit| ; Top of Stack
                DCD     Reset_Handler  ; Reset Handler
                DCD     NMI_Handler                         ;NMI Handler
                DCD     HardFault_Handler                   ;Hard Fault Handler
                DCD     MemManage_Handler                   ;MPU Fault Handler
                DCD     BusFault_Handler                    ;Bus Fault Handler
                DCD     UsageFault_Handler                  ;Usage Fault Handler
                DCD     0                                   ;Reserved
                DCD     0                                   ;Reserved
                DCD     0                                   ;Reserved
                DCD     0                                   ;Reserved
                DCD     SVC_Handler                         ;SVCall Handler
                DCD     DebugMon_Handler                    ;Debug Monitor Handler
                DCD     0                                   ;Reserved
                DCD     PendSV_Handler                      ;PendSV Handler
                DCD     SysTick_Handler                     ;SysTick Handler

                                                            ;External Interrupts
                DCD     GPR_Handler                         ;GPR Interrupt
                DCD     DAP_Handler                         ;DAP Interrupt
                DCD     SDMA_Handler                        ;SDMA Interrupt
                DCD     DBGMON_Handler                      ;DBGMON Interrupt
                DCD     SNVS_Handler                        ;SNVS Interrupt
                DCD     LCDIF_Handler                       ;LCDIF Interrupt
                DCD     SIM2_Handler                        ;SIM2 Interrupt
                DCD     CSI_Handler                         ;CSI Interrupt
                DCD     PXP1_Handler                        ;PXP1 Interrupt
                DCD     Reserved9_Handler                   ;Reserved interrupt 9
                DCD     WDOG3_Handler                       ;WDOG3 Interrupt
                DCD     SEMA4_HS_M4_Handler                 ;SEMA4_HS_M4 Interrupt
                DCD     APBHDMA_Handler                     ;APBHDMA Interrupt
                DCD     EIM_Handler                         ;EIM Interrupt
                DCD     BCH_Handler                         ;BCH Interrupt
                DCD     GPMI_Handler                        ;GPMI Interrupt
                DCD     UART6_Handler                       ;UART6 Interrupt
                DCD     FTM1_Handler                        ;FTM1 Interrupt
                DCD     FTM2_Handler                        ;FTM2 Interrupt
                DCD     SNVS_CONSOLIDATED_Handler           ;SNVS_CONSOLIDATED Interrupt
                DCD     SNVS_SECURITY_Handler               ;SNVS_SECURITY Interrupt
                DCD     CSU_Handler                         ;CSU Interrupt
                DCD     uSDHC1_Handler                      ;uSDHC1 Interrupt
                DCD     uSDHC2_Handler                      ;uSDHC2 Interrupt
                DCD     uSDHC3_Handler                      ;uSDHC3 Interrupt
                DCD     MIPI_CSI_Handler                    ;MIPI_CSI Interrupt
                DCD     UART1_Handler                       ;UART1 Interrupt
                DCD     UART2_Handler                       ;UART2 Interrupt
                DCD     UART3_Handler                       ;UART3 Interrupt
                DCD     UART4_Handler                       ;UART4 Interrupt
                DCD     UART5_Handler                       ;UART5 Interrupt
                DCD     eCSPI1_Handler                      ;eCSPI1 Interrupt
                DCD     eCSPI2_Handler                      ;eCSPI2 Interrupt
                DCD     eCSPI3_Handler                      ;eCSPI3 Interrupt
                DCD     eCSPI4_Handler                      ;eCSPI4 Interrupt
                DCD     I2C1_Handler                        ;I2C1 Interrupt
                DCD     I2C2_Handler                        ;I2C2 Interrupt
                DCD     I2C3_Handler                        ;I2C3 Interrupt
                DCD     I2C4_Handler                        ;I2C4 Interrupt
                DCD     RDC_Handler                         ;RDC Interrupt
                DCD     USB_OH3_OTG2_1_Handler              ;USB_OH3_OTG2_1 Interrupt
                DCD     MIPI_DSI_Handler                    ;MIPI_DSI Interrupt
                DCD     USB_OH3_OTG2_2_Handler              ;USB_OH3_OTG2_2 Interrupt
                DCD     USB_OH2_OTG_Handler                 ;USB_OH2_OTG Interrupt
                DCD     USB_OTG1_Handler                    ;USB_OTG1 Interrupt
                DCD     USB_OTG2_Handler                    ;USB_OTG2 Interrupt
                DCD     PXP2_Handler                        ;PXP2 Interrupt
                DCD     SCTR1_Handler                       ;SCTR1 Interrupt
                DCD     SCTR2_Handler                       ;SCTR2 Interrupt
                DCD     Analog_TempSensor_Handler           ;Analog_TempSensor Interrupt
                DCD     SAI3_Handler                        ;SAI3 Interrupt
                DCD     Analog_brown_out_Handler            ;Analog_brown_out Interrupt
                DCD     GPT4_Handler                        ;GPT4 Interrupt
                DCD     GPT3_Handler                        ;GPT3 Interrupt
                DCD     GPT2_Handler                        ;GPT2 Interrupt
                DCD     GPT1_Handler                        ;GPT1 Interrupt
                DCD     GPIO1_INT7_Handler                  ;GPIO1_INT7 Interrupt
                DCD     GPIO1_INT6_Handler                  ;GPIO1_INT6 Interrupt
                DCD     GPIO1_INT5_Handler                  ;GPIO1_INT5 Interrupt
                DCD     GPIO1_INT4_Handler                  ;GPIO1_INT4 Interrupt
                DCD     GPIO1_INT3_Handler                  ;GPIO1_INT3 Interrupt
                DCD     GPIO1_INT2_Handler                  ;GPIO1_INT2 Interrupt
                DCD     GPIO1_INT1_Handler                  ;GPIO1_INT1 Interrupt
                DCD     GPIO1_INT0_Handler                  ;GPIO1_INT0 Interrupt
                DCD     GPIO1_INT15_0_Handler               ;GPIO1_INT15_0 Interrupt
                DCD     GPIO1_INT31_16_Handler              ;GPIO1_INT31_16 Interrupt
                DCD     GPIO2_INT15_0_Handler               ;GPIO2_INT15_0 Interrupt
                DCD     GPIO2_INT31_16_Handler              ;GPIO2_INT31_16 Interrupt
                DCD     GPIO3_INT15_0_Handler               ;GPIO3_INT15_0 Interrupt
                DCD     GPIO3_INT31_16_Handler              ;GPIO3_INT31_16 Interrupt
                DCD     GPIO4_INT15_0_Handler               ;GPIO4_INT15_0 Interrupt
                DCD     GPIO4_INT31_16_Handler              ;GPIO4_INT31_16 Interrupt
                DCD     GPIO5_INT15_0_Handler               ;GPIO5_INT15_0 Interrupt
                DCD     GPIO5_INT31_16_Handler              ;GPIO5_INT31_16 Interrupt
                DCD     GPIO6_INT15_0_Handler               ;GPIO6_INT15_0 Interrupt
                DCD     GPIO6_INT31_16_Handler              ;GPIO6_INT31_16 Interrupt
                DCD     GPIO7_INT15_0_Handler               ;GPIO7_INT15_0 Interrupt
                DCD     GPIO7_INT31_16_Handler              ;GPIO7_INT31_16 Interrupt
                DCD     WDOG1_Handler                       ;WDOG1 Interrupt
                DCD     WDOG2_Handler                       ;WDOG2 Interrupt
                DCD     KPP_Handler                         ;KPP Interrupt
                DCD     PWM1_Handler                        ;PWM1 Interrupt
                DCD     PWM2_Handler                        ;PWM2 Interrupt
                DCD     PWM3_Handler                        ;PWM3 Interrupt
                DCD     PWM4_Handler                        ;PWM4 Interrupt
                DCD     CCM1_Handler                        ;CCM1 Interrupt
                DCD     CCM2_Handler                        ;CCM2 Interrupt
                DCD     GPC_Handler                         ;GPC Interrupt
                DCD     MU_A7_Handler                       ;MU_A7 Interrupt
                DCD     SRC_Handler                         ;SRC Interrupt
                DCD     SIM1_Handler                        ;SIM1 Interrupt
                DCD     RTIC_Handler                        ;RTIC Interrupt
                DCD     CPU_Handler                         ;CPU Interrupt
                DCD     CPU_CTI_Handler                     ;CPU_CTI Interrupt
                DCD     CCM_SRC_GPC_Handler                 ;CCM_SRC_GPC Interrupt
                DCD     SAI1_Handler                        ;SAI1 Interrupt
                DCD     SAI2_Handler                        ;SAI2 Interrupt
                DCD     MU_M4_Handler                       ;MU_M4 Interrupt
                DCD     ADC1_Handler                        ;ADC1 Interrupt
                DCD     ADC2_Handler                        ;ADC2 Interrupt
                DCD     ENET2_MAC0_TRANS1_Handler           ;ENET2_MAC0_TRANS1 Interrupt
                DCD     ENET2_MAC0_TRANS2_Handler           ;ENET2_MAC0_TRANS2 Interrupt
                DCD     ENET2_MAC0_IRQ_Handler              ;ENET2_MAC0_IRQ Interrupt
                DCD     ENET2_1588_TIMER_IRQ_Handler        ;ENET2_1588_TIMER_IRQ Interrupt
                DCD     TPR_Handler                         ;TPR Interrupt
                DCD     CAAM_QUEUE_Handler                  ;CAAM_QUEUE Interrupt
                DCD     CAAM_ERROR_Handler                  ;CAAM_ERROR Interrupt
                DCD     QSPI_Handler                        ;QSPI Interrupt
                DCD     TZASC1_Handler                      ;TZASC1 Interrupt
                DCD     WDOG4_Handler                       ;WDOG4 Interrupt
                DCD     FLEXCAN1_Handler                    ;FLEXCAN1 Interrupt
                DCD     FLEXCAN2_Handler                    ;FLEXCAN2 Interrupt
                DCD     PERFMON1_Handler                    ;PERFMON1 Interrupt
                DCD     PERFMON2_Handler                    ;PERFMON2 Interrupt
                DCD     CAAM_WRAPPER1_Handler               ;CAAM_WRAPPER1 Interrupt
                DCD     CAAM_WRAPPER2_Handler               ;CAAM_WRAPPER2 Interrupt
                DCD     SEMA4_HS_A7_Handler                 ;SEMA4_HS_A7 Interrupt
                DCD     EPDC_Handler                        ;EPDC Interrupt
                DCD     ENET1_MAC0_TRANS1_Handler           ;ENET1_MAC0_TRANS1 Interrupt
                DCD     ENET1_MAC0_TRANS2_Handler           ;ENET1_MAC0_TRANS2 Interrupt
                DCD     ENET1_MAC0_Handler                  ;ENET1_MAC0 Interrupt
                DCD     ENET1_1588_TIMER_Handler            ;ENET1_1588_TIMER Interrupt
                DCD     PCIE_CTRL1_Handler                  ;PCIE_CTRL1 Interrupt
                DCD     PCIE_CTRL2_Handler                  ;PCIE_CTRL2 Interrupt
                DCD     PCIE_CTRL3_Handler                  ;PCIE_CTRL3 Interrupt
                DCD     PCIE_CTRL4_Handler                  ;PCIE_CTRL4 Interrupt
                DCD     UART7_Handler                       ;UART7 Interrupt
                DCD     PCIE_CTRL_REQUEST_Handler           ;PCIE_CTRL_REQUEST Interrupt
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors


                AREA    |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main

                CPSID   I               ; Mask interrupts
                LDR     R0, =SystemInit
                BLX     R0
                CPSIE   i               ; Unmask interrupts
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)
NMI_Handler\
                PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler\
                PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP
Default_Handler\
                PROC
                EXPORT  GPR_Handler               [WEAK]
                EXPORT  DAP_Handler               [WEAK]
                EXPORT  SDMA_Handler              [WEAK]
                EXPORT  DBGMON_Handler            [WEAK]
                EXPORT  SNVS_Handler              [WEAK]
                EXPORT  LCDIF_Handler             [WEAK]
                EXPORT  SIM2_Handler              [WEAK]
                EXPORT  CSI_Handler               [WEAK]
                EXPORT  PXP1_Handler              [WEAK]
                EXPORT  Reserved9_Handler         [WEAK]
                EXPORT  WDOG3_Handler             [WEAK]
                EXPORT  SEMA4_HS_M4_Handler       [WEAK]
                EXPORT  APBHDMA_Handler           [WEAK]
                EXPORT  EIM_Handler               [WEAK]
                EXPORT  BCH_Handler               [WEAK]
                EXPORT  GPMI_Handler              [WEAK]
                EXPORT  UART6_Handler             [WEAK]
                EXPORT  FTM1_Handler              [WEAK]
                EXPORT  FTM2_Handler              [WEAK]
                EXPORT  SNVS_CONSOLIDATED_Handler [WEAK]
                EXPORT  SNVS_SECURITY_Handler     [WEAK]
                EXPORT  CSU_Handler               [WEAK]
                EXPORT  uSDHC1_Handler            [WEAK]
                EXPORT  uSDHC2_Handler            [WEAK]
                EXPORT  uSDHC3_Handler            [WEAK]
                EXPORT  MIPI_CSI_Handler          [WEAK]
                EXPORT  UART1_Handler             [WEAK]
                EXPORT  UART2_Handler             [WEAK]
                EXPORT  UART3_Handler             [WEAK]
                EXPORT  UART4_Handler             [WEAK]
                EXPORT  UART5_Handler             [WEAK]
                EXPORT  eCSPI1_Handler            [WEAK]
                EXPORT  eCSPI2_Handler            [WEAK]
                EXPORT  eCSPI3_Handler            [WEAK]
                EXPORT  eCSPI4_Handler            [WEAK]
                EXPORT  I2C1_Handler              [WEAK]
                EXPORT  I2C2_Handler              [WEAK]
                EXPORT  I2C3_Handler              [WEAK]
                EXPORT  I2C4_Handler              [WEAK]
                EXPORT  RDC_Handler               [WEAK]
                EXPORT  USB_OH3_OTG2_1_Handler    [WEAK]
                EXPORT  MIPI_DSI_Handler          [WEAK]
                EXPORT  USB_OH3_OTG2_2_Handler    [WEAK]
                EXPORT  USB_OH2_OTG_Handler       [WEAK]
                EXPORT  USB_OTG1_Handler          [WEAK]
                EXPORT  USB_OTG2_Handler          [WEAK]
                EXPORT  PXP2_Handler              [WEAK]
                EXPORT  SCTR1_Handler             [WEAK]
                EXPORT  SCTR2_Handler             [WEAK]
                EXPORT  Analog_TempSensor_Handler [WEAK]
                EXPORT  SAI3_Handler              [WEAK]
                EXPORT  Analog_brown_out_Handler  [WEAK]
                EXPORT  GPT4_Handler              [WEAK]
                EXPORT  GPT3_Handler              [WEAK]
                EXPORT  GPT2_Handler              [WEAK]
                EXPORT  GPT1_Handler              [WEAK]
                EXPORT  GPIO1_INT7_Handler        [WEAK]
                EXPORT  GPIO1_INT6_Handler        [WEAK]
                EXPORT  GPIO1_INT5_Handler        [WEAK]
                EXPORT  GPIO1_INT4_Handler        [WEAK]
                EXPORT  GPIO1_INT3_Handler        [WEAK]
                EXPORT  GPIO1_INT2_Handler        [WEAK]
                EXPORT  GPIO1_INT1_Handler        [WEAK]
                EXPORT  GPIO1_INT0_Handler        [WEAK]
                EXPORT  GPIO1_INT15_0_Handler     [WEAK]
                EXPORT  GPIO1_INT31_16_Handler    [WEAK]
                EXPORT  GPIO2_INT15_0_Handler     [WEAK]
                EXPORT  GPIO2_INT31_16_Handler    [WEAK]
                EXPORT  GPIO3_INT15_0_Handler     [WEAK]
                EXPORT  GPIO3_INT31_16_Handler    [WEAK]
                EXPORT  GPIO4_INT15_0_Handler     [WEAK]
                EXPORT  GPIO4_INT31_16_Handler    [WEAK]
                EXPORT  GPIO5_INT15_0_Handler     [WEAK]
                EXPORT  GPIO5_INT31_16_Handler    [WEAK]
                EXPORT  GPIO6_INT15_0_Handler     [WEAK]
                EXPORT  GPIO6_INT31_16_Handler    [WEAK]
                EXPORT  GPIO7_INT15_0_Handler     [WEAK]
                EXPORT  GPIO7_INT31_16_Handler    [WEAK]
                EXPORT  WDOG1_Handler             [WEAK]
                EXPORT  WDOG2_Handler             [WEAK]
                EXPORT  KPP_Handler               [WEAK]
                EXPORT  PWM1_Handler              [WEAK]
                EXPORT  PWM2_Handler              [WEAK]
                EXPORT  PWM3_Handler              [WEAK]
                EXPORT  PWM4_Handler              [WEAK]
                EXPORT  CCM1_Handler              [WEAK]
                EXPORT  CCM2_Handler              [WEAK]
                EXPORT  GPC_Handler               [WEAK]
                EXPORT  MU_A7_Handler             [WEAK]
                EXPORT  SRC_Handler               [WEAK]
                EXPORT  SIM1_Handler              [WEAK]
                EXPORT  RTIC_Handler              [WEAK]
                EXPORT  CPU_Handler               [WEAK]
                EXPORT  CPU_CTI_Handler           [WEAK]
                EXPORT  CCM_SRC_GPC_Handler       [WEAK]
                EXPORT  SAI1_Handler              [WEAK]
                EXPORT  SAI2_Handler              [WEAK]
                EXPORT  MU_M4_Handler             [WEAK]
                EXPORT  ADC1_Handler              [WEAK]
                EXPORT  ADC2_Handler              [WEAK]
                EXPORT  ENET2_MAC0_TRANS1_Handler [WEAK]
                EXPORT  ENET2_MAC0_TRANS2_Handler [WEAK]
                EXPORT  ENET2_MAC0_IRQ_Handler    [WEAK]
                EXPORT  ENET2_1588_TIMER_IRQ_Handler[WEAK]
                EXPORT  TPR_Handler               [WEAK]
                EXPORT  CAAM_QUEUE_Handler        [WEAK]
                EXPORT  CAAM_ERROR_Handler        [WEAK]
                EXPORT  QSPI_Handler              [WEAK]
                EXPORT  TZASC1_Handler            [WEAK]
                EXPORT  WDOG4_Handler             [WEAK]
                EXPORT  FLEXCAN1_Handler          [WEAK]
                EXPORT  FLEXCAN2_Handler          [WEAK]
                EXPORT  PERFMON1_Handler          [WEAK]
                EXPORT  PERFMON2_Handler          [WEAK]
                EXPORT  CAAM_WRAPPER1_Handler     [WEAK]
                EXPORT  CAAM_WRAPPER2_Handler     [WEAK]
                EXPORT  SEMA4_HS_A7_Handler       [WEAK]
                EXPORT  EPDC_Handler              [WEAK]
                EXPORT  ENET1_MAC0_TRANS1_Handler [WEAK]
                EXPORT  ENET1_MAC0_TRANS2_Handler [WEAK]
                EXPORT  ENET1_MAC0_Handler        [WEAK]
                EXPORT  ENET1_1588_TIMER_Handler  [WEAK]
                EXPORT  PCIE_CTRL1_Handler        [WEAK]
                EXPORT  PCIE_CTRL2_Handler        [WEAK]
                EXPORT  PCIE_CTRL3_Handler        [WEAK]
                EXPORT  PCIE_CTRL4_Handler        [WEAK]
                EXPORT  UART7_Handler             [WEAK]
                EXPORT  PCIE_CTRL_REQUEST_Handler [WEAK]
                EXPORT  DefaultISR                [WEAK]
GPR_Handler
DAP_Handler
SDMA_Handler
DBGMON_Handler
SNVS_Handler
LCDIF_Handler
SIM2_Handler
CSI_Handler
PXP1_Handler
Reserved9_Handler
WDOG3_Handler
SEMA4_HS_M4_Handler
APBHDMA_Handler
EIM_Handler
BCH_Handler
GPMI_Handler
UART6_Handler
FTM1_Handler
FTM2_Handler
SNVS_CONSOLIDATED_Handler
SNVS_SECURITY_Handler
CSU_Handler
uSDHC1_Handler
uSDHC2_Handler
uSDHC3_Handler
MIPI_CSI_Handler
UART1_Handler
UART2_Handler
UART3_Handler
UART4_Handler
UART5_Handler
eCSPI1_Handler
eCSPI2_Handler
eCSPI3_Handler
eCSPI4_Handler
I2C1_Handler
I2C2_Handler
I2C3_Handler
I2C4_Handler
RDC_Handler
USB_OH3_OTG2_1_Handler
MIPI_DSI_Handler
USB_OH3_OTG2_2_Handler
USB_OH2_OTG_Handler
USB_OTG1_Handler
USB_OTG2_Handler
PXP2_Handler
SCTR1_Handler
SCTR2_Handler
Analog_TempSensor_Handler
SAI3_Handler
Analog_brown_out_Handler
GPT4_Handler
GPT3_Handler
GPT2_Handler
GPT1_Handler
GPIO1_INT7_Handler
GPIO1_INT6_Handler
GPIO1_INT5_Handler
GPIO1_INT4_Handler
GPIO1_INT3_Handler
GPIO1_INT2_Handler
GPIO1_INT1_Handler
GPIO1_INT0_Handler
GPIO1_INT15_0_Handler
GPIO1_INT31_16_Handler
GPIO2_INT15_0_Handler
GPIO2_INT31_16_Handler
GPIO3_INT15_0_Handler
GPIO3_INT31_16_Handler
GPIO4_INT15_0_Handler
GPIO4_INT31_16_Handler
GPIO5_INT15_0_Handler
GPIO5_INT31_16_Handler
GPIO6_INT15_0_Handler
GPIO6_INT31_16_Handler
GPIO7_INT15_0_Handler
GPIO7_INT31_16_Handler
WDOG1_Handler
WDOG2_Handler
KPP_Handler
PWM1_Handler
PWM2_Handler
PWM3_Handler
PWM4_Handler
CCM1_Handler
CCM2_Handler
GPC_Handler
MU_A7_Handler
SRC_Handler
SIM1_Handler
RTIC_Handler
CPU_Handler
CPU_CTI_Handler
CCM_SRC_GPC_Handler
SAI1_Handler
SAI2_Handler
MU_M4_Handler
ADC1_Handler
ADC2_Handler
ENET2_MAC0_TRANS1_Handler
ENET2_MAC0_TRANS2_Handler
ENET2_MAC0_IRQ_Handler
ENET2_1588_TIMER_IRQ_Handler
TPR_Handler
CAAM_QUEUE_Handler
CAAM_ERROR_Handler
QSPI_Handler
TZASC1_Handler
WDOG4_Handler
FLEXCAN1_Handler
FLEXCAN2_Handler
PERFMON1_Handler
PERFMON2_Handler
CAAM_WRAPPER1_Handler
CAAM_WRAPPER2_Handler
SEMA4_HS_A7_Handler
EPDC_Handler
ENET1_MAC0_TRANS1_Handler
ENET1_MAC0_TRANS2_Handler
ENET1_MAC0_Handler
ENET1_1588_TIMER_Handler
PCIE_CTRL1_Handler
PCIE_CTRL2_Handler
PCIE_CTRL3_Handler
PCIE_CTRL4_Handler
UART7_Handler
PCIE_CTRL_REQUEST_Handler
DefaultISR
                B      DefaultISR
                ENDP
                  ALIGN


                END
