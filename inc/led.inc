
; --
LED_BLUE:
  ; Read Led Register
  ldi YH, high(LedReg)
  ldi YL, low(LedReg)
  ld tmp, Y
  andi tmp, ((1<<_BLF_)|0b111) ; three low bits are command, five high bits are LEDs
  ; Read command
  cpi tmp, (_LUP_|(1<<_BLF_))
  breq _LED_BLUE_UP
  cpi tmp, (_LUC_|(1<<_BLF_))
  breq _LED_BLUE_UP_DELAY
  cpi tmp, (_LDW_|(1<<_BLF_))
  breq _LED_BLUE_DOWN
  cpi tmp, (_LDC_|(1<<_BLF_))
  breq _LED_BLUE_DOWN_DELAY
  ret

_LED_BLUE_UP:
  rcall LED_BLUE_UP
  ret

_LED_BLUE_UP_DELAY:
  rcall LED_BLUE_UP_DELAY
  ret

_LED_BLUE_DOWN:
  rcall LED_BLUE_DOWN
  ret

_LED_BLUE_DOWN_DELAY:
  rcall LED_BLUE_DOWN_DELAY
  ret


LED_BLUE_UP:
  ; turn LED on
  ldi ZH, high(2*LedBluePrm)
  ldi ZL, low(2*LedBluePrm)
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
  ldi ZH, high(2*LedBluePrm)
  ldi ZL, low(2*LedBluePrm)
  lpm tmp, Z
  mov r0, tmp
  neg r0
  dec r0
  in tmp, PORTB
  and tmp, r0
  out PORTB, tmp
  ; set up a delay
  DELAY QntCnt, LedBlueStack+2, 25 ; 25ms delay, store threshold in the BlueLedStack
  ; set _LDC_ command onto LED registry
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
  ld tmp, X
  andi tmp, 0b11111000
  st X, tmp
  
  _LED_BLUE_DOWN_DELAY_END:
    ret






; --
LED_GREEN:
  ; Read Led Register
  ldi YH, high(LedReg)
  ldi YL, low(LedReg)
  ld tmp, Y
  andi tmp, ((1<<_GLF_)|0b111) ; three low bits are command, five high bits are LEDs
  ; Read command
  cpi tmp, (_LUP_|(1<<_GLF_))
  breq _LED_GREEN_UP
  cpi tmp, (_LUC_|(1<<_GLF_))
  breq _LED_GREEN_UP_DELAY
  cpi tmp, (_LDW_|(1<<_GLF_))
  breq _LED_GREEN_DOWN
  cpi tmp, (_LDC_|(1<<_GLF_))
  breq _LED_GREEN_DOWN_DELAY
  ret

_LED_GREEN_UP:
  rcall LED_GREEN_UP
  ret

_LED_GREEN_UP_DELAY:
  rcall LED_GREEN_UP_DELAY
  ret

_LED_GREEN_DOWN:
  rcall LED_GREEN_DOWN
  ret

_LED_GREEN_DOWN_DELAY:
  rcall LED_GREEN_DOWN_DELAY
  ret


LED_GREEN_UP:
  ; turn LED on
  ldi ZH, high(2*LedGreenPrm)
  ldi ZL, low(2*LedGreenPrm)
  lpm tmp, Z
  mov r1, tmp
  in tmp, PORTB
  or tmp, r1 
  out PORTB, tmp
  ; set up a delay
  DELAY QntCnt, LedGreenStack+2, 125 ; 25ms delay, store threshold in the GREENLedStack
  ; set _LUC_ aka check delay status command
  ldi XH, high(LedReg)
  ldi XL, low(LedReg)
  ld tmp, X
  andi tmp, 0b11111000
  ori tmp, _LUC_
  st X, tmp
  ret

LED_GREEN_UP_DELAY:
  ; check delay status
  DELAY_STATE QntCnt, LedGreenStack+2, _LED_GREEN_UP_DELAY_END
  ; set _LDW_ command onto LED registry
  ldi XH, high(LedReg)
  ldi XL, low(LedReg)
  ld tmp, X
  andi tmp, 0b11111000
  ori tmp, _LDW_
  st X, tmp
  
  _LED_GREEN_UP_DELAY_END:
    ret

LED_GREEN_DOWN:
  ; turn LED off
  ldi ZH, high(2*LedGreenPrm)
  ldi ZL, low(2*LedGreenPrm)
  lpm tmp, Z
  mov r0, tmp
  neg r0
  dec r0
  in tmp, PORTB
  and tmp, r0
  out PORTB, tmp
  ; set up a delay
  DELAY QntCnt, LedGreenStack+2, 25 ; 25ms delay, store threshold in the GREENLedStack
  ; set _LDC_ command onto LED registry
  ldi XH, high(LedReg)
  ldi XL, low(LedReg)
  ld tmp, X
  andi tmp, 0b11111000
  ori tmp, _LDC_
  st X, tmp
  ret

LED_GREEN_DOWN_DELAY:
  ; check delay status
  DELAY_STATE QntCnt, LedGreenStack+2, _LED_GREEN_DOWN_DELAY_END
  ; clear commands in LED registry 
  ldi XH, high(LedReg)
  ldi XL, low(LedReg)
  ld tmp, X
  andi tmp, 0b11111000
  st X, tmp
  
  _LED_GREEN_DOWN_DELAY_END:
    ret
