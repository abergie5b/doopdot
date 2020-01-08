### DoopDot: A C++ Image Processing Library

- Supported image formats
    - PGM and PPM
    - JPEG

- Algorithms

    - Resizing
        - bilinear interpolation
        - nearest neighbor
        - bicubic interpolation
        - resampling

    - Convolution
        - greyscale and rgb kernel convolutions
        - gaussian kernel generation

    - Pixel Filtering
        - median
        - laplacian
        - maximum and minimum
        - sobel
        - prewitt

    - Histogram Computation
        - histogram transform and visualization
        - contrast equalization via cumulative distribution function

    - Rotations and Other Transformations
        - 90 degree rotation
        - negative transformation
        - inverting channels
        - convert rgb to greyscale 

- Utilities

    - convert PGM and/or PPM to JPEG (and vice versa)
    - write image files from memory to filesystem

- Build

    1. clone the repository
    2. create a doopdot/build directory
    3. cd into the doopdot/build directory
    4. run ```cmake ..```
    5. run ```make doopdot```

- Usage

    - For development, a single ```doopdot::Image``` class can be used for all formats. Methods for each algorithm modify the image in-place.
    - For command line or scripting, the executable can be run ```doopdot <file> <actions> [params] [-w <path>][-v]```. For example ```./doopdot <input_filepath> resize bilinear 256 256 -w <output_filepath>```.

