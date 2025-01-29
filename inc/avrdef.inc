;
; ATTiny85 Assembller Template
; avrdef.inc
; This file contains various definitions.
;
; Created: 28.01.2025 11:23am
; Author : Dmitry Slobodchikov
;

.equ F_CPU = 16384000 ; CPU frequency defined as 16 MHz

; --- Frequently used register definitions 
.def dClock   = R12
.def dRate    = R13
.def txByte   = R14
.def rxByte   = R15
.def tmp      = R16
.def _EREG_   = R17
.def tmpLL    = R18
.def tmpLH    = R19
.def tmpHL    = R20
.def tmpHH    = R21
.def cntLL    = R22
.def cntLH    = R23
.def cntHL    = R24
.def cntHH    = R25

.equ LEDDDR   = DDRB
.equ LEDPORT  = PORTB
.equ LEDPIN   = PINB
.equ LEDBLUE  = PB1


; --- Register name definitions
#define tmpL tmpLL
#define tmpH tmpLH
#define cntL cntLL
#define cntH cntLH
#define _cntL cntHL
#define _cntH cntHH
#define _tmp2 R3        ; reserved for 16-bit, 32-bit, and 64-bit operations 
#define _tmp tmpLL      ; reserved for 16-bit and 64-bit operations 
#define __tmp tmpLL     ; reserved for 32-bit operations
#define _cnt cntLL      ; reserved for 16-bit and 64-bit operations
#define __cnt cntLL     ; reserved for 32-bit operations

#define S cntHL         ; Pair of registers R19-R20
#define SL cntHL
#define SH cntHH
#define T cntHL         ; Pair of registers R20-R21
#define TL cntHL
#define TH cntHH
#define V cntHL         ; Pair of registers R22-R23
#define VL cntHL
#define VH cntHH
#define W cntHL         ; Pair of registers R25-R25
#define WL cntHL
#define WH cntHH


; --- Constant definitions
#define QNT_THRESHOLD 240 ; it gives 16 prescaler for 1ms system quant
#define SEC_THRESHOLD 1000
#define INIT_RAM_CLR_CNT 32
#define INIT_SCHED_TMOUT 50

#define _LEDBLUE_PD_    ; Define Blue Led in Pull-Down Mode


; --- Event REGistry Flag Definitions
.equ _QIF_    = 0       ; System Quant Interval Flag
; .equ _SIF_    = 1       ; 1 Second Interval Flag
; .equ _10F_    = 2       ; 10 Seconds Interval Flag
; .equ _MIF_    = 3       ; 1 Minute Interval Flag
.equ _SMF_    = 4       ; Sleep Mode Flag
.equ _DLF_    = 6       ; Delay Flag

.equ _BLNF_    = 0       ; Blue LED On Flag
.equ _BLFF_    = 1       ; Blue LED Off Flag
.equ _GLNF_    = 2       ; Green LED On Flag
.equ _GLFF_    = 3       ; Green LED Off Flag
.equ _RLNF_    = 4       ; Red LED On Flag
.equ _RLFF_    = 5       ; Red LED Off Flag