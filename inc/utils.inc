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




; -- LED
LED:
  ldi YH, high(LedReg)
  ldi YL, low(LedReg)
  ld tmp, Y
  
  sbrs tmp, _BLAF_
  rjmp _RET_LED

  cbr tmp, (1<<_BLAF_)
  st Y, tmp

  ldi YH, high(LedReg+1)
  ldi YL, low(LedReg+1)
  ld tmp, Y

  sbr tmp, (1<<_BLUF_)
  st Y, tmp

  ret


  _RET_LED:
    rcall LED_UP
    rcall LED_DOWN
    ret




; ---
LED_UP:

  ldi YH, high(LedReg+1)
  ldi YL, low(LedReg+1)
  ld tmp, Y

  sbrs tmp, _BLUF_
  rjmp _LED_UP_PAUSE_UP

  sbrc tmp, _LPBF_
  rjmp _RET_LED_UP

  sbr tmp, (1<<_LPBF_)
  st Y, tmp
  sbi LEDPORT, LEDBLUE
  PAUSE QntCnt, 50, LedCnt

  _RET_LED_UP:
    ; 
    PAUSE_STATE QntCnt, LedCnt, LedReg+1, _BLUF_, _LED_UP_PAUSE_UP, _LED_UP_PAUSE_DOWN

  _LED_UP_PAUSE_DOWN:
    ldi YH, high(LedReg+1)
    ldi YL, low(LedReg+1)
    ld tmp, Y

    cbr tmp, (1<<_BLUF_)|(1<<_LPBF_)
    sbr tmp, (1<<_BLDF_)
    st Y, tmp

    ret
  
  _LED_UP_PAUSE_UP:
    ret



; ---
LED_DOWN:

  ldi YH, high(LedReg+1)
  ldi YL, low(LedReg+1)
  ld tmp, Y

  sbrs tmp, _BLDF_
  rjmp _RET_LED_DOWN

  sbrc tmp, _LPBF_
  rjmp _RET_LED_DOWN

  sbr tmp, (1<<_LPBF_)
  st Y, tmp
  cbi LEDPORT, LEDBLUE
  PAUSE SecCnt, 1, LedCnt

  _RET_LED_DOWN:
    ; 
    PAUSE_STATE SecCnt, LedCnt, LedReg+1, _BLDF_, _LED_DOWN_PAUSE_UP, _LED_DOWN_PAUSE_DOWN

  _LED_DOWN_PAUSE_DOWN:
    ldi YH, high(LedReg+1)
    ldi YL, low(LedReg+1)
    ld tmp, Y

    cbr tmp, (1<<_BLDF_)|(1<<_LPBF_)
    st Y, tmp

    ret
  
  _LED_DOWN_PAUSE_UP:
    ret

