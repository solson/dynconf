# dynconf

A simple demo for dynamically loading a shared library and running a function in
it. This could be used for configuring something like a window manager by having
the WM automatically rebuild and reload the user's config code in C, C++, Rust,
or some other native-code language.

## Running the demo

Build and run `dynconf_demo`:

```sh
make
./dynconf_demo
```

Hit enter to make it rebuild and reload `libconfig.so` and run the
`dynconf_init` function. Try editing `config.c` while it's running and hitting
enter to see your changes take effect without recompiling `main.c`.

## License

Licensed under the [ISC license](https://en.wikipedia.org/wiki/ISC_license). See
the LICENSE file.
