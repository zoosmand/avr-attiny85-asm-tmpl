; --
LED_RED:
  ; read command and route the program
  ldi YH, high(LedRedStack+4)
  ldi YL, low(LedRedStack+4)
  ld tmp, Y
  cpi tmp, _LUP_
  breq _LED_RED_UP
  cpi tmp, _LUC_
  breq _LED_RED_UP_DELAY
  cpi tmp, _LDW_
  breq _LED_RED_DOWN
  cpi tmp, _LDC_
  breq _LED_RED_DOWN_DELAY
  ret

_LED_RED_UP:
  rcall LED_RED_UP
  ret

_LED_RED_UP_DELAY:
  rcall LED_RED_UP_DELAY
  ret

_LED_RED_DOWN:
  rcall LED_RED_DOWN
  ret

_LED_RED_DOWN_DELAY:
  rcall LED_RED_DOWN_DELAY
  ret


LED_RED_UP:
  ; turn LED on
  ldi ZH, high(2*LedRedPrm)
  ldi ZL, low(2*LedRedPrm)
  lpm tmp, Z
  mov r1, tmp
  in tmp, PORTB
  or tmp, r1 
  out PORTB, tmp
  ; set up a 25ms delay
  DELAY QntCnt, LedRedStack+2, 25
  ; set _LUC_ aka check delay status command
  ldi XH, high(LedRedStack+4)
  ldi XL, low(LedRedStack+4)
  ld tmp, X
  andi tmp, _LCMSK_
  ori tmp, _LUC_
  st X, tmp
  ret

LED_RED_UP_DELAY:
  ; check delay status
  DELAY_STATE QntCnt, LedRedStack+2, _LED_RED_UP_DELAY_END
  ; set _LDW_ command onto LED registry
  ldi XH, high(LedRedStack+4)
  ldi XL, low(LedRedStack+4)
  ld tmp, X
  andi tmp, _LCMSK_
  ori tmp, _LDW_
  st X, tmp
  
  _LED_RED_UP_DELAY_END:
    ret

LED_RED_DOWN:
  ; turn LED off
  ldi ZH, high(2*LedRedPrm)
  ldi ZL, low(2*LedRedPrm)
  lpm tmp, Z
  mov r0, tmp
  neg r0
  dec r0
  in tmp, PORTB
  and tmp, r0
  out PORTB, tmp
  ; set up a 25ms delay
  DELAY QntCnt, LedRedStack+2, 25
  ; set _LDC_ command onto LED registry
  ldi XH, high(LedRedStack+4)
  ldi XL, low(LedRedStack+4)
  ld tmp, X
  andi tmp, _LCMSK_
  ori tmp, _LDC_
  st X, tmp
  ret

LED_RED_DOWN_DELAY:
  ; check delay status
  DELAY_STATE QntCnt, LedRedStack+2, _LED_RED_DOWN_DELAY_END
  ; clear commands in LED registry 
  ldi XH, high(LedRedStack+4)
  ldi XL, low(LedRedStack+4)
  ld tmp, X
  andi tmp, _LCMSK_
  st X, tmp
  
  _LED_RED_DOWN_DELAY_END:
    ret
