# This project is a mockup for a camera control system

The project consists of the following classes:

- cam_hardware:

  Implements some form of a hardware abstraction. It's not really part of the project. The code in that class simulates a pseudo serial port interface

- camera: 

  The core of the project. This class implements the main goal of this project in that it communicates with the "hardware" class and implements four (4) main methods:
  1. capture_image( )
  2. read_code( )
  3. ProcessBarcodeData( )
  4. ProcessImageData


- vpathlog:

  Implements a minimal logging system TBC
  
---------------------------------------------------------------------------------------------------------------------

## Description of the functions in the core class

### **capture_image**:

This function really doesn't do much besides sending a control code to the camera hardware to tell camera to take a snapshot of the image, then call ProcessImageData function which does the actual image processing

### **read_code**:

like capture_image, this function mainly sends a control code to the camera hardware so camera can capture barcode(s) then call ProcessBarcodeData function which does actual barcode processing

### **ProcessBarcodeData**:

this function setup a state machine to make it easier to detect what type of barcode data(if any) we are getting from the camera hardware. With the state machine we are able to see if the transfer was interrupted either by the USB cable being pulled out or some other hardware failure. With that scheme, unless the barcode(s) is/are valid they do not make their way to the caller

### **ProcessImageData**:

like "ProcessBarcodeData", this function setup a state machine to make it easier to detect what type of image data(if any) we are getting from the camera hardware. With the state machine we are able to see if the transfer was interrupted either by the USB cable being pulled out or some other hardware failure. With that scheme, unless the image is valid it does not make its way to the caller.

####Testing / Building the project

A "main" function is provided for convenience and is the basis for upcoming [unit] test which will essentially consist of simulating "unplugging" a usb cable and verify that  incomplete barcode / image data is indeed discarded

A Makefile is provided making it possible to build the project by simply typing "make" in the project root folder

For convenience, if one is running WSL, a .vscode folder is also provided making it possible to run and debug this project right from Visual Studio Code

Note: the binary data is currently not JPEG

Testing code will be added soon :-)
