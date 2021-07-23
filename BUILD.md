## Build TurtleRaw from source

Building TurtleRaw is quite easy. It looks like more than it is. And it is not complex either...

### Dependencies

necessary:
- [Qt 5.12.x](https://download.qt.io/archive/qt/5.12/)
- [exiv2](https://exiv2.org/download.html)
- [QtRaw](https://gitlab.com/mardy/qtraw/)

optional:
- [QtHeifPlugin](https://github.com/jakar/qt-heif-image-plugin)

### Linux

I recommend to install Qt5 via the package manager of your Linux distro. Example for Ubuntu:

```
$ sudo apt install build-essential qt5-default qt5-qmake qtbase5-dev qtcreator qtdeclarative5-dev qtmultimedia5-dev libqt5multimedia5 libqtmultimedia5-plugins
```

Exiv2 needs to be build from source. Please note that [some dependencies](https://github.com/Exiv2/exiv2#5) are required before you can [build](https://github.com/Exiv2/exiv2#2-1) exiv2.

QtRaw and the optional QtHeifPlugin are pretty straightforward to install. Check out the corresponding [README](https://gitlab.com/mardy/qtraw/-/blob/master/README.md) [files](https://github.com/jakar/qt-heif-image-plugin/blob/master/README.md). For the QtHeifPlugin you can even use a PPA on Ubuntu.

#### Compiling TurtleRaw on Linux

Lets start with cloning the repo and fetching the submodules:

```
$ git clone https://github.com/yeahitsjan/turtleraw.git
$ cd turtleraw
$ git submodule init
$ git submodule update
```

This will fetch phantomstyle, easylogging++ and sol2 for you.

You can now simply build TurtleRaw:

```
$ mkdir out && cd out
$ qmake ..
$ make -j<number_of_cpu_cores>
```

That's it! You can now start with ``./turtleraw``.

*NOTE: The ``out`` directory is added to the ``.gitignore`` file. So you leave the working directory untouched when you want to contribute.*

### Windows

Currently, there is no *real* way on how to use Windows, because I never tested it. You can try it out on your own and report, what you experience. I recommend you to test out some issues I opened and worked on with my old account:

- [exiv2 on mingw64](https://github.com/Exiv2/exiv2/issues/1101)
- [FMeinicke/QtRaw](https://github.com/FMeinicke/QtRaw/issues/1)
- [rdi, playground](https://github.com/moowgle/rdi)

When there is a somewhat *stable* version of TurtleRaw I will take focus on a Windows version!

### macOS

Sadly, I am missing a device to do that. You can support me through [Liberapay](https://liberapay.com/jkowalewicz) if you want to give this a go :wink:

As it is a UNIX system, building should be as easy as on Linux. You can try out and report what you encounter, I try to help were I can!