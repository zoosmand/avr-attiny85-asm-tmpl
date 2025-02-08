;
; ATTiny85 Assembller Template
; led.inc
; This file contains LED related code.
;
; Created: 02.02.2025 8:30am
; Author : Dmitry Slobodchikov
;


; --- Runs Blue LED routine
LED_BLUE:
  ; write Blue Led parameter address onto cache
  ldi ZH, high(2*LedBluePrm)
  ldi ZL, low(2*LedBluePrm)
  mov tmpH, ZH
  mov tmpL, ZL
  ldi YH, high(LedCache)
  ldi YL, low(LedCache)
  st Y+, tmpH
  st Y+, tmpL
  ; write Blue Led stack address onto cache
  ldi ZH, high(LedBlueStack)
  ldi ZL, low(LedBlueStack)
  mov tmpH, ZH
  mov tmpL, ZL
  st Y+, tmpH
  st Y, tmpL
  ; run Led routine
  rcall LED
  ret


; --- Runs Green LED routine
LED_GREEN:
  ; write Green Led parameter address onto cache
  ldi ZH, high(2*LedGreenPrm)
  ldi ZL, low(2*LedGreenPrm)
  mov tmpH, ZH
  mov tmpL, ZL
  ldi YH, high(LedCache)
  ldi YL, low(LedCache)
  st Y+, tmpH
  st Y+, tmpL
  ; write Green Led stack address onto cache
  ldi ZH, high(LedGreenStack)
  ldi ZL, low(LedGreenStack)
  mov tmpH, ZH
  mov tmpL, ZL
  st Y+, tmpH
  st Y, tmpL
  ; run Led routine
  rcall LED
  ret


; --- Runs Red LED routine
LED_RED:
  ; write Red Led parameter address onto cache
  ldi ZH, high(2*LedRedPrm)
  ldi ZL, low(2*LedRedPrm)
  mov tmpH, ZH
  mov tmpL, ZL
  ldi YH, high(LedCache)
  ldi YL, low(LedCache)
  st Y+, tmpH
  st Y+, tmpL
  ; write Red Led stack address onto cache
  ldi ZH, high(LedRedStack)
  ldi ZL, low(LedRedStack)
  mov tmpH, ZH
  mov tmpL, ZL
  st Y+, tmpH
  st Y, tmpL
  ; run Led routine
  rcall LED
  ret


; --- Serves LEDs routine
LED:
  ; read command and route the program
  ; +++ get parameter address from .dseg 
  ldi YH, high(LedCache+2)
  ldi YL, low(LedCache+2)
  ld tmpH, Y+
  ld tmpL, Y
  mov YH, tmpH
  mov YL, tmpL
  ; +++ offset address for getting commands
  ldd tmp, Y+4
  cpi tmp, _LUP_
  breq _LED_UP
  cpi tmp, _LUC_
  breq _LED_UP_DELAY
  cpi tmp, _LDW_
  breq _LED_DOWN
  cpi tmp, _LDC_
  breq _LED_DOWN_DELAY
  ret

_LED_UP:
  rcall LED_UP
  ret

_LED_UP_DELAY:
  rcall LED_UP_DELAY
  ret

_LED_DOWN:
  rcall LED_DOWN
  ret

_LED_DOWN_DELAY:
  rcall LED_DOWN_DELAY
  ret

LED_UP:
  ; turn LED on
  ; +++ get parameter address from cache
  ldi ZH, high(LedCache)
  ldi ZL, low(LedCache)
  ld _cntH, Z+
  ld _cntL, Z
  mov ZH, _cntH
  mov ZL, _cntL
  lpm tmp, Z
  mov r1, tmp
  in tmp, PORTB
  or tmp, r1 
  out PORTB, tmp
  ; set up delay
  ; +++ get interval from cache
  adiw _cntH:_cntL, 2
  mov ZH, _cntH
  mov ZL, _cntL
  ; +++ reverse Big Endian
  lpm tmpL, Z+
  lpm tmpH, Z
  ; +++ get delay counter address from cache 
  ldi YH, high(LedCache+2)
  ldi YL, low(LedCache+2)
  ld _cntH, Y+
  ld _cntL, Y
  ; +++ offset for specific address
  adiw _cntH:_cntL, 2
  mov YH, _cntH
  mov YL, _cntL
  DELAY QntCnt, Y
  ; set Led command (_LUC_), write to cache
  ; +++ get command address from cache 
  ldi XH, high(LedCache+2)
  ldi XL, low(LedCache+2)
  ld _cntH, X+
  ld _cntL, X
  ; +++ offset for specific address
  adiw _cntH:_cntL, 4
  mov XH, _cntH
  mov XL, _cntL
  ld tmp, X
  andi tmp, _LCMSK_
  ori tmp, _LUC_
  st X, tmp
  ret

