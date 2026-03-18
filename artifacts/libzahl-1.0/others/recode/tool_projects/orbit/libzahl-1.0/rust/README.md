# libzahl - Big Integer Library (Rust Translation)

## NAME
libzahl - Big integer library

## ETYMOLOGY
The bold uppercase 'Z' which represents the set of all integers is derived from the german word 'zahlen', whose singular is 'zahl'.

## DESCRIPTION
libzahl is a Rust library for arbitrary size integers, translated from the original C implementation. This translation aims to provide the same functionality with Rust's memory safety guarantees.

The library provides operations for big integer arithmetic including:
- Basic arithmetic (addition, subtraction, multiplication, division)
- Modular arithmetic
- Bitwise operations
- Prime testing
- Random number generation
- String conversion and serialization

## NOTES
- This is a Rust translation of the original C libzahl library
- The library maintains the same API semantics as the C version where possible
- All code is 100% safe Rust with no unsafe blocks

## ORIGINAL RATIONALE
GMP MP cannot be used for robust programs. LibTomMath is too slow, probably because of all memory allocations, and has an nonintuitive API. Hebimath is promising, but I think it can be done better.

## LICENSE
MIT/X Consortium License - See LICENSE file for details
