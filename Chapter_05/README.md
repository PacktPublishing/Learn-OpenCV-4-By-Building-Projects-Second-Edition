# Chapter 05.  Automated Optical Inspection, Object Segmentation, and Detection 

## Requirements

- OpenCV 4.0

## Steps to build

To compile on Linux, mac or Windows using Mingw

```
mkdir build
cd build
cmake ..
make
```

## Executables

The following applications are generated.

```
./Chapter5
```

Parameters that accepts executable:

```
Chapter 5.
Usage: Chapter5 [params] image lightPattern 

	-?, -h, --help, --usage (value:true)
		print this message
	--lightMethod (value:1)
		Method to remove backgroun light, 0 differenec, 1 div, 2 no light removal'
	--segMethod (value:1)
		Method to segment: 1 connected Components, 2 connectec components with stats, 3 find Contours

	image
		Image to process
	lightPattern
		Image light pattern to apply to image input

```
