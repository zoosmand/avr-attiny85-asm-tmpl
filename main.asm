;
; ATtiny85 Assembller Template
; main.asm
; This file contains the base logic code.
;
; Created: 25.01.2025 4:40pm
; Author : Dmitry Slobodchikov
;

; Fuses: 
;   HIGH=0xdf
;   LOW=0xe2 (8MHz)
;   LOW=0xe1 (16MHz), Current

.include "tn85def.inc"

.equ F_CPU = 16000000

.def dClock   = R12
.def dRate    = R13
.def cntHL    = R14
.def cntd     = R15
.def tmp      = R16
.def _EREG_   = R17
.def txByte   = R18
.def rxByte   = R19
.def tcntL    = R20
.def tcntH    = R21
.def tmpL     = R22
.def tmpH     = R23
.def cntLL    = R24
.def cntLH    = R25

.equ LEDDDR   = DDRB
.equ LEDPORT  = PORTB
.equ LEDPIN   = PINB
.equ LED0PIN  = PB1


;/*************************** Definitions and Constanrs **************************/
#define QNT_THRESHOLD 240 ; it gives 16 prescaler for 1ms system quant
#define SEC_THRESHOLD 1000


;/******************************* Event REGistry Flags ***************************/
.equ _QIF_    = 0       ; System Quant Interval Flag
.equ _SIF_    = 1       ; Second Interval Flag
.equ _SMF_    = 2       ; Sleep Mode Flag
.equ _LBF_    = 3       ; LED Blink Flag

.cseg
.org 0

.include "./inc/vectors.inc"
.include "./inc/macroses.inc"
.include "./inc/init.inc"



;/*********************************** MAIN LOOP **********************************/
MAIN:
  sbrs _EREG_, _SMF_
  rjmp _AWAKE
  rcall SLEEP_MODE

  _AWAKE:

    rcall INC_QNT_CNT
    rcall INC_SEC_CNT
    rcall INC_SEC

    rcall LED_BLINK

    ; Set Sleep Mode flag
    sbr _EREG_, (1<<_SMF_)  
  
  rjmp MAIN
  rjmp THE_END

.include "./inc/interrupts.inc"
.include "./inc/utils.inc"


;/************************* Emergency Exit and Reboot ****************************/
THE_END:
  cli
  rjmp 0


.include "./inc/var.inc"
