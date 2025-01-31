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
  ; ldi YH, high(LedReg)
  ; ldi YL, low(LedReg)
  ; ld tmp, Y
  ; mov R0, tmp
  ; ldi tmp, (1<<_BLAF_)
  ; mov R1, tmp
  ; or R0, R1
  ; mov tmp, R0
  ; st Y, tmp


  ; ldd tmp, Y+1

  ; mov R0, tmp
  ; ldi tmp, (1<<_BLUF_)
  ; mov R1, tmp
  ; or R0, R1
  ; mov tmp, R0
  ; std Y+1, tmp

  ; ; Prepare Counter Address
  ; ldi YH, high(LedReg+4)
  ; ldi YL, low(LedReg+4)
  ; ldi tmpH, high(LedCntBlue)
  ; ldi tmpL, low(LedCntBlue)
  ; std Y+0, tmpH 
  ; std Y+1, tmpL 

  ; rcall LED
  ; ret
  ldi YH, high(LedReg)
  ldi YL, low(LedReg)
  ld tmp, Y

  sbrc tmp, _BLBF_
  rjmp _RET_LED_BLUE

  sbrs tmp, _BLAF_
  rjmp _RET_LED_BLUE
  
  
  ; ***

  ldi YH, high(LedReg+2)
  ldi YL, low(LedReg+2)
  ; Store Counter address
  ldi tmpH, high(LedCntBlue)
  ldi tmpL, low(LedCntBlue)
  std Y+0, tmpH
  std Y+1, tmpL

  ; ***

  ldi YH, high(LedReg)
  ldi YL, low(LedReg)
  ld tmp, Y
  ; cbr tmp, (1<<_BLAF_)
  sbr tmp, (1<<_BLBF_)
  st Y, tmp

  ; Store Leb UP flag
  ldi YH, high(LedCntBlue+5)
  ldi YL, low(LedCntBlue+5)
  clr tmp
  sbr tmp, (1<<_LUF_)
  st Y, tmp

  _RET_LED_BLUE:
    rcall LED_UP
    ret



; ; -- LED
; LED:
;   ; Load Flag from a tempopary register
;   ldi YH, high(LedReg+2)
;   ldi YL, low(LedReg+2)
;   ld tmp, Y
;   mov R0, tmp
;   ldi YH, high(LedReg)
;   ldi YL, low(LedReg)
;   ld tmp, Y
;   mov R1, tmp

;   ; Branch if Active Flag Down
;   and R1, R0
;   cp R1, R0
;   brne _RET_LED

;   ; Clear Active Flag
;   neg R1
;   eor R0, R1
;   and tmp, R0
;   st Y, tmp

;   ; Set Up Flag
;   ; Load Flag from a tempopary register
;   ldi YH, high(LedReg+3)
;   ldi YL, low(LedReg+3)
;   ld tmp, Y
;   mov R0, tmp
;   ldi YH, high(LedReg+1)
;   ldi YL, low(LedReg+1)
;   ld tmp, Y
;   or tmp, R0
;   st Y, tmp

;   ret

;   _RET_LED:
;     rcall LED_UP
;     rcall LED_DOWN
;     ret




; ---
LED_UP:

  ldi YH, high(LedReg)
  ldi YL, low(LedReg)
  ldd tmp, Y+5
  mov R0, Y
  mov R1, Y

  and R0, _LUF_
  cpi R0, _LUF_
  brne _RET_LED_UP

  and R1, _LBF_
  cpi R1, _LBF_
  breq _RET_LED_UP

  sbr tmp, (1<<_LBF_)
  std Y+5, tmp

  ldd tmpH, Y+2
  ldd tmpL, Y+3
  ldd tmp, Y+4

  sbi Y+2, 
  PAUSE QntCnt, 50, LedCntBlue

  ; ldi YH, high(LedReg+1)
  ; ldi YL, low(LedReg+1)
  ; ld tmp, Y
  ; mov R1, tmp

  ; push R1

  ; ; sbrs tmp, _BLUF_
  ; ; rjmp _LED_UP_PAUSE_UP

  ; ; Branch if Active Flag Down
  ; and R1, R0
  ; cp R1, R0
  ; brne _LED_UP_PAUSE_UP



  ; sbrc tmp, _LPBF_
  ; rjmp _RET_LED_UP

  ; sbr tmp, (1<<_LPBF_)
  ; st Y, tmp
  ; sbi LEDPORT, LEDBLUE
  ; PAUSE QntCnt, 50, LedCntBlue

  ; _RET_LED_UP:
  ;   ; 
  ;   PAUSE_STATE QntCnt, LedCntBlue, LedReg+1, _BLUF_, _LED_UP_PAUSE_UP, _LED_UP_PAUSE_DOWN

  ; _LED_UP_PAUSE_DOWN:
  ;   ldi YH, high(LedReg+1)
  ;   ldi YL, low(LedReg+1)
  ;   ld tmp, Y

  ;   cbr tmp, (1<<_BLUF_)|(1<<_LPBF_)
  ;   sbr tmp, (1<<_BLDF_)
  ;   st Y, tmp

  ;   ret
  
  _RET_LED_UP:
    ret



; ; ---
; LED_DOWN:

;   ldi YH, high(LedReg+1)
;   ldi YL, low(LedReg+1)
;   ld tmp, Y

;   sbrs tmp, _BLDF_
;   rjmp _RET_LED_DOWN

;   sbrc tmp, _LPBF_
;   rjmp _RET_LED_DOWN

;   sbr tmp, (1<<_LPBF_)
;   st Y, tmp
;   cbi LEDPORT, LEDBLUE
;   PAUSE SecCnt, 1, LedCntBlue

;   _RET_LED_DOWN:
;     ; 
;     PAUSE_STATE SecCnt, LedCntBlue, LedReg+1, _BLDF_, _LED_DOWN_PAUSE_UP, _LED_DOWN_PAUSE_DOWN

;   _LED_DOWN_PAUSE_DOWN:
;     ldi YH, high(LedReg+1)
;     ldi YL, low(LedReg+1)
;     ld tmp, Y

;     cbr tmp, (1<<_BLDF_)|(1<<_LPBF_)
;     st Y, tmp

;     ret
  
;   _LED_DOWN_PAUSE_UP:
;     ret

