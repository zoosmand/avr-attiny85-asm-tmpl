;
; ATtiny85 Assembller Template
; init.inc
; This file contains initialization code.
;
; Created: 25.01.2025 4:40pm
; Author : Dmitry Slobodchikov
;

;/********************** START AFTER POWER UP OR RESET FROM **********************/
_RESET:
  clr R1
  out SREG, R1
  ldi tmp, high(RAMEND)
  out SPH, tmp
  ldi tmp, low(RAMEND)
  out SPL, tmp


;/******************** INIT EVENT AND MEASURE REGISTRY FLAGS  ********************/
INIT_FLAGS:
  clr _EREG_
  ; sbr _EREG_, (1<<_MIF_)

;/************************************ Timer *************************************/
;/*     (1/8000000)*1024*256 = 32.768ms      */
INIT_TIMER:
  cli
  in tmp, TCCR0B ; 11.9.3 p.79
  sbr tmp, (1<<CS02)|(1<<CS00) ; 1024
  out TCCR0B, tmp
  in tmp, TIMSK ; 11.9.7 p.81
  sbr tmp, (1<<TOIE0)
  out TIMSK, tmp
  clr tmp ; 256
  out TCNT0, tmp ; 11.9.4 p.80
  sei

; Init Second Counter
  ld SecCnt, X+

cli

;/*********************************** MCU ***************************************/
INIT_MCU:
  in tmp, MCUCR ; Enable Sleep Mode
  sbr tmp, (1<<SE) ; Idle mode
  out MCUCR, tmp

  ; Reduce Power Consumption
  in tmp, ACSR ; 16.2.2 p.120
  sbr tmp, (1<<ACD)
  out ACSR, tmp

  in tmp, PRR ; 7.5.2 p.38
  sbr tmp, (1<<PRADC)|(1<<PRUSI)|(1<<PRTIM1)
  out PRR, tmp


;/******************************* WatchDog Timer *********************************/
INIT_WATCHDOG:
  in tmp, WDTCR ; 8.5.2 p.45
  sbr tmp, (1<<WDCE)|(1<<WDE)
  out WDTCR, tmp
  sbr tmp, (1<<WDP3)|(1<<WDP0)|(1<<WDIE) ; 8s
  out WDTCR, tmp

sei


;/*********************************** LED ***************************************/
INIT_LED:
  sbi LEDDDR, LED0PIN
  ;sbi LEDPORT, LED0PIN


