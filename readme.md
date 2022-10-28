# Instructions for the usage of the c++ algorithm

*src*: All functions and headers for the project
*build*: build folder with CmakeList.txt file
*Input*: All images that you want to indentified
*Volunteer*: All images that you want/have registered

*disclaimer*: certain parts of the program are specified according to the name of the data I used while creating it, you may have to change the path and name of files according to yours.

## Images input
**Put the input image inside the Input folder as follow:**
- 01/ is for left hand
- 02/ is for right hand
	
## Images registered classification
**Put the images to register inside the volunteer folder as follow:**
- 01/ is for left hand
	- give a number to all the registered patient as follow: 01, 02, ..., 99
- 02/ is for right hand
	- give a number to all the registered patient as follow: 01, 02, ..., 99
	
*put all the corresponding images inside the folders*
	
## Build
**build with cmake inside the build folder**

```cmake .```

```make```
	
*if you just copied the folder and have other files except "CmakeList.txt" inside the build folder you will have cmake error, remove everything except "CmakeList.txt" and build again*
	
## Execution
**You can now execute the two functions from this build folder with:**

```./Registrationcpp ../volunteers/02/ (for left hand)```

```./Matchingcpp ../Input/02/ ../volunteers/02/ (for left hand)```
	
	
***This algortihm was created by Virgile based on the LLBP technique (references below), you can contact me at virgile.dlr@protonmail.com***


### Reference

*A. Petpon and S. Srisuk, “Face Recognition with Local Line Binary Pattern,” in 2009 Fifth International Conference on Image and Graphics, Sep. 2009, pp. 533–539. doi: 10.1109/ICIG.2009.123.*
