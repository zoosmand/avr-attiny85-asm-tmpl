;
; ATTiny85 Assembller Template
; interrupts.inc
; This file contains the code dedicated to interrupts' logic.
;
; Created: 25.01.2025 4:40pm
; Author : Dmitry Slobodchikov
;


; --- Watchdog
_WDT:
  push R1
  push R0
  in R0, SREG
  push R0
  push tmp

  wdr
  in tmp, WDTCR
  sbr tmp, (1<<WDIE)
  out WDTCR, tmp

  cbr _EREG_, (1<<_SMF_)

  _WDT_exit:
    pop tmp
    pop R0
    out SREG, R0
    pop R0
    pop R1
  reti


; Timer0 Counter
_TIMER0_OVF:
  push R1
  push R0
  in R0, SREG
  push R0
  push tmp

  ldi tmp, QNT_THRESHOLD
  out TCNT0, tmp

  sbr _EREG_, (1<<_QIF_)
  cbr _EREG_, (1<<_SMF_)
 
  _TIMER0_OVF_exit:
    pop tmp
    pop R0
    out SREG, R0
    pop R0
    pop R1
  reti
