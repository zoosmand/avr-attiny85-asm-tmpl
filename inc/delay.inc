;
; ATTiny85 Assembller Template
; delay.inc
; This file contains delay code.
;
; Created: 28.01.2025 4:20pm
; Author : Dmitry Slobodchikov
;



; --- Sets pause
; 0 - sourse counter address
; 1 - threshold counter
.MACRO DELAY
  ; Load source counter
  ldi XH, high(@0)
  ldi XL, low(@0)
  ld cntH, X+
  ld cntL, X
  ; Interval already loaded into tmpH:tmpL
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



; --- Simple delay
; 0 - counter value in us, or directly stored in R24:R25 regosters
.MACRO SIMPLE_DELAY
  push _cntL
  push _cntH
  .IF @0 > 0
  ; Load source counter
  ldi _cntH, high(@0)
  ldi _cntL, low(@0)
  .ENDIF

  _SIMPLE_DELAY_CYCLE:
    ; 1us on 8 MHz
    nop
    nop
    nop
    #if F_CPU==16 ; 1us on 16Mhz
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    ; nop
    #endif

    ; Decrement counter
    sbiw _cntH:_cntL, 1
    cpi _cntL, 0
    brne _SIMPLE_DELAY_CYCLE ; exit if positive
    cpi _cntH, 0
    brne _SIMPLE_DELAY_CYCLE ; exit if positive

    pop _cntH
    pop _cntL

.ENDMACRO
