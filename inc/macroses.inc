;
; ATTiny85 Assembller Template
; macroses.inc
; This file contains various macroses.
;
; Created: 25.01.2025 4:40pm
; Author : Dmitry Slobodchikov
;

; --- Initiates/erases SRAM data by given address and the number of bytes to zero.
; 0 - the beginning address of the data to clean
; 1 - the number of bytes to clean
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


; --- Increments counters by given address.
; 0 - address of the counter
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


; --- Sets a given flag into the register
; 0 - register
; 1 - flag
.MACRO SET_FLAG
  push tmp

  ldi XH, high(@0)
  ldi XL, low(@0)
  ld tmp, X
  sbr tmp, (1<<@1)
  st X, tmp

  pop tmp
.ENDMACRO


; --- Clears a given flag from the register
; 0 - register
; 1 - flag
.MACRO CLR_FLAG
  push tmp

  ldi XH, high(@0)
  ldi XL, low(@0)
  ld tmp, X
  cbr tmp, (1<<@1)
  st X, tmp

  pop tmp
.ENDMACRO


; --- Checks if a given flag has been set in the register
; 0 - register
; 1 - flag
; 2 - Exit eddress when the is set
.MACRO CHK_FLAG_SET
  push tmp

  ldi XH, high(@0)
  ldi XL, low(@0)
  ld tmp, X
  sbrs tmp, (1<<@1)
  rjmp @2

  pop tmp
.ENDMACRO


; --- Checks if a given flag has not been set in the register
; 0 - register
; 1 - flag
; 2 - Exit eddress when the is not set
.MACRO CHK_FLAG_CLR
  push tmp

  ldi XH, high(@0)
  ldi XL, low(@0)
  ld tmp, X
  sbrc tmp, (1<<@1)
  rjmp @2

  pop tmp
.ENDMACRO