LED_UP_DELAY:
  ; check delay status
  ; +++ get delay counter address from cache 
  ldi YH, high(LedCache+2)
  ldi YL, low(LedCache+2)
  ld _cntH, Y+
  ld _cntL, Y
  ; +++ offset for specific address
  adiw _cntH:_cntL, 2
  mov YH, _cntH
  mov YL, _cntL
  DELAY_STATE QntCnt, Y, _LED_UP_DELAY_END
  ; set Led Down command (_LDW_), write to cache
  ; +++ get command address from cache 
  ldi XH, high(LedCache+2)
  ldi XL, low(LedCache+2)
  ld _cntH, X+
  ld _cntL, X
  ; +++ offset for specific address
  adiw _cntH:_cntL, 4
  mov XH, _cntH
  mov XL, _cntL
  ld tmp, X
  andi tmp, _LCMSK_
  ori tmp, _LDW_
  st X, tmp
  
  _LED_UP_DELAY_END:
    ret

LED_DOWN:
  ; turn LED off
  ; +++ get parameter address from cache 
  ldi ZH, high(LedCache)
  ldi ZL, low(LedCache)
  ld _cntH, Z+
  ld _cntL, Z
  mov ZH, _cntH
  mov ZL, _cntL
  lpm tmp, Z
  mov r0, tmp
  neg r0
  dec r0
  in tmp, PORTB
  and tmp, r0
  out PORTB, tmp
  ; set up delay
  ; +++ get interval from cache
  adiw _cntH:_cntL, 4
  mov ZH, _cntH
  mov ZL, _cntL
  ; +++ reverse Big Endian
  lpm tmpL, Z+
  lpm tmpH, Z
  ; +++ get delay counter address from cache
  ldi YH, high(LedCache+2)
  ldi YL, low(LedCache+2)
  ld _cntH, Y+
  ld _cntL, Y
  ; +++ offset for specific address
  adiw _cntH:_cntL, 2
  mov YH, _cntH
  mov YL, _cntL
  DELAY QntCnt, Y
  ; set Led command (_LDC_), write to cache
  ; +++ get command address from cache 
  ldi XH, high(LedCache+2)
  ldi XL, low(LedCache+2)
  ld _cntH, X+
  ld _cntL, X
  ; +++ offset for specific address
  adiw _cntH:_cntL, 4
  mov XH, _cntH
  mov XL, _cntL
  ld tmp, X
  andi tmp, _LCMSK_
  ori tmp, _LDC_
  st X, tmp
  ret

LED_DOWN_DELAY:
  ; check delay status
  ; +++ get delay counter address from cache 
  ldi YH, high(LedCache+2)
  ldi YL, low(LedCache+2)
  ld _cntH, Y+
  ld _cntL, Y
  ; +++ offset for specific address
  adiw _cntH:_cntL, 2
  mov YH, _cntH
  mov YL, _cntL
  DELAY_STATE QntCnt, Y, _LED_DOWN_DELAY_END
  ; clear Led commands
  ; +++ get command address from cache 
  ldi XH, high(LedCache+2)
  ldi XL, low(LedCache+2)
  ld _cntH, X+
  ld _cntL, X
  ; +++ offset for specific address
  adiw _cntH:_cntL, 4
  mov XH, _cntH
  mov XL, _cntL
  ld tmp, X
  andi tmp, _LCMSK_
  st X, tmp
  
  _LED_DOWN_DELAY_END:
    ret
