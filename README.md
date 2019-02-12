# packedForest
A memory efficient and fast random forest which produces trees with fast prediction speeds.

To compile:

- Linux:

    `sudo apt install libomp-dev`

    ```sh
    make
    ```

- Windows:

    Install: [Visual Studio Build Tools](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2017)

    From the native build tools command prompt environment:

    ```cmd
    cl /EHsc src\fp.cpp /openmp
    ```