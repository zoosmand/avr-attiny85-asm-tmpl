;
; ATTiny85 Assembller Template
; avrdef.inc
; This file contains various definitions.
;
; Created: 28.01.2025 11:23am
; Author : Dmitry Slobodchikov
;

#define F_CPU 16 ; CPU frequency defined as 16 MHz

; --- Frequently used register definitions 
.def dClock     = R12
.def dRate      = R13
; .def txByte     = R14
; .def rxByte     = R15 
.def tmp        = R16
.def _EREG_     = R17
.def tmpLL      = R18
.def tmpLH      = R19
.def tmpHL      = R20
.def tmpHH      = R21
.def cntLL      = R22
.def cntLH      = R23
.def cntHL      = R24
.def cntHH      = R25

; --- LED
.equ LEDDDR     = DDRB
.equ LEDPORT    = PORTB
.equ LEDPIN     = PINB
.equ LEDBLUE    = PB1
.equ LEDGREEN   = PB4
.equ LEDRED     = PB3

; --- I2C
.equ I2CDDR     = DDRB
.equ I2CPORT    = PORTB
.equ I2CPIN     = PINB
.equ SDA        = PB0
.equ SCL        = PB2



; --- Register name definitions
#define txByte tmpLL
#define rxByte tmpLH
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
#define INIT_RAM_CLR_CNT 128

;#define _LEDBLUE_PD_   ; Define Blue Led in Pull-Down Mode
;#define _LEDGREEN_PD_  ; Define Green Led in Pull-Down Mode
;#define _LEDRED_PD_    ; Define Red Led in Pull-Down Mode


; --- Event REGistry Flag Definitions
.equ _QIF_    = 0       ; System Quant Interval Flag
.equ _SMF_    = 1       ; Sleep Mode Flag

; LED manage commands
.equ _LCMSK_  = 0b11111000  ; LED commands mask
.equ _LUP_    = 0b00000001  ; Up a given LED
.equ _LUC_    = 0b00000010  ; Check state while given LED is up
.equ _LDW_    = 0b00000101  ; Down given LED
.equ _LDC_    = 0b00000110  ; Check state while given LED is down


; --- I2C Bus flags
; .equ _MIF_		= 0 ; Timer Measure Interval Flag
.equ _I2CRWF_	= 0 ; I2C Read/Write Flag, 0 - write (m->s), 1 - read (m<-s)
.equ _I2CANF_	= 1 ; I2C Ack/Nack Flag, 0 - ACK, 1 - NACK
.equ _I2CERF_	= 2 ; I2C ERror Flag

; 1602A Display Flags
.equ _1602RSF_	= 0 ; 1602A RS Flag, 0 - command, 1 - data
.equ _1602RWF_	= 1 ; 1602A R/W Flag, 0 - write, 1 - read
.equ _1602EF_	= 2 ; 1602A E Flag, Enable (Strobe) Flag
; .equ _BF_		= 7 ; Bit Flag

; 1602A Command instructions
.equ _E         = 2
.equ _Rw        = 1
.equ _Rs        = 0
