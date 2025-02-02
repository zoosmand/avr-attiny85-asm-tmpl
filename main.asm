;
; ATTiny85 Assembller Template
; main.asm
; This file contains the base logic code.
;
; Created: 25.01.2025 4:40pm
; Author : Dmitry Slobodchikov
;

; The ATTiny85 fuses are set as follows: 
;   HIGH=0xdf
;   LOW=0xe1 (16MHz), Current
; To reduce power consumption set the low fuse register as follows:
;   LOW=0xe2 (8MHz)

.include "tn85def.inc"
.include "./inc/avrdef.inc"


; --- Set start address
.cseg
.org 0

.include "./inc/vectors.inc"
.include "./inc/macroses.inc"
.include "./inc/delay.inc"
.include "./inc/scheduler.inc"
.include "./inc/init.inc"


 
; --- Main workflow
MAIN:
  rcall SLEEP_MODE

  SCHEDULER SecCnt, 5, LedPrmBlue, LedReg, _BLAF_, _END_SCHED_01
  _END_SCHED_01:
    nop

  SCHEDULER SecCnt, 7, LedPrmGreen, LedReg, _GLAF_, _END_SCHED_02
  _END_SCHED_02:
    nop

  rcall INC_QNT_CNT

  rcall LED_BLUE
  rcall LED_GREEN

  rjmp MAIN
  rjmp THE_END

.include "./inc/interrupts.inc"
.include "./inc/utils.inc"
.include "./inc/led.inc"


; --- Emergency Exit and Reboot
THE_END:
  cli
  rjmp 0


.include "./inc/var.inc"
