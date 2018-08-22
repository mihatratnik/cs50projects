# Questions

## What's `stdint.h`?

A C standard library, which provides developers with set of typedefs that specify exact-width integer types.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

For all above mentioned integer types we know exactly how big (in bits / bytes) they are and what is their minimum / maximum value, so we can predict, how much memory is needed for our program.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE = 1 byte; DWORD =  4 bytes; LONG = 4 bytes; WORD = 2 bytes.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

ASCII = BM; decimal = 66 77; hexadecimal = 0x424d.

## What's the difference between `bfSize` and `biSize`?

bfSize is included in BITMAFILEHEADER and is the size of the file (in bytes), where as biSize is included in BITMAPINFOHEADER and represents the number of bytes required by the structure of bitmap.

## What does it mean if `biHeight` is negative?

The bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

Probabily if it can not find the file.

## Why is the third argument to `fread` always `1` in our code?

This number represents number of units that the function should read and we want the functionto read only each unit at the time.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

fseek allowes us to change the location of the file pointer

## What is `SEEK_CUR`?

An argument in fseek fanction, that determines, that the change of the location will be relative to pointer's current location.

## Whodunit?

It was Professor Plum with the candlestick in the library.
