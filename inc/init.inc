;
; ATTiny85 Assembller Template
; init.inc
; This file contains initialization code.
;
; Created: 25.01.2025 4:40pm
; Author : Dmitry Slobodchikov
;

; --- Entry point on Reset or Brown Level Event
_RESET:
  ; --- Set Global Interrupt Block, not to bother initialization steps
  cli
  clr R1
  out SREG, R1
  ldi tmp, high(RAMEND)
  out SPH, tmp
  ldi tmp, low(RAMEND)
  out SPL, tmp

; --- Init/erase SRAM data
INIT_DATA SRAM_START, INIT_RAM_CLR_CNT
; Clear the first half of RAM
; INIT_DATA SRAM_START, (SRAM_SIZE/2)-1
; Then, the second one
; INIT_DATA SRAM_START+(SRAM_SIZE/2)+1, (SRAM_SIZE/2)-1

; --- Init Flag Register
INIT_FLAGS:
  clr _EREG_
  ; sbr _EREG_, (1<<_MIF_)

; --- Init timer TIM0
INIT_TIMER:
  in tmp, TCCR0B ; 11.9.3 p.79
  sbr tmp, (1<<CS02)|(1<<CS00) ; 1024
  out TCCR0B, tmp
  in tmp, TIMSK ; 11.9.7 p.81
  sbr tmp, (1<<TOIE0)
  out TIMSK, tmp
  ldi tmp, QNT_THRESHOLD
  out TCNT0, tmp ; 11.9.4 p.80

; --- Init MCU
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

; --- Init Watchdog
INIT_WATCHDOG:
  in tmp, WDTCR ; 8.5.2 p.45
  sbr tmp, (1<<WDCE)|(1<<WDE)
  out WDTCR, tmp
  sbr tmp, (1<<WDP3)|(1<<WDP0)|(1<<WDIE) ; 8s
  out WDTCR, tmp

sei


; --- Init LEDs
INIT_LED:
  sbi LEDDDR, LEDBLUE
  #if _LEDBLUE_PD_
  sbi LEDPORT, LEDBLUE
  #endif

  sbi LEDDDR, LEDGREEN
  #if _LEDGREEN_PD_
  sbi LEDPORT, LEDGREEN
  #endif
  
  sbi LEDDDR, LEDRED
  #if _LEDRED_PD_
  sbi LEDPORT, LEDRED
  #endif


