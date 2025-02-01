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


; --
LED_BLUE:
  ; Read Flags
  ldi YH, high(LedReg)
  ldi YL, low(LedReg)
  ld tmp, Y
  sbrc tmp, _BLBF_
  rjmp _RET_LED_BLUE
  sbrs tmp, _BLAF_
  rjmp _RET_LED_BLUE
  
  ; Store Counter address
  ldi YH, high(LedReg+2)
  ldi YL, low(LedReg+2)
  ldi tmpH, high(LedCntBlue)
  ldi tmpL, low(LedCntBlue)
  std Y+0, tmpH
  std Y+1, tmpL

  ; Redefine flags
  ldi YH, high(LedReg)
  ldi YL, low(LedReg)
  ld tmp, Y
  ; cbr tmp, (1<<_BLAF_)
  sbr tmp, (1<<_BLBF_)
  st Y, tmp

  ; Store Blue LED Flag
  ldi YH, high(LedCntBlue+5)
  ldi YL, low(LedCntBlue+5)
  clr tmp
  sbr tmp, (1<<_LUF_)
  st Y, tmp

  _RET_LED_BLUE:
    rcall LED_UP
    rcall LED_DOWN
    ret



; ---
LED_UP:
  ; Read LED paramener address
  ldi ZH, high(LedReg+2)
  ldi ZL, low(LedReg+2)
  ldd tmpH, Z+0 
  ldd tmpL, Z+1 
  ; Load parameters address
  mov YH, tmpH
  mov YL, tmpL
  ; Read temporary register
  ; Check Up Flag
  ldd tmp, Y+5
  andi tmp, (1<<_LUF_)
  cpi tmp, (1<<_LUF_)
  brne _RET_LED_UP
  ; Check Busy Flag
  ldd tmp, Y+5
  andi tmp, (1<<_LBF_)
  cpi tmp, (1<<_LBF_)
  breq _LED_UP_BUSY
  ; Set Busy Flag
  ldd tmp, Y+5
  sbr tmp, (1<<_LBF_)
  std Y+5, tmp
  ; Read PIN board address
  ldd ZH, Y+2
  ldd ZL, Y+3
  ; ldd tmpL, Y+3
  ; Read PIN bit
  ldd tmp, Y+4

  ; TODO Update PORTB as a normal register
  mov R1, tmp
  in tmp, PORTB
  or tmp, R1 

  out PORTB, tmp
  PAUSE QntCnt, 50, LedCntBlue

  ; LED is UP now, so exit
  rjmp _RET_LED_UP

  _LED_UP_BUSY:
    ; TODO Get pause state
    ; ldd tmp, Y+5
    ; std Y+5, tmp

  _LED_UP_READY:
    ; Read LED paramener address
    ldi ZH, high(LedReg+2)
    ldi ZL, low(LedReg+2)
    ldd tmpH, Z+0 
    ldd tmpL, Z+1 
    ; Load parameters address
    mov YH, tmpH
    mov YL, tmpL
    ; Clear Flags in the temporary register
    ldd tmp, Y+5
    cbr tmp, (1<<_LBF_)|(1<<_LUF_)
    sbr tmp, (1<<_LDF_)
    std Y+5, tmp

  _RET_LED_UP:
    ret



; ---
LED_DOWN:
  ; Read LED paramener address
  ldi ZH, high(LedReg+2)
  ldi ZL, low(LedReg+2)
  ldd tmpH, Z+0 
  ldd tmpL, Z+1 
  ; Load parameters address
  mov YH, tmpH
  mov YL, tmpL
  ; Read temporary register
  ; Check Up Flag
  ldd tmp, Y+5
  andi tmp, (1<<_LDF_)
  cpi tmp, (1<<_LDF_)
  brne _RET_LED_DOWN
  ; Check Busy Flag
  ldd tmp, Y+5
  andi tmp, (1<<_LBF_)
  cpi tmp, (1<<_LBF_)
  breq _LED_DOWN_BUSY
  ; Set Busy Flag
  ldd tmp, Y+5
  sbr tmp, (1<<_LBF_)
  std Y+5, tmp
  ; Read PIN board address
  ldd ZH, Y+2
  ldd ZL, Y+3
  ; ldd tmpL, Y+3
  ; Read PIN bit
  ldd tmp, Y+4
  mov R1, tmp
  neg R1
  dec R1

  ; TODO Update PORTB as a normal register
  in tmp, PORTB
  and tmp, R1

  out PORTB, tmp
  PAUSE QntCnt, 50, LedCntBlue

  ; LED is UP now, so exit
  rjmp _RET_LED_DOWN

  _LED_DOWN_BUSY:
    ; TODO Get pause state
    ; ldd tmp, Y+5
    ; std Y+5, tmp

  _LED_DOWN_READY:
    ; Read LED paramener address
    ldi ZH, high(LedReg)
    ldi ZL, low(LedReg)
    ldd tmpH, Z+2
    ldd tmpL, Z+3
    ; Load parameters address
    mov YH, tmpH
    mov YL, tmpL
    ; Clear Flags in the temporary register
    ldd tmp, Y+5
    cbr tmp, (1<<_LBF_)|(1<<_LDF_)
    std Y+5, tmp
    ; Clear Active Flag in LED Regiser
    ld tmp, Z
    cbr tmp, (1<<_BLAF_)|(1<<_BLBF_)
    st Z, tmp

  _RET_LED_DOWN:
    ret

