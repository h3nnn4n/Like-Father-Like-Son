# Like Father Like Son

Rust and C are like father and son. One is destined to replace the other. They have their share of similarities but are not quite the same.
This repo aims to provide a simple proof of concept of compiling Rust code to a dylib/so file and loading it inside C.

## Was has been done

1. Pass a double and get a double
2. Define a struct in C/Rust, pass it from C to Rust, change it in Rust and print it back in C
3. Write into an array from C
4. Malloc memory inside Rust, initialize it and pass it back to C

# Why?

1. I want to know how
2. I have a [pro](https://github.com/h3nnn4n/garapa)[ject](https://github.com/h3nnn4n/garapa/tree/gabate) which I am proud of but it is written in C. I want it to be in rust. By loading Rust code in C I hope to slowly turn the thing into Rust. Piece by piece.
3. Rust is awesome. I want to bring this awesomeness into C.

