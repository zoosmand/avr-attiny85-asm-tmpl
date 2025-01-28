;
; ATTiny85 Assembller Template
; utils.inc
; This file contains various utilities code.
;
; Created: 25.01.2025 4:40pm
; Author : Dmitry Slobodchikov
;


; ; --- Toggles LED
; LED_TOGGLE:
;   sbrs _EREG_, _LBF_
;   ret

;   sbis LEDPIN, LED0PIN
;   rjmp _LED0PIN_H
;   cbi LEDPORT, LED0PIN
;   rjmp _RET_LED_TOGGLE

;   _LED0PIN_H:
;     sbi LEDPORT, LED0PIN
  
;   _RET_LED_TOGGLE:
;     cbr _EREG_, (1<<_LBF_)
;     ret




; --- Toggles LED
TOGGLE_LED:
  sbis LEDPIN, LED0PIN
  rjmp _LED0PIN_H
  cbi LEDPORT, LED0PIN
  ret
  _LED0PIN_H:
    sbi LEDPORT, LED0PIN
    ret


MAN_LED:
  rcall TOGGLE_LED
  DELAY 3
  rcall TOGGLE_LED
  DELAY 5
  ret


; --- Activates MCU SLEEP Mode
SLEEP_MODE:
  sbrs _EREG_, _SMF_
  ret
  sei     ; Enable interrupts to wake up the MCU
  sleep
  ; Set Sleep Mode flas right after the MCU woke up
  ; The MCU to sleep on the next iteration
  sbr _EREG_, (1<<_SMF_)
  ret


; --- Increments system quant
INC_QNT_CNT:
  cli
  sbrs _EREG_, _QIF_
  rjmp _RET_INC_QNT_CNT
  INC_CNT QntCnt
  rcall INC_SEC_CNT
  cbr _EREG_, (1<<_QIF_)

  _RET_INC_QNT_CNT:
    sei
    ret


; --- Increments seconds counter
INC_SEC_CNT:
  ; cli
  ; sbrs _EREG_, _QIF_
  ; rjmp _RET_INC_SEC_CNT

  ldi XL, low(QntCnt)
  ldi XH, high(QntCnt)
  ldi YL, low(NextQnt)
  ldi YH, high(NextQnt)

  ; Load and compare the Low bytes
  ; exit if not equal
  ld cntH, X+
  ld cntL, X
  cp cntL, _cntL
  brne _RET_INC_SEC_CNT

  ; Load and compare the High bytes
  ; exit if not equal
  ld _cntH, Y+
  ld _cntL, Y
  cp cntH, _cntH
  brne _RET_INC_SEC_CNT

  ; Load limit
  ldi tmpL, low(SEC_THRESHOLD)
  ldi tmpH, high(SEC_THRESHOLD)

  ; Increase the next second quants counter value
  adc _cntL, tmpL
  in tmp, SREG
  sbrc tmp, SREG_C
  inc _cntH
  add _cntH, tmpH

  ; Store the new value 
  st Y, _cntL
  st -Y, _cntH
  ; sbr _EREG_, (1<<_SIF_)
  ; Increment seconds counter
  INC_CNT SecCnt

  _RET_INC_SEC_CNT:
    ; sei
    ret


; --- Scheduled activity (e.g. secondly)
; Secondly
; SCH_SEC:
;   sbrs _EREG_, _SIF_
;   ret
;   INC_CNT SecCnt
;   cbr _EREG_, (1<<_SIF_)
;   ; sbr _EREG_, (1<<_LBF_)  ; Raise flag to toggle LED
;   ret


; Every 10 secobds
; SCH_10S:
;   sbrs _EREG_, _10F_
;   ret
;   cbr _EREG_, (1<<_10F_)
;   ret
