# Codeshark

## Overview
Writing high-quality and elegant C/C++ code is hard, especially for beginners. Codeshark is a repository of C/C++ code on common data structures and algorithms. The goal of Codeshark is to demonstrate how to write **high-quality and easy-to-read C/C++ code**, being a good tutorial for learning and teaching; however, it's not designed to be used in production environment.


## Features
- **Clean and efficient memory use**: flexible, bug-free memory and pointer manipulation
- **Good coding standard**: easy to read source code
- **Reasonable source tree** multiple level source directories commonly used in large projects
- **Comprehensive tests**: rich test code, and also using Address Sanitizer to test memory bug
- **Minimal use of C++**: use only basic parts of C++, e.,g ```class``` and ```string```.


## Components

Data structures
- [x] linklist
- [x] stack
- [x] queue
- [x] hash table
- [x] binary tree(partial)
- [ ] graph


Algorithms
- [ ] math
- [ ] sort
- [ ] recursive
- [ ] dynamic programming
- [ ] greedy

## Environment

C/C++ is Linux and OSX friendly, and all code has been tested in major distributions of Linux(Centos, Fedora, Ubuntu) and OSX(x86, M1).

- Compiler: g++/clang++ with C++11 support
- Building: CMake (minimal 3.18)

One external dependency is ```libasan```, which is used to detect memory leak.
```
# Centos, Fedora
sudo dnf install libasan        

# Ubuntu
sudo apt-get install libasan0

# OSX
brew install libasan
```

## How to use Codeshark

### Building
Building Codeshark is easy with CMake.

```
mkdir build
cd build
cmake ../
make -j6
```

Make a symbolic link of the shared library.
```
ln -s $PWD/lib/libcodeshark.so $PWD/bin/libcodeshark.so

# Alternatively, link the library somewhere else;
sudo ln -s $PWD/lib/libcodeshark.so /usr/local/lib/libcodeshark.so

# We can also declare LD_LIBRARY_PATH as environment variable
echo LD_LIBRARY_PATH=$PWD/lib >> ~/.bashrc
source ~/.bashrc
```


### Using
There are several executables and one shared binary generated.
- ```lib\libcodeshark.so```: the shared library to link with executables
- ```bin\datastructures_test```: test program of datastructures_test
- ```bin\common_test```: test program of common module

### Reading

The source tree of Codeshark is structured as follows.

```\src```: core code of Codeshark
- ```\common```: common module
- ```\datastructures```: data structures module

```\tests```:

- ```\common_test```: test code of module common
- ```\datastructures_test```: test code of module data structures

```\bin```: executables

```\lib```: shared library

```\CMakeLists.txt```: top level CMakefile


## TODO
- Graph
- Algorithms

## License
Codeshark is open source under Apache 2.0 license. You can freely modify, distribute the code and contribute. 
