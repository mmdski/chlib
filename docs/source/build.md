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

### 1. Install LLVM

```
brew install llvm
```

### 2. Install lcov

```
brew install lcov
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

To initialize with coverage reports and memory tests
```
meson -Db_coverage=true -Db_lundef=false -Db_sanitize=address build
```

#### Build and run tests
The command to build and run tests is
```
ninja -C build test
```

To build, run tests, and run coverage reports
```
ninja -C build test coverage-html
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
