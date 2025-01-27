;
; ATtiny85 Assembller Template
; utils.inc
; This file contains the utilities code.
;
; Created: 25.01.2025 4:40pm
; Author : Dmitry Slobodchikov
;


;/*********************************** LED Blink *********************************/
LED_BLINK:
  sbrs _EREG_, _LBF_
  ret

  sbis LEDPIN, LED0PIN
  rjmp _LED0PIN_H
  cbi LEDPORT, LED0PIN
  rjmp _RETURN

  _LED0PIN_H:
    sbi LEDPORT, LED0PIN
  
  _RETURN:
    cbr _EREG_, (1<<_LBF_)
    ret


;/************************** Turn the MCU into SLEEP Mode ***********************/
SLEEP_MODE:
  ; sei     ; Enable interrapts to wake up the MCU
  ; sleep
  ret


INC_QNT_CNT:
  sbrs _EREG_, _QIF_
  rjmp _RETURN_000
  INC_CNT QntCnt
  cbr _EREG_, (1<<_QIF_)

  _RETURN_000:
    ret



INC_SEC_CNT:
  ldi XH, high(QntCnt)
  ldi XL, low(QntCnt)

  ld tmpH, X+
  ld tmpL, X

  cpi tmpL, low(SEC_THRESHOLD)
  brne _RETURN_001
  cpi tmpH, high(SEC_THRESHOLD)
  brne _RETURN_001

  clr R1
  st X, R1
  st -X, R1
  sbr _EREG_, (1<<_SIF_)

  _RETURN_001:
    ret


INC_SEC:
  sbrs _EREG_, _SIF_
  rjmp _RETURN_002
  INC_CNT SecCnt
  cbr _EREG_, (1<<_SIF_)
  sbr _EREG_, (1<<_LBF_)  ; Command to run LED Blink

  _RETURN_002:
    ret
