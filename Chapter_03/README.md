# Chapter 03.  Learning Graphical User Interfaces 

## Requirements

- QT library
- VTK library
- OpenCV 4.0 with QT and VTK support

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
./ch3_sample1
./ch3_sample2
./ch3_sample3
./ch3_sample4
./ch3_sample5
./ch3_sample6
```

Sample 1. Basic GUI
- Differences between QT and Normal GUI
- Create a window
- Move
- Resize
- Wait for key
- Destroy

Sample 2. QT functions
- Properties window
- Overlay
- Status Bar
- Note: Save and load

Sample 3. Create a Slider
- Create a slider
- Event slider
- Add +1 to image

Sample 4. Create a button
- Create a button
- Event button
- Change color to gray

Sample 5. Advanced UI. OpenGL
- Create an interface
- Add some boxe
- Update

Sample 6. Advanced UI. VTK
- Create basic VTK sample
