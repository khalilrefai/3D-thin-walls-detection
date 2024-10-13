# 3D mesh thin walls detection
![screenshot](https://github.com/khalilrefai/3D-thin-walls-detection/blob/main/screenshot.PNG?raw=true)

## Overview

This C++ algorithm detects thin walls in a 3D mesh.

## Build and Run Instructions

Follow these steps to build and run the C++ implementation:

1. Create a build directory:

    ```bash
    mkdir build
    ```

2. Change into the build directory:

    ```bash
    cd build
    ```

3. Run CMake to configure the build:

    ```bash
    cmake ..
    ```

4. Build the project:

    ```bash
    cmake --build . --config Release
    ```

5. Execute the algorithm:

    ```bash
    ./thin-walls <input_filepath> <thickness_threshold>
    ```

Replace `<input_filepath>` and `<thickness_threshold>` with the actual file paths and thickness values.

## Usage

The algorithm takes a 3D mesh as input and detects thin walls based on the specified thickness threshold.

## Contributing

Contributions are welcome! If you'd like to contribute to this project, feel free to submit pull requests or open issues.

## License

This project is licensed under the [MIT License](LICENSE).
