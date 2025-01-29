;
; ATTiny85 Assembller Template
; utils.inc
; This file contains various utilities code.
;
; Created: 25.01.2025 4:40pm
; Author : Dmitry Slobodchikov
;


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
  rcall INC_SEC_CNT
  INC_CNT QntCnt
  cbr _EREG_, (1<<_QIF_)

  _RET_INC_QNT_CNT:
    sei
    ret


; --- Increments seconds counter
INC_SEC_CNT:
  ldi XL, low(QntCnt)
  ldi XH, high(QntCnt)
  ldi YL, low(QntCnt+2)
  ldi YH, high(QntCnt+2)

  ; Load and compare the Low bytes
  ; exit if not equal
  ld cntH, X+
  ld cntL, X
  ld _cntH, Y+
  ld _cntL, Y

  cp cntL, _cntL
  brne _RET_INC_SEC_CNT

  ; Compare the High bytes
  ; exit if not equal
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
  ; Increment seconds counter
  INC_CNT SecCnt

  _RET_INC_SEC_CNT:
    ret

