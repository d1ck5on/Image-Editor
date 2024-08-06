# Image Editor
Simple command line image processor for BMP.

## Supported format
Image Editor supports 24-bit BMP without compression and color table.

## Usage

```./ImageEditor {input_file} {output_file} [-{filter 1} <param 1> <param 2> ...] [-{filter 2} <param 1> <param 2> ...] ...```

For example:

```./ImageEditor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5```

When running without arguments, the program displays help.

## Filters

### Crop (```-crop <width> <height>```)
Crops the image to the specified width and height. The upper left part of the image is used.

### Grayscale (```-gs```)
Converts the image to grayscale.

### Negative (```-neg```)
Converts the image to negative.

### Sharpening (```-sharp```)
Just sharpening...

### Edge Detection (```-edge <threshold>```) 
Border selection. Pixels with a value higher than threshold are colored white, and the rest are colored black.

## Build

```
mkdir build
cd build
cmake ..
cmake --build .
```

## Test

```python3 test/test.py build/ImageEditor```