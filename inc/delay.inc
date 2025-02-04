;
; ATTiny85 Assembller Template
; delay.inc
; This file contains delay code.
;
; Created: 28.01.2025 4:20pm
; Author : Dmitry Slobodchikov
;



; --- Set pause
; 0 - sourse counter address
; 1 - interval
; 2 - threshold counter
.MACRO DELAY
  ; Load source counter
  ldi XH, high(@0)
  ldi XL, low(@0)
  ld cntH, X+
  ld cntL, X
  ; Load interval
  ldi tmpH, high(@2)
  ldi tmpL, low(@2)
  ; Set new threshold
  add cntL, tmpL
  adc cntH, tmpH
  ; Store new threshold
  ldi XH, high(@1)
  ldi XL, low(@1)
  st X+, cntH
  st X, cntL

.ENDMACRO



; --- Checks pause state
; 0 - source counter address
; 1 - threshold counter
; 2 - exit link pause runs
; 3 - exit link pause ends
.MACRO DELAY_STATE
  ; Load source counter
  ldi XH, high(@0)
  ldi XL, low(@0)
  ld cntH, X+
  ld cntL, X
  ; Load threshold counter
  ldi XH, high(@1)
  ldi XL, low(@1)
  ld _cntH, X+
  ld _cntL, X
  ; Compare counters
  ; TODO Fix comparison
  cp cntL, _cntL
  brne @2 ; exit if not equal
  cp cntH, _cntH
  brne @2 ; exit if not equal

.ENDMACRO
