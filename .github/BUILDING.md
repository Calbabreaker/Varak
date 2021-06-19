# Building Varak!

First make sure you have a compiler `cmake` and `conan` (can be installed
through pip) installed. Make sure conan uses the new ABI or else it will fail:

```sh
conan profile update settings.compiler.libcxx=libstdc++11 default
```

Now then make a build folder and cd into it and do these commands to get the
build files.

```sh
conan install .. --build
cmake .. -DCMAKE_BUILD_TYPE=DEBUG
```

Then use your output buildset to compile everything. For example `make`.
