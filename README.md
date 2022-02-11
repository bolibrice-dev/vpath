# This project is a mockup for a camera control system

The project consists of the following classes:

- cam_hardware
  Implements some form of a hardware attraction. It's not really part of the project. It just simulate what would be the serial port interface

- camera
  The core of the project. This class implements the main goal of this project in that it communicates with the "hardware" class and implements four (4) main methods:
  1. capture_image( )
  2. read_code( )
  3. ProcessBarcodeData( )
  4. ProcessImageData


- vpathlog
  Implements a minimal logging system TBC
