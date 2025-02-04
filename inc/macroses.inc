;
; ATTiny85 Assembller Template
; macroses.inc
; This file contains various macroses.
;
; Created: 25.01.2025 4:40pm
; Author : Dmitry Slobodchikov
;

; --- Initiates/erases SRAM data by given address and the number of bytes to zero.
.MACRO INIT_DATA
  clr R1
  ldi YH, high(@0)
  ldi YL, low(@0)
  clr tmp
  _WHILE_CLR_DATA:
    st Y+, R1
    inc tmp
    cpi tmp, @1
    brne _WHILE_CLR_DATA

.ENDMACRO


; ; --- Initializes given variable
; ; 0 - LED param address
; ; 1 - Delay 1
; ; 2 - Delay 2
; ; 3 - PORT address
; ; 4 - PIN bit
; ; 5 - Delay 1 source counter address
; ; 6 - Delay 2 source counter address
; .MACRO INIT_LED_PARAM
;   ldi YH, high(@0)
;   ldi YL, low(@0)
;   ; Store Pause1
;   ldi tmpH, high(@1)
;   ldi tmpL, low(@1)
;   std Y+0x08, tmpH
;   std Y+0x09, tmpL
;   ; Store Pause2
;   ldi tmpH, high(@2)
;   ldi tmpL, low(@2)
;   std Y+0x0a, tmpH
;   std Y+0x0b, tmpL
;   ; Store LED PORT
;   ldi tmpH, high(@3)
;   ldi tmpL, low(@3)
;   std Y+0x0c, tmpH
;   std Y+0x0d, tmpL
;   ; Store LED PIN
;   ldi tmp, (1<<@4)
;   std Y+0x0e, tmp
;   ; Clear temporary register
;   clr tmp
;   std Y+0x0f, tmp
;   ; Store Delay1 source address
;   ldi tmpH, high(@5)
;   ldi tmpL, low(@5)
;   std Y+0x10, tmpH
;   std Y+0x11, tmpL
;   ; Store Delay2 source address
;   ldi tmpH, high(@6)
;   ldi tmpL, low(@6)
;   std Y+0x12, tmpH
;   std Y+0x13, tmpL

; .ENDMACRO


; --- Increments counters by given address.
.MACRO INC_CNT
  ldi YH, high(@0)
  ldi YL, low(@0)
  ld tmpH, Y+
  ld tmpL, Y
  ldi tmp, 0x01
  mov R0, tmp
  clr R1
  add tmpL, R0
  adc tmpH, R1
  st Y, tmpL
  st -Y, tmpH
  
.ENDMACRO
