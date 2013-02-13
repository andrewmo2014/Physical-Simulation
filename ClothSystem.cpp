#include "ClothSystem.h"
#include <cmath>
#include <iostream>

using namespace std;

ClothSystem::ClothSystem(int C_SIZE):PendulumSystem(C_SIZE*C_SIZE)
{

	particles_ON = false;
	structSprings_ON = true;

	isCloth = true;

	float restL = 0.20f;
	float distance = 0.20f;
	float springC = 200.0f;

	for (int row=0; row < C_SIZE; row++){
	    for (int col=0; col < C_SIZE; col++){

		if ((row == 0 && col == 0) || (row == 0 && col == C_SIZE-1)){	//endpoints are fixed
		        particles.push_back(Vector4f(col*distance, 0.0f, row*distance, 1.0f));}
		else{   particles.push_back(Vector4f(col*distance, 0.0f, row*distance, 0.0f));}
		
		//Structural Springs
		//======================================================
		//Link(row,col) to Link(row+1,col)
		if (row < C_SIZE-1){
		    float p0 = (float)((row)   * C_SIZE + (col));
		    float p1 = (float)((row+1) * C_SIZE + (col));
		    springs.push_back(Vector4f(p0, p1, restL, springC));
		}
		//Link(row,col) to Link(row,col+1)
		if (col < C_SIZE-1){
		    float p0 = (float)((row) * C_SIZE + (col)  );
		    float p1 = (float)((row) * C_SIZE + (col+1));
		    springs.push_back(Vector4f(p0, p1, restL, springC));
		}
		
		//Shear Springs
		//======================================================
		//Link(row,col) to Link(row+1,col+1)
		if (row < C_SIZE-1 && col < C_SIZE-1){
		    float p0 = (float)((row)   * C_SIZE + (col)  );
		    float p1 = (float)((row+1) * C_SIZE + (col+1));
		    springs.push_back(Vector4f(p0, p1, restL*sqrt(2), springC));
		}
		//Link(row,col) to Link(row+1,col-1)
		if (row < C_SIZE-1 && col > 0){
		    float p0 = (float)((row) * C_SIZE + (col)  );
		    float p1 = (float)((row+1) * C_SIZE + (col-1));
		    springs.push_back(Vector4f(p0, p1, restL*sqrt(2), springC));
		}
		
		//Flex Springs
		//======================================================
		//Link(row,col) to Link(row+2,col)
		if (row < C_SIZE-2){
		    float p0 = (float)((row)   * C_SIZE + (col));
		    float p1 = (float)((row+2) * C_SIZE + (col));
		    springs.push_back(Vector4f(p0, p1, restL*2, springC));
		}
		//Link(row,col) to Link(row,col+2)
		if (col < C_SIZE-2){
		    float p0 = (float)((row) * C_SIZE + (col)  );
		    float p1 = (float)((row) * C_SIZE + (col+2));
		    springs.push_back(Vector4f(p0, p1, restL*2, springC));
		}

		//Faces
		
		//======================================================
		if (row < C_SIZE-1 && col < C_SIZE-1){

		    //Front - normals pointing forward
		    
		    Vector3f face1 = Vector3f((float)((row+1)*C_SIZE + (col+1)),
					      (float)((row)  *C_SIZE + (col+1)),
					      (float)((row+1)*C_SIZE + (col)  ));
		    faces.push_back(face1);

		    Vector3f face2 = Vector3f((float)((row)  *C_SIZE + (col+1)),
					      (float)((row)  *C_SIZE + (col)  ),
					      (float)((row+1)*C_SIZE + (col)  ));
		    faces.push_back(face2);

		    //Back - normals pointing backward
		    Vector3f face3 = Vector3f((float)((row+1)*C_SIZE + (col+1)),
					      (float)((row+1)*C_SIZE + (col)  ),
					      (float)((row)  *C_SIZE + (col+1)  ));
		    faces.push_back(face3);

		    Vector3f face4 = Vector3f((float)((row)  *C_SIZE + (col+1)),
					      (float)((row+1)*C_SIZE + (col)  ),
					      (float)((row)  *C_SIZE + (col)  ));
		    faces.push_back(face4);
		    
		}
		
		
	    }
	}

	initPendulum(particles, springs, faces);
	        
}

