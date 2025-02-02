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
  add _cntL, tmpL
  adc _cntH, tmpH

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
  
  ; Store params counter address in to LedReg
  ldi YH, high(LedReg+2)
  ldi YL, low(LedReg+2)
  ldi tmpH, high(LedPrmBlue)
  ldi tmpL, low(LedPrmBlue)
  std Y+0, tmpH
  std Y+1, tmpL

  ; Set Blue LED BUSY flags in to LedReg
  ldi YH, high(LedReg)
  ldi YL, low(LedReg)
  ld tmp, Y
  ; cbr tmp, (1<<_BLAF_)
  sbr tmp, (1<<_BLBF_)
  st Y, tmp

  ; Store Blue LED UP Flag in to temporary register
  ldi YH, high(LedPrmBlue+0x0f)
  ldi YL, low(LedPrmBlue+0x0f)
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
  ldd tmp, Y+0xf
  andi tmp, (1<<_LUF_)
  cpi tmp, (1<<_LUF_)
  brne _RET_LED_UP
  ; Check Busy Flag
  ldd tmp, Y+0xf
  andi tmp, (1<<_LBF_)
  cpi tmp, (1<<_LBF_)
  breq _LED_UP_BUSY
  ; Set Busy Flag
  ldd tmp, Y+0xf
  sbr tmp, (1<<_LBF_)
  std Y+0xf, tmp

  ; ; TODO For other AVR chips determine PORT by paramater's address
  ; ; Read PORT board address
  ; ldd XH, Y+2
  ; ldd XL, Y+3

  ; Read PIN bit
  ldd tmp, Y+0xe

  mov R1, tmp
  in tmp, PORTB
  or tmp, R1 

  out PORTB, tmp
  DELAY Y+0x10, Y+0x08, Y+0x02

  ; LED is UP now, so exit
  rjmp _RET_LED_UP

  _LED_UP_BUSY:
    DELAY_STATE Y+0x10, Y+0x02, _RET_LED_UP, _LED_UP_READY

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
    ldd tmp, Y+0xf
    cbr tmp, (1<<_LBF_)|(1<<_LUF_)
    sbr tmp, (1<<_LDF_)
    std Y+0xf, tmp

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
  ldd tmp, Y+0xf
  andi tmp, (1<<_LDF_)
  cpi tmp, (1<<_LDF_)
  brne _RET_LED_DOWN
  ; Check Busy Flag
  ldd tmp, Y+0xf
  andi tmp, (1<<_LBF_)
  cpi tmp, (1<<_LBF_)
  breq _LED_DOWN_BUSY
  ; Set Busy Flag
  ldd tmp, Y+0xf
  sbr tmp, (1<<_LBF_)
  std Y+0xf, tmp
  ; ; TODO For other AVR chips determine PORT by paramater's address
  ; ; Read PORT board address
  ; ldd ZH, Y+2
  ; ldd ZL, Y+3

  ; Read PIN bit
  ldd tmp, Y+0xe
  mov R1, tmp
  neg R1
  dec R1

  in tmp, PORTB
  and tmp, R1

  out PORTB, tmp
  DELAY Y+0x12, Y+0x0a, Y+0x02

  ; LED is UP now, so exit
  rjmp _RET_LED_DOWN

  _LED_DOWN_BUSY:
    DELAY_STATE Y+0x12, Y+0x02, _RET_LED_DOWN, _LED_DOWN_READY

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
    ldd tmp, Y+0xf
    cbr tmp, (1<<_LBF_)|(1<<_LDF_)
    std Y+0xf, tmp
    ; Clear Active Flag in LED Regiser
    ld tmp, Z
    cbr tmp, (1<<_BLAF_)|(1<<_BLBF_)
    st Z, tmp

  _RET_LED_DOWN:
    ret

