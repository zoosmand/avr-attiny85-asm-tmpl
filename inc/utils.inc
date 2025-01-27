;
; ATTiny85 Assembller Template
; utils.inc
; This file contains vary utilities code.
;
; Created: 25.01.2025 4:40pm
; Author : Dmitry Slobodchikov
;


; --- Toggles LED
LED_TOGGLE:
  sbrs _EREG_, _LBF_
  ret

  sbis LEDPIN, LED0PIN
  rjmp _LED0PIN_H
  cbi LEDPORT, LED0PIN
  rjmp _RET_LED_TOGGLE

  _LED0PIN_H:
    sbi LEDPORT, LED0PIN
  
  _RET_LED_TOGGLE:
    cbr _EREG_, (1<<_LBF_)
    ret


; --- Activates MCU SLEEP Mode
SLEEP_MODE:
  sbrs _EREG_, _SMF_
  ret
  sei     ; Enable interrapts to wake up the MCU
  sleep
  ret


; --- Increments system quant
INC_QNT_CNT:
  sbrs _EREG_, _QIF_
  ret
  INC_CNT QntCnt
  cbr _EREG_, (1<<_QIF_)
  ret


; --- Increamnts seconds counter
INC_SEC_CNT:
  ldi XH, high(QntCnt)
  ldi XL, low(QntCnt)

  ld tmpH, X+
  ld tmpL, X

  cpi tmpL, low(SEC_THRESHOLD)
  brne _RET_INC_SEC_CNT
  cpi tmpH, high(SEC_THRESHOLD)
  brne _RET_INC_SEC_CNT

  clr R1
  st X, R1
  st -X, R1
  sbr _EREG_, (1<<_SIF_)

  _RET_INC_SEC_CNT:
    ret


; --- Scheduled activity (e.g. secondly)
SCH_SEC:
  sbrs _EREG_, _SIF_
  ret
  INC_CNT SecCnt
  cbr _EREG_, (1<<_SIF_)
  sbr _EREG_, (1<<_LBF_)  ; Raise flag to toggle LED
  ret
