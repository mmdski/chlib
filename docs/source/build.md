# Building chlib on macOS

## Install the build tools

### Install Homebrew
[Homebrew](https://brew.sh)

### Set up the Python environment

Create a virtual environment
```
python3 -m venv env
```

Install requirements
```
pip install -r requirements.txt
```

## Native build

### 1. Install GLib

```
brew install glib
```

### 2. Install LLVM

#### Install LLVM
```
brew install llvm
```

#### Set environment variables

Put the Homebrew LLVM in your PATH
```
echo 'export PATH="/opt/homebrew/opt/llvm/bin:$PATH"' >> ~/.zshrc
```

Tell Meson to use clang
```
echo 'export CC=clang' >> ~/.zshrc
```

### 3. Run Meson

#### Initialize build folder

Generally, the command is

```
meson <options> <build directory>
```

With building the Meson project, you have three options:
1. Build using `float` instead of `double`
2. Build the unit tests
3. Build the memory tests

`float` instead of `double`
```
-real_is_float=true
```

Build the unit tests
```
-Dunit_tests=true
```

Build the memory tests
```
-Db_sanitize=address
```

To use all three options and use `build` as the build directory, the command is
```
meson -Dreal_is_float=true -Dunit_tests=true -Db_sanitize=address build
```

#### Build and run tests
The command to build and run tests is
```
ninja -C build test
```

## Web Assembly build

### 1. Install Emscripten
```
brew install emscripten
```

### 2. Run Meson

#### Initialize the build directory
```
meson --cross wasm32.ini -Dprefix=$PWD"docs/source/static/" build.wasm32
```

#### Build and install the Web Assembly and JavaScript files
```
ninja -C build.wasm32 install
```
