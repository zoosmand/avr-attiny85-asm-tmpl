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
  ; Load interval
  ldi tmpH, high(@2)
  ldi tmpL, low(@2)
  ld cntL, X
  ; Set new threshold
  add cntL, tmpL
  adc cntH, tmpH
  ; Store new threshold
  std @1+0, cntH
  std @1+1, cntL

.ENDMACRO



; --- Checks pause state
; 0 - source counter address
; 1 - threshold counter
; 2 - exit link pause runs
.MACRO DELAY_STATE
  ; Load threshold counter
  ldd _cntH, @1+0
  ldd _cntL, @1+1
  ; Load source counter
  ldi XH, high(@0)
  ldi XL, low(@0)
  ld cntH, X+
  ld cntL, X
  ; Compare counters
  cp cntL, _cntL
  brne @2 ; exit if not equal
  cp cntH, _cntH
  brne @2 ; exit if not equal

.ENDMACRO
