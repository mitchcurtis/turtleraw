![repostat](https://img.shields.io/badge/repo%20status-Active-brightgreen) ![qtver](https://img.shields.io/badge/qt5-5.12%2B-orange) ![qt6support](https://img.shields.io/badge/qt6-unsupported-red)

![screenshot](https://raw.githubusercontent.com/yeahitsjan/turtleraw/develop/.github/images/screenshot-1.png)

A dead-simple image viewer with a main focus on raw images and extensibility.

**NOTE**: TurtleRaw is currently pre-alpha software, which means that it can be normal that the program crashes or is missing functions. This ``README`` will also grow and shrink from time to time...

## Installation

Currently there are no binaries yet. But in the near future there will be different packages available for download. Since TurtleRaw is pre-alpha, it is recommended to build it manually.

## Build from source

Checkout the [BUILD](https://github.com/yeahitsjan/turtleraw/blob/develop/BUILD.md) guide on how to get started an build TurtleRaw from source.

## Known Issues

- **22.07.2021**: The QtHeifPlugin does not support ``QImageReader::size``. The image does not has a valid size, but can be opened. See [this](https://github.com/jakar/qt-heif-image-plugin/issues/20) for more infos.
- **20.07.2021**: The right click menu inside the folder browser has some style issues.

## License

[MIT.](https://github.com/yeahitsjan/turtleraw/blob/develop/LICENSE)