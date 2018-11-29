# Chapter 12. Deep Learning with OpenCV 

## Requirements

- Protobuf 3.5
- OpenCV 4.0 With DNN module enabled
- Download Yolov3 models. (Links provided on the book)
- Webcam (For face detection)

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
./DeepLearning_ch12  
./DeepLearning_ch12_face
```

Parameters accepted from executables:

```
./DeepLearning_ch2 image_to_recognize_required
```

```
 ./DeepLearning_ch12_face --model=../data/res10_300x300_ssd_iter_140000.caffemodel --proto=../data/deploy.prototxt.txt
```