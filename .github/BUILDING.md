# Building Varak!

First make sure you have a compiler (`gcc`, `clang`, `mscv`, etc), `cmake` and
`conan` (can be installed using `pip install --user conan`) installed. Also
install `ccache` for faster build times.


Now make a build folder, cd into it then run cmake to get the build files:

```sh
cmake .. 
```

You could also use cmake-gui or ccmake.

Then use your output buildset to compile Varak. For example `make` or Visual Studio.

Make sure to run Varak executables like VarakEditor (at
`build/target/varak_editor/VarakEditor`) from the root directory of the
project.
