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


; Load Counter address
ldi YH, high(LedPrmBlue)
ldi YL, low(LedPrmBlue)
; Store Pause1
ldi tmpH, 0x00
ldi tmpL, 0x32
std Y+0x08, tmpH
std Y+0x09, tmpL
; Store Pause2
ldi tmpH, 0x00
ldi tmpL, 0x02
std Y+0x0a, tmpH
std Y+0x0b, tmpL
; Store LED PORT
ldi tmpH, high(LEDPORT)
ldi tmpL, low(LEDPORT)
std Y+0x0c, tmpH
std Y+0x0d, tmpL
; Store LED PIN
ldi tmp, (1<<LEDBLUE)
std Y+0x0e, tmp
; Clear temporary register
clr tmp
std Y+0x0f, tmp
; Store Pause1 source address
ldi tmpH, high(QntCnt)
ldi tmpL, low(QntCnt)
std Y+0x10, tmpH
std Y+0x11, tmpL
; Store Pause2 source address
ldi tmpH, high(SecCnt)
ldi tmpL, low(SecCnt)
std Y+0x12, tmpH
std Y+0x13, tmpL

; ; Load Counter address
; ldi YH, high(LedPrmGreen)
; ldi YL, low(LedPrmGreen)
; ; Store LED PORT
; ldi tmpH, high(LEDPORT)
; ldi tmpL, low(LEDPORT)
; std Y+0x08, tmpH
; std Y+0x09, tmpL
; ; Store LED PIN
; ldi tmp, (1<<LEDGREEN)
; std Y+0x0a, tmp
; ; Clear temporary register
; clr tmp
; std Y+0x0b, tmp

; ; Load Counter address
; ldi YH, high(LedPrmRed)
; ldi YL, low(LedPrmRed)
; ; Store LED PORT
; ldi tmpH, high(LEDPORT)
; ldi tmpL, low(LEDPORT)
; std Y+0x08, tmpH
; std Y+0x09, tmpL
; ; Store LED PIN
; ldi tmp, (1<<LEDRED)
; std Y+0x0a, tmp
; ; Clear temporary register
; clr tmp
; std Y+0x0b, tmp


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


