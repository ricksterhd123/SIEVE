# SIEVE
Sieve of Atkins implementation in C++ using libgmp compiled to wasm using emscripten, ran by node.js

## Remarks about libgmp
Looking at SIZE_MAX in stdint.h - it's potentially big enough to fit 64 bits unsigned long. libgmp doesn't
provide much benefit here besides useful arbitrary size integer type. I primarily wanted to see if I could compile it to WASM and use it.

### Node.js WASM via emscripten
```
Calculating primes up to 1048576
Got 82025 prime numbers

real    0m5.661s
user    0m5.754s
sys     0m0.132s
```

### GNU/Linux x86 via GCC
```
Calculating primes up to 1048576
Got 82025 prime numbers

real    0m1.028s
user    0m1.027s
sys     0m0.001s
```

This is as far as I've got with my sieve, generating primes up to 2 ^ 20 = 1048576, resulting in 82k primes in 5 seconds.

## Prerequisites
- Docker
- GNU/Linux x86
- Node.js LTS

## Setup
Use
- `bash run.sh`

Or alternatively,
- `bash build.sh`
- `node build/SIEVE.js`

## TODO?
- [] use better method or data structure?
- [] Try get primes up to 2 ^ 32 within a nice time
- [] Make it inteface with Javascript, load into demo github page

## References
- https://www.geeksforgeeks.org/sieve-of-atkin/
- https://github.com/mccricardo/sieve_of_atkin/blob/master/sieve_of_atkin.py#L31
