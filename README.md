# Resize and rotate image
> Resize and rotate image using OpenCV in C++


This project is a demo project for resize and rotate image using nearest neighbor search, bilinear interpolation and bicubic interpolation

## Installation
```
git clone https://github.com/hailiang194/resize-rotate-image.git
```

### Nearnest neighbor searching
Execution file is in ```nearest_neibor/build/``` folder

To execute type
```
./ResizeImage <image-path> <resize-ratio> [G]
```
Add ```G``` if you want gray scale image, otherwise it is going to color image

### Bilinear interpolation
Execution file is in ```bilinear/build/``` folder

To execute type
```
./ResizeImage <image-path> <resize-ratio> [G]
```
Add ```G``` if you want gray scale image, otherwise it is going to color image

### Bicubic interpolation
Execution file is in ```bicubic/build/``` folder

To execute type
```
./ResizeImage <image-path> <resize-ratio> [G]
```
Add ```G``` if you want gray scale image, otherwise it is going to color image

### Rotate image
Execution file is in ```rotate-bilinear/build/``` folder

To execute type
```
./RotateImage <image-path> <resize-ratio> [G]
```
Add ```G``` if you want gray scale image, otherwise it is going to color image

## Usage example

#### Original image
![original image](README-img/img.jpg)
#### Nearest neighbor searching with resize ratio = 4.4
![nearest neighbor searching](README-img/nearest-neibor.jpg)
#### Bilinear interpolation with resize ratio = 4.4
![bilinear](README-img/bilinear.jpg)
#### Bicubic interpolation with resize ratio = 4.4
![bicubic](README-img/bicubic.jpg)
#### Rotate image with 30 degree
![rotate](README-img/rotate.jpg)

## Development setup

Go to ```build/``` folder of each project

Type
```
cmake ../
```