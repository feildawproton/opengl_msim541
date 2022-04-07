# opengl_msim541
An old and simple school project (msin541) using opengl.

## 1.	Introduction 
This assignment is an extension of P2 introducing several new concepts.  In this assignment you will see texture binding and mapping to manually built billboards.  This assignment also demonstrates texture blending through the use of glActiveTexture() and glMultTexCoord2f().  There are classes and methods for reading in PPM files, writing them, and performing vertical flips of char pointers arraignment in the PPM format.  This project also shows screen capture generation and writing, and automatic screen capture of traffic violations.  This assignment also shows encapsulation of the simulation using a simulation engine base class.

## B.	Functional Block Diagram
![image](https://user-images.githubusercontent.com/56926839/162270367-922b6481-3928-4935-a08c-1ff8b0a15224.png)

## C.	Class Diagram
![image](https://user-images.githubusercontent.com/56926839/162270506-50af92ad-b460-41c1-a7c5-5688f28531c5.png)

## D.	Class Descriptions – I will describe the classes unique to this assignment.
a.	Simulation – Base class that it used to derive transportSimulation
b.	transPortSimulation: This class is used to handle and run the simulation.  To run the simulation, create an instance of it, call SetWindowXXX() if desired, call InitializeSimulation(), and finally call Run()
c.	Billboard: This class is used to create static billboards.  You can set the location, orientation, and size of the billboard with the SetXXX functions.  Use ReadFile to set an image to the billboard, and call draw during your draw function.
d.	multiBoard:  This class is derived from Billboard and is used to create a billboard that transition between multiple images.  This class is used just like Billboard except that ReadFile() cam be called repeatedly to add images to be displayed and Update() must be called on it (from the simulation’s update function) to get the blending animation.
changed.
e.	PPMImage: this class is used to read in PPM images and to right out screen captures as PPM images.  To read in an image for texture binding, call ReadFile, then the image is the character pointer image.

Special Instructions:  The traffic cameras are off by default this time.  To toggle them on, press ‘c’.  The traffic cameras will need to be on for the South East Camera to capture the car running the northbound red light.
