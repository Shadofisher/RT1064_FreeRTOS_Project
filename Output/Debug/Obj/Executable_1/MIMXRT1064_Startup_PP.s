# 0 "/home/graeme/Projects/RT1064_FreeRTOS_Project/MIMXRT1064/Source/MIMXRT1064_Startup.s"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/graeme/Projects/RT1064_FreeRTOS_Project/MIMXRT1064/Source/MIMXRT1064_Startup.s"
# 78 "/home/graeme/Projects/RT1064_FreeRTOS_Project/MIMXRT1064/Source/MIMXRT1064_Startup.s"
        .syntax unified
# 101 "/home/graeme/Projects/RT1064_FreeRTOS_Project/MIMXRT1064/Source/MIMXRT1064_Startup.s"
        .global reset_handler
        .global Reset_Handler
        .equ reset_handler, Reset_Handler
        .section .init.Reset_Handler, "ax"
        .balign 2
        .thumb_func
Reset_Handler:




        bl SystemInit
# 155 "/home/graeme/Projects/RT1064_FreeRTOS_Project/MIMXRT1064/Source/MIMXRT1064_Startup.s"
        movw R0, 0xED88
        movt R0, 0xE000
        ldr R1, [R0]
        orrs R1, R1, #(0xf << 20)
        str R1, [R0]




        b _start





        .weak SystemInit





        .section .init_array, "aw"
        .balign 4
        .word SystemCoreClockUpdate
# 197 "/home/graeme/Projects/RT1064_FreeRTOS_Project/MIMXRT1064/Source/MIMXRT1064_Startup.s"
        .weak HardFault_Handler
        .section .init.HardFault_Handler, "ax"
        .balign 2
        .thumb_func
HardFault_Handler:



        ldr R1, =0xE000ED2C
        ldr R2, [R1]
        cmp R2, #0

hfLoop:
        bmi hfLoop
# 225 "/home/graeme/Projects/RT1064_FreeRTOS_Project/MIMXRT1064/Source/MIMXRT1064_Startup.s"
        tst LR, #4
        ite eq
        mrseq R0, MSP
        mrsne R0, PSP
# 239 "/home/graeme/Projects/RT1064_FreeRTOS_Project/MIMXRT1064/Source/MIMXRT1064_Startup.s"
        orr R2, R2, #0x80000000
        str R2, [R1]




        ldr R1, [R0, #24]
        adds R1, #2
        str R1, [R0, #24]

        bx LR
