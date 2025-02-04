
; --
LED_BLUE:
  ; Read Led Register
  ldi YH, high(LedReg)
  ldi YL, low(LedReg)
  ld tmp, Y
  andi tmp, (_BLF_|0b111) ; three low bits are command, five high bits are LEDs
  ; Read command
  cpi tmp, (_LUP_|_BLF_)
  breq LED_BLUE_UP
  cpi tmp, (_LUC_|_BLF_)
  breq LED_BLUE_UP_DELAY
  cpi tmp, (_LDW_|_BLF_)
  breq LED_BLUE_DOWN
  cpi tmp, (_LDC_|_BLF_)
  breq _LED_BLUE_DOWN_DELAY

  ret

_LED_BLUE_DOWN_DELAY:
  rcall LED_BLUE_DOWN_DELAY


LED_BLUE_UP:
  ; turn LED on
  ldi ZH, high(2*LebBluePrm)
  ldi ZL, low(2*LebBluePrm)
  lpm tmp, Z
  mov r1, tmp
  in tmp, PORTB
  or tmp, r1 
  out PORTB, tmp
  ; set up a delay
  DELAY QntCnt, LedBlueStack+2, 25 ; 25ms delay, store threshold in the BlueLedStack
  ; set _LUC_ aka check delay status command
  ldi XH, high(LedReg)
  ldi XL, low(LedReg)
  ld tmp, X
  andi tmp, 0b11111000
  ori tmp, _LUC_
  st X, tmp
  ret

LED_BLUE_UP_DELAY:
  ; check delay status
  DELAY_STATE QntCnt, LedBlueStack+2, _LED_BLUE_UP_DELAY_END
    ; set _LDW_ command onto LED registry 
    ; set _LUC_ aka check delay status command
    ldi XH, high(LedReg)
    ldi XL, low(LedReg)
    ld tmp, X
    andi tmp, 0b11111000
    ori tmp, _LDW_
    st X, tmp
  
  _LED_BLUE_UP_DELAY_END:
    ret

LED_BLUE_DOWN:
  ; turn LED off
  ldi ZH, high(2*LebBluePrm)
  ldi ZL, low(2*LebBluePrm)
  lpm tmp, Z
  mov r0, tmp
  neg r0
  dec r0
  in tmp, PORTB
  and tmp, r0
  out PORTB, tmp
  ; set up a delay
  DELAY QntCnt, LedBlueStack+2, 25 ; 25ms delay, store threshold in the BlueLedStack
  ldi XH, high(LedReg)
  ldi XL, low(LedReg)
  ld tmp, X
  andi tmp, 0b11111000
  ori tmp, _LDC_
  st X, tmp
  ret

LED_BLUE_DOWN_DELAY:
  ; check delay status
  DELAY_STATE QntCnt, LedBlueStack+2, _LED_BLUE_DOWN_DELAY_END
  ; clear commands in LED registry 
  ldi XH, high(LedReg)
  ldi XL, low(LedReg)
  ; ld tmp, X
  ; andi tmp, 0b11111000
  clr tmp
  st X, tmp
  
  _LED_BLUE_DOWN_DELAY_END:
    ret

  ; ; Read Flags
  ; ldi YH, high(LedReg)
  ; ldi YL, low(LedReg)
  ; ld tmp, Y
  ; sbrc tmp, _BLBF_
  ; rjmp _RET_LED_BLUE
  ; sbrs tmp, _BLAF_
  ; rjmp _RET_LED_BLUE
  
  ; ; Store params counter address in to LedReg
  ; ldi YH, high(LedReg+2)
  ; ldi YL, low(LedReg+2)
  ; ldi tmpH, high(LedPrmBlue)
  ; ldi tmpL, low(LedPrmBlue)
  ; std Y+0, tmpH
  ; std Y+1, tmpL

  ; ; Set Blue LED BUSY flags in to LedReg
  ; ldi YH, high(LedReg)
  ; ldi YL, low(LedReg)
  ; ld tmp, Y
  ; ; cbr tmp, (1<<_BLAF_)
  ; sbr tmp, (1<<_BLBF_)
  ; st Y, tmp

  ; ; Store Blue LED UP Flag in to temporary register
  ; ldi YH, high(LedPrmBlue+0x0f)
  ; ldi YL, low(LedPrmBlue+0x0f)
  ; clr tmp
  ; sbr tmp, (1<<_LUF_)
  ; st Y, tmp

  _RET_LED_BLUE:
    ; rcall LED_UP
    ; rcall LED_DOWN
    ret


; --
LED_GREEN:
;   ; Read Flags
;   ldi YH, high(LedReg)
;   ldi YL, low(LedReg)
;   ld tmp, Y
;   sbrc tmp, _GLBF_
;   rjmp _RET_LED_BLUE
;   sbrs tmp, _GLAF_
;   rjmp _RET_LED_BLUE
  
;   ; Store params counter address in to LedReg
;   ldi YH, high(LedReg+2)
;   ldi YL, low(LedReg+2)
;   ldi tmpH, high(LedPrmBlue)
;   ldi tmpL, low(LedPrmBlue)
;   std Y+0, tmpH
;   std Y+1, tmpL

