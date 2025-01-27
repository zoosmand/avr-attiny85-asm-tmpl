;
; ATTiny85 Assembller Template
; macroses.inc
; This file contains vary macroses.
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


; --- Increments counters by given address.
.MACRO INC_CNT
  ldi YH, high(@0)
  ldi YL, low(@0)
  ld tmpH, Y+
  ld tmpL, Y
  inc tmpL
  in tmp, SREG
  sbrc tmp, SREG_Z
  inc tmpH
  st Y, tmpL
  st -Y, tmpH

.ENDMACRO
