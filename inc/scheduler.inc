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
  ldi ZL, low(@0)
  ldi ZH, high(@0)

  ldi YL, low(@2)
  ldi YH, high(@2)

  ld cntH, Z+
  ld cntL, Z

  ld _cntH, Y+
  ld _cntL, Y

  ; Start compate registers
  cp cntL, _cntL
  brne @5
  cp cntH, _cntH
  brne @5

  ; Load schedule interval value
  ldi tmpH, high(@1)
  ldi tmpL, low(@1)

  adc cntL, tmpL
  in tmp, SREG
  sbrc tmp, SREG_C
  inc cntH
  add cntH, tmpH

  ; Store the new next point
  st Y, cntL
  st -Y, cntH

  ; Raise flag in given registry
  ldi YH, high(@3)
  ldi YL, low(@3)
  ld tmp, Y
  sbr tmp, (1<<@4)
  st Y, tmp

.ENDMACRO




; --- Set pause
; 0 - counter
; 1 - interval
; 2 - threshold
.MACRO PAUSE
  ldi ZL, low(@0)
  ldi ZH, high(@0)

  ldi YL, low(@2)
  ldi YH, high(@2)

  ld cntH, Z+
  ld cntL, Z

  ld _cntH, Y+
  ld _cntL, Y

  ldi tmpH, high(@1)
  ldi tmpL, low(@1)

  adc cntL, tmpL
  in tmp, SREG
  sbrc tmp, SREG_C
  inc cntH
  add cntH, tmpH

  st Y, cntL
  st -Y, cntH

.ENDMACRO




; --- Checks pause state
; 0 - counter
; 1 - threshold
; 2 - register
; 3 - flag
; 4 - exit link pause up
; 5 - exit link pause down
.MACRO PAUSE_STATE
  ldi XL, low(@2)
  ldi XH, high(@2)
  ld tmp, X

  sbrs tmp, @3
  rjmp @4

  ldi ZL, low(@0)
  ldi ZH, high(@0)

  ldi YL, low(@1)
  ldi YH, high(@1)

  ld cntH, Z+
  ld cntL, Z

  ld _cntH, Y+
  ld _cntL, Y

  ; Start compate registers
  cp cntL, _cntL
  brne @4
  cp cntH, _cntH
  brne @4

  rjmp @5

.ENDMACRO