;   ; Set Blue LED BUSY flags in to LedReg
;   ldi YH, high(LedReg)
;   ldi YL, low(LedReg)
;   ld tmp, Y
;   ; cbr tmp, (1<<_BLAF_)
;   sbr tmp, (1<<_GLBF_)
;   st Y, tmp

;   ; Store Blue LED UP Flag in to temporary register
;   ldi YH, high(LedPrmBlue+0x0f)
;   ldi YL, low(LedPrmBlue+0x0f)
;   clr tmp
;   sbr tmp, (1<<_LUF_)
;   st Y, tmp

  _RET_LED_GREEN:
    ; rcall LED_UP
    ; rcall LED_DOWN
    ret



; ; ---
; LED_UP:
;   ; Read LED paramener address
;   ldi ZH, high(LedReg+2)
;   ldi ZL, low(LedReg+2)
;   ldd tmpH, Z+0 
;   ldd tmpL, Z+1 
;   ; Load parameters address
;   mov YH, tmpH
;   mov YL, tmpL
;   ; Read temporary register
;   ; Check Up Flag
;   ldd tmp, Y+0xf
;   andi tmp, (1<<_LUF_)
;   cpi tmp, (1<<_LUF_)
;   brne _RET_LED_UP
;   ; Check Busy Flag
;   ldd tmp, Y+0xf
;   andi tmp, (1<<_LBF_)
;   cpi tmp, (1<<_LBF_)
;   breq _LED_UP_BUSY
;   ; Set Busy Flag
;   ldd tmp, Y+0xf
;   sbr tmp, (1<<_LBF_)
;   std Y+0xf, tmp

;   ; ; TODO For other AVR chips determine PORT by paramater's address
;   ; ; Read PORT board address
;   ; ldd XH, Y+2
;   ; ldd XL, Y+3

;   ; Read PIN bit
;   ldd tmp, Y+0xe

;   mov R1, tmp
;   in tmp, PORTB
;   or tmp, R1 

;   out PORTB, tmp
;   DELAY Y+0x10, Y+0x08, Y+0x02

;   ; LED is UP now, so exit
;   rjmp _RET_LED_UP

;   _LED_UP_BUSY:
;     DELAY_STATE Y+0x10, Y+0x02, _RET_LED_UP, _LED_UP_READY

;   _LED_UP_READY:
;     ; Read LED paramener address
;     ldi ZH, high(LedReg+2)
;     ldi ZL, low(LedReg+2)
;     ldd tmpH, Z+0 
;     ldd tmpL, Z+1 
;     ; Load parameters address
;     mov YH, tmpH
;     mov YL, tmpL
;     ; Clear Flags in the temporary register
;     ldd tmp, Y+0xf
;     cbr tmp, (1<<_LBF_)|(1<<_LUF_)
;     sbr tmp, (1<<_LDF_)
;     std Y+0xf, tmp

;   _RET_LED_UP:
;     ret



; ; ---
; LED_DOWN:
;   ; Read LED paramener address
;   ldi ZH, high(LedReg+2)
;   ldi ZL, low(LedReg+2)
;   ldd tmpH, Z+0 
;   ldd tmpL, Z+1 
;   ; Load parameters address
;   mov YH, tmpH
;   mov YL, tmpL
;   ; Read temporary register
;   ; Check Up Flag
;   ldd tmp, Y+0xf
;   andi tmp, (1<<_LDF_)
;   cpi tmp, (1<<_LDF_)
;   brne _RET_LED_DOWN
;   ; Check Busy Flag
;   ldd tmp, Y+0xf
;   andi tmp, (1<<_LBF_)
;   cpi tmp, (1<<_LBF_)
;   breq _LED_DOWN_BUSY
;   ; Set Busy Flag
;   ldd tmp, Y+0xf
;   sbr tmp, (1<<_LBF_)
;   std Y+0xf, tmp
;   ; ; TODO For other AVR chips determine PORT by paramater's address
;   ; ; Read PORT board address
;   ; ldd ZH, Y+2
;   ; ldd ZL, Y+3

;   ; Read PIN bit
;   ldd tmp, Y+0xe
;   mov R1, tmp
;   neg R1
;   dec R1

;   in tmp, PORTB
;   and tmp, R1

;   out PORTB, tmp
;   DELAY Y+0x12, Y+0x0a, Y+0x02

;   ; LED is UP now, so exit
;   rjmp _RET_LED_DOWN

;   _LED_DOWN_BUSY:
;     DELAY_STATE Y+0x12, Y+0x02, _RET_LED_DOWN, _LED_DOWN_READY

;   _LED_DOWN_READY:
;     ; Read LED paramener address 
;     ldi ZH, high(LedReg)
;     ldi ZL, low(LedReg)
;     ldd tmpH, Z+2
;     ldd tmpL, Z+3
;     ; Load parameters address
;     mov YH, tmpH
;     mov YL, tmpL
;     ; Clear Flags in the temporary register
;     ldd tmp, Y+0xf
;     cbr tmp, (1<<_LBF_)|(1<<_LDF_)
;     std Y+0xf, tmp
;     ; Clear Active Flag in LED Regiser
;     ld tmp, Z
;     cbr tmp, (1<<_BLAF_)|(1<<_BLBF_)
;     st Z, tmp

;   _RET_LED_DOWN:
;     ret

