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
; 2 - register
; 3 - flag
.MACRO SCHEDULER
  ldi ZL, low(@0)
  ldi ZH, high(@0)

  ldi YL, low(@1+2)
  ldi YH, high(@1+2)

  ld cntH, Z+
  ld cntL, Z

  ld _cntH, Y+
  ld _cntL, Y

  ; Start compate registers
  cp cntL, _cntL
  brne _END_SCHEDULER
  cp cntH, _cntH
  brne _END_SCHEDULER

  ; Load schedule interval value
  ldi XL, low(@1)
  ldi XH, high(@1)

  ld tmpH, X+
  ld tmpL, X

  adc cntL, tmpL
  in tmp, SREG
  sbrc tmp, SREG_C
  inc cntH
  add cntH, tmpH

  ; Store the new next point
  st Y, cntL
  st -Y, cntH

  ; Raise flag in given registry
  ldi YH, high(@2)
  ldi YL, low(@2)
  ld tmp, Y
  sbr tmp, (1<<@3)
  st Y, tmp

  _END_SCHEDULER:

.ENDMACRO
