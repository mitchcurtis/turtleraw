![repostat](https://img.shields.io/badge/repo%20status-Active-brightgreen) ![qtver](https://img.shields.io/badge/qt5-5.12%2B-orange) ![qt6support](https://img.shields.io/badge/qt6-unsupported-red)

![screenshot](https://raw.githubusercontent.com/yeahitsjan/turtleraw/develop/.github/images/screenshot-1.png)

A dead-simple image viewer with a main focus on raw images and extensibility.

**NOTE**: TurtleRaw is currently pre-alpha software, which means that it can be normal that the program crashes or is missing functions. This ``README`` will also grow and shrink from time to time...

## Build from source (linux)

Currently there are no binaries, so TurtleRaw must be built from source. Before we can start we need to setup our environment.

### Dependencies

It looks like more than it is. And it is not complex either... Dependencies should be available for all common distros, here for Ubuntu.

**[Qt 5.12+ (Qt6 is not supported)](https://download.qt.io/archive/qt/5.12/)**
```
$ sudo apt install build-essential qt5-default qt5-qmake qtbase5-dev qtcreator qtdeclarative5-dev qtmultimedia5-dev libqt5multimedia5 libqtmultimedia5-plugins
```

**[exiv2](https://exiv2.org/download.html)**

Download the source code from the website and unzip it. Then open a terminal and install required packages to build exiv2:

```
$ sudo apt install --yes build-essential git clang ccache python3 libxml2-utils cmake python3 libexpat1-dev libz-dev zlib1g-dev libssh-dev libcurl4-openssl-dev libgtest-dev google-mock
```

After that, simply build exiv2 with:

```
$ cd exiv2/
$ mkdir build && cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ make -j<number_of_cpu_cores>
$ make tests # if needed
$ sudo make install
```

**[QtRaw](https://gitlab.com/mardy/qtraw/)**

Just clone the repo and build the plugin (Libraw is needed):

```
$ sudo apt install libraw-dev
$ git clone https://gitlab.com/mardy/qtraw.git
$ cd qtraw/
$ mkdir build && cd build
$ qmake ..
$ make && sudo make install
```

Should be pretty fast. After that, QtRaw is installed as a global plugin on your system.

**[QtHeifPlugin](https://github.com/jakar/qt-heif-image-plugin)**

Either, on Ubuntu, use the PPA, or build it from source like QtRaw. Libheif is needed here.

*NOTE: The QtHeifPlugin is not needed to run TurtleRaw!*

### Compiling

After all dependencies have been installed, clone the repo and let's start:

```
$ git clone https://github.com/yeahitsjan/turtleraw.git
$ cd turtleraw/
$ git submodule init && git submodule update
$ mkdir out && cd out
$ qmake ..
$ make -j<number_of_cpu_cores>
$ ./turtleraw
```

*NOTE: Although they are there, the only submodules used are ``easylogging++`` and ``phantomstyle``. ``sol2`` will find its way later into TurtleRaw.*

And you are ready to go! The first time you start it, you will be asked for which file types TurtleRaw should be the default image viewer. Currently, however, this dialog does nothing (because of alpha LOL).

### Other platforms (macOS / Windows)

At the moment I'm focusing on building a stable Linux version. Since no platform dependent code is used, it should be easily run on these platforms as well. A Windows port will definitely be there soon, for macOS I'm missing the right device... but you can support me through Liberapay! :wink:

## Known Issues

- **22.07.2021**: The QtHeifPlugin does not support ``QImageReader::size``. The image does not has a valid size, but can be opened. See [this](https://github.com/jakar/qt-heif-image-plugin/issues/20) for more infos.

## License

[MIT.](https://github.com/yeahitsjan/turtleraw/blob/develop/LICENSE)