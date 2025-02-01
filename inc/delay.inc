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
  ldd XH, @0+0
  ldd XL, @0+1
  ld cntH, X+
  ld cntL, X
  ; Load interval
  ldd _cntH, @2+0
  ldd _cntL, @2+1
  ; Load threshold counter
  ldd tmpH, @1+0
  ldd tmpL, @1+1
  ; Set new threshold
  clc
  adc cntL, tmpL
  in tmp, SREG
  sbrc tmp, SREG_C
  inc cntH
  add cntH, tmpH
  ; Store new threshold
  std @2+0, cntH
  std @2+1, cntL

.ENDMACRO



; --- Checks pause state
; 0 - source counter address
; 1 - threshold counter
; 2 - exit link pause runs
; 3 - exit link pause ends
.MACRO DELAY_STATE
  ; Load source counter
  ldd XH, @0+0
  ldd XL, @0+1
  ld cntH, X+
  ld cntL, X
  ; Load threshold counter
  ldd _cntH, @1+0
  ldd _cntL, @1+1
  ; Compare counters
  cp cntL, _cntL
  brne @2 ; exit if not equal
  cp cntH, _cntH
  brne @2 ; exit if not equal

  rjmp @3 ; exit if equal

.ENDMACRO
