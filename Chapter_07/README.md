# Chapter 07.  Detecting Face Parts and Overlaying Masks 

## Requirements

- OpenCV 4.0

## Steps to build

To compile on linux, Mac or windows using Mingw

```
mkdir build
cd build
cmake ..
make
```

## Executables

The following applications are generated.

```
./earDetector  
./overlayFacemask  
./overlayMoustache  
./overlayNose  
./overlaySunglasses
```

Parameters that accepts executable:

```
./overlayFacemask ../resources/haarcascade_frontalface_alt.xml ../resources/mask.jpg 
./overlaySunglasses ../resources/haarcascade_frontalface_alt.xml ../resources/haarcascade_eye.xml ../resources/glasses.jpg
```