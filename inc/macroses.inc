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


; --- Initializes given variable
.MACRO INIT_VAR
  ldi YH, high(@0)
  ldi YL, low(@0)
  ld tmpH, Y+
  ld tmpL, Y
  ldi tmpH, high(@1)
  ldi tmpL, low(@1)
  st Y, tmpL
  st -Y, tmpH

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


; --- Toggles LED by given led and the correspondent flag
.MACRO LED_TOGGLE
  ldi YH, high(@0)
  ldi YL, low(@0)

  ld tmp, Y

  sbrs tmp, @1
  rjmp _EXIT_@0_@1_INACTIVE

  sbis LEDPIN, @2
  rjmp _EXIT_@1_H
  cbi LEDPORT, @2
  rjmp _EXIT_@0_@1

  _EXIT_@1_H:
    sbi LEDPORT, @2
  
  _EXIT_@0_@1:
    cbr tmp, (1<<@1)
    st Y, tmp

  _EXIT_@0_@1_INACTIVE:

.ENDMACRO
