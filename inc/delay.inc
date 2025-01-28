;
; ATTiny85 Assembller Template
; delay.inc
; This file contains delay code.
;
; Created: 28.01.2025 4:20pm
; Author : Dmitry Slobodchikov
;


; ; --- Toggles LED
; TOGGLE_LED:
;   ; sbrs _EREG_, _TLF_
;   ; ret

;   sbis LEDPIN, LED0PIN
;   rjmp _LED0PIN_H
;   cbi LEDPORT, LED0PIN
;   ; cbr _EREG_, (1<<_TLF_)  ; Down LED flag to indicate that the process finished 
;   ret

;   _LED0PIN_H:
;     sbi LEDPORT, LED0PIN
;     ret


.MACRO DELAY
  ldi XH, high(@0)
  ldi XL, low(@0)
  ld tmpH, X+
  ld tmpL, X
  rcall _DELAY
.ENDMACRO


; --- Managed LED
_DELAY:
  ldi ZL, low(SecCnt)
  ldi ZH, high(SecCnt)

  ldi YL, low(DelayEnd)
  ldi YH, high(DelayEnd)

  ld cntH, Z+
  ld cntL, Z

  ld _cntH, Y+
  ld _cntL, Y

  cp cntL, _cntL
  brne _RET_MAN_LED
  cp cntH, _cntH
  brne _RET_MAN_LED


  ; sbrc _EREG_, _DLF_
  ; ret

  _SET_DELAY:
    adc cntL, tmpL 
    in tmp, SREG
    sbrc tmp, SREG_C
    inc cntH
    add cntH, tmpH

    st Y, cntL
    st -Y, cntH

    ; sbr _EREG_, (1<<_DLF_)

  _RET_MAN_LED:
    ret