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
; 3 - command
; 4 - task to run
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
  brne _RUNNER ; exit if not equal
  cp cntH, _cntH
  brne _RUNNER ; exit if not equal
  ; Set the new threshold
  ldi tmpH, high(@1)
  ldi tmpL, low(@1)
  add cntL, tmpL
  adc cntH, tmpH
  st Y, cntL
  st -Y, cntH
  ; Set the command
  ldi YL, low(@2+4)
  ldi YH, high(@2+4)
  ldi tmp, @3
  st Y, tmp
  _RUNNER:
    rcall @4

.ENDMACRO

