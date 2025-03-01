;
; ATTiny85 Assembller Template
; vectors.inc
; This file contains the code dedicated to the interrupt vectors logic.
;
; Created: 25.01.2025 4:40pm
; Author : Dmitry Slobodchikov
;


rjmp _RESET           ; Reset
rjmp _INT0            ; IRQ0
rjmp _PCINT0          ; PCINT0
rjmp _TIMER1_COMPA    ; Timer1 CompareA
rjmp _TIMER1_OVF      ; Timer1 Overflow
rjmp _TIMER0_OVF      ; Timer0 Overflow
rjmp _EE_RDY          ; EEPROM Ready
rjmp _ANA_COMP        ; Analog Comparator
rjmp _ADC             ; ADC Conversion Complete
rjmp _TIMER1_COMPB    ; Timer1 CompareB
rjmp _TIMER0_COMPA    ; Timer0 CompareA
rjmp _TIMER0_COMPB    ; Timer0 CompareB
rjmp _WDT             ; Watchdog Timeout
rjmp _USI_START       ; USI Start
rjmp _USI_OVF         ; USI Overflow


; --- Interrupt Vectors
_INT0:
_PCINT0:
_TIMER1_COMPA:
_TIMER1_OVF:
;_TIMER0_OVF:         ; This interrupt code is moved to interrupts.inc file.
_EE_RDY:
_ANA_COMP:
_ADC:
_TIMER1_COMPB:
_TIMER0_COMPA:
_TIMER0_COMPB:
;_WDT:                ; This interrupt code is moved to interrupts.inc file.
_USI_START:
_USI_OVF:

rjmp 0
