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
  sbis LEDPIN, LED0PIN
  rjmp _LED0PIN_H
  cbi LEDPORT, LED0PIN
  rjmp _RETURN

  _LED0PIN_H:
    sbi LEDPORT, LED0PIN
  
  _RETURN:
    ; cbr _EREG_, (1<<_LBF_)
    ret


;/************************** Turn the MCU into SLEEP Mode ***********************/
SLEEP_MODE:
  ; sei     ; Enable interrapts to wake up the MCU
  ; sleep
  ret
