README.txt
==========================================================================================
Author:		Andrew Moran	|
Date:		11/01/2012	|
6.837 Computer Graphics		|
Assignment 3			|
=================================
__________________________________________________________________________________________
Compiling Instructions
==========================================================================================
	When I completed the assignment, I managed to run Linux through my Macbook Pro laptop with a Virtual Machine called VirtualBox.  I also tested on the campus Athena computer to make sure that it worked correctly.  Here are instructions
	1.	Unzip submission on Stellar and extract all files to designated directory
	2.	In terminal, cd to directory containing "assn3" folder
	3.	command make
	4.	command ./a3 <INTEGRATOR> <STEP_SIZE>
		INTEGRATOR: e - ForwardEuler
			    t - Trapezoidal
			    r - RK4 (default)
		STEP_SIZE:  decimal number

	5. 	command line arguments:
		ESCAPE	- quit the application
		t	- toggle between systems (Simple, Pendulum, Chain, Cloth)
		
		When viweing cloth:
		w	- toggle wireframe
		s	- toggle swing
		r	- reset
		d	- toggle wind
		UP	- translate sphere along positive y-axis (hold-down key)
		DOWN	- translate sphere along negative y-axis (hold-down key)
		LEFT	- translate sphere along negative x-axis (hold-down key)
		RIGHT	- translate sphere along positive x-axis (hold-down key)

	5.	"assn3" folder contains all necessary files including updated 
		files, classes, subclasses, etc.

__________________________________________________________________________________________
Collaboration
==========================================================================================
	I had no further assitance other than the help I received from Professor/TAs at office hours.

__________________________________________________________________________________________
References
==========================================================================================
	⁃	6.837 Lecture Notes
	⁃	Untangling Cloth - graphics.pixar.com/library/UntanglingCloth/paper.pdf
	-	Baraff, David, and Pixar Animation Studios. "Physically Based Modeling."
        -	http://www.cplusplus.com/reference/

__________________________________________________________________________________________
Problems
==========================================================================================
	Currently, my code is functioning properly.  However, there are a few things to look out for when running the application
	•	Integerator & Step_size:  All systems seem to have a stable state when
		run the application as ./a3 r .04
		Potential problems can occur when using a large stepsize on an integrator.
		For example, ClothSystem with ForwardEuler and Trapezoid with .04 step size
                or higher seems to explode 
	•	Cloth & Ball collision:  interaction between ball and cloth seems to work,
		however, moving ball through cloth can form mesh and divergence issues


__________________________________________________________________________________________
Extra Credit
==========================================================================================
	Here are some added features to the assignment:
	•	Cloth-Wind Toggle:    (toggle wind force on cloth by pressing 'd') 
	•	Cloth-Mesh:	      (toggle between faces and wireframe by pressing 'w') 
	•	Cloth-Ball Collision: (when swinging ['s'], cloth interacts with ball)
	•	Cloth-Ball Movement:  (move ball when viewing cloth by pressing arrow keys)
	•	System toggle: 	      (switch between different systems by pressing 't') 

	I attempted to do smooth rendering of the cloth to optimize the original triangle mesh implementation, however did not fix my bugs in time.

__________________________________________________________________________________________
Comments
==========================================================================================
	This was a very satisfying assignment.  At first, I did not know what to expect, trying to simulate a cloth.  However, after spending most of my time on my design and conceptually understainding what was going on, I managed to get pretty far on the assignmnet at a reasonable pace.  I was able to implement user interface features and added extra credit features.  My biggest problem that hindered my progress were memory issues.  It wasn't until after office hours that I realized this came from changing the original particleSystem.cpp & particleSystem.h files.  I made necssary changes to subclasses to get it back to a workign state (However, I wish I hadn't make that mistake to save time).  While adding/optimizing features, I wish I could have implemented smooth rendering correctly.  I had an idea of calculating normals for each vertex, however, did not get it at a wirking state.  Instead, I left it as the original triangle mesh.

 
