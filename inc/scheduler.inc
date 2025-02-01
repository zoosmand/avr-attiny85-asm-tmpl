;
; ATTiny85 Assembller Template
; scheduler.inc
; This file contains scheduler, aka periodical task runner code.
;
; Created: 29.01.2025 10:10am
; Author : Dmitry Slobodchikov
;



; --- Runs scheduled tasks
; 0 - counter
; 1 - interval
; 2 - threshold
; 3 - register
; 4 - flag
; 5 - return point
.MACRO SCHEDULER
  ; Load counter
  ldi ZL, low(@0)
  ldi ZH, high(@0)
  ld cntH, Z+
  ld cntL, Z
  ; Load task counter threshold
  ldi YL, low(@2)
  ldi YH, high(@2)
  ld _cntH, Y+
  ld _cntL, Y
  ; Compate counters
  cp cntL, _cntL
  brne @5 ; exit if not equal
  cp cntH, _cntH
  brne @5 ; exit if not equal

  ; Load schedule interval value
  ldi tmpH, high(@1)
  ldi tmpL, low(@1)
  ; Set the new threshold
  clc
  adc cntL, tmpL
  in tmp, SREG
  sbrc tmp, SREG_C
  inc cntH
  add cntH, tmpH
  ; Store the new threshold
  st Y, cntL
  st -Y, cntH
  ; Raise flag in the given registry
  ldi YH, high(@3)
  ldi YL, low(@3)
  ld tmp, Y
  sbr tmp, (1<<@4)
  st Y, tmp

.ENDMACRO

