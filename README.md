# AVR Assemble Programming Project

## ATTiny85, Initial Template

### Tips & Tricks

~~~ asm
_DISPLAY_ERROR:
  ldi YH, high(displaySymbols)
  ldi YL, low(displaySymbols)
  ldi tmp, 0x01
  std Y+0, tmp
  ldi tmp, 0x0e
  std Y+1, tmp
  std Y+2, tmp
  ldi tmp, 0x0d
  std Y+3, tmp
~~~


C:\Program Files (x86)\Atmel\Studio\7.0\packs\atmel\ATtiny_DFP\1.10.348\avrasm\inc\tn85def.inc

---

&copy; 2017-2025, Askug Ltd.