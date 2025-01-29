;
; ATTiny85 Assembller Template
; scheduler.inc
; This file contains scheduler, aka periodical task runner code.
;
; Created: 29.01.2025 10:10am
; Author : Dmitry Slobodchikov
;


; --- Runs scheduled tasks
SCHEDULER:
  ldi ZL, low(SecCnt)
  ldi ZH, high(SecCnt)

  ldi YL, low(SchCnt+2)
  ldi YH, high(SchCnt+2)

  ld cntH, Z+
  ld cntL, Z

  ld _cntH, Y+
  ld _cntL, Y

  ; Start compate registers
  cp cntL, _cntL
  brne _RET_SCHEDULER
  cp cntH, _cntH
  brne _RET_SCHEDULER

  ; Load schedule interval value
  ldi XL, low(SchCnt)
  ldi XH, high(SchCnt)

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

  sbr _EREG_, (1<<_TBF_)

  _RET_SCHEDULER:
    ret
