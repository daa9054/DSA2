#include "BoundingBox.h"
//Author: David Amata and Christian Gileski
//Date: November 9, 2014
//

BoundingBox::BoundingBox(String a_sInstanceName)
{
	//Initialize variables
	m_pMeshOBB = nullptr; // mesh for primitive shape's OBB
	m_pMeshAABB = nullptr; // mesh for the primitive shape's AABB
	m_v3CentroidOBB = vector3(0.0f,0.0f,0.0f); //center of OBB
	m_v3CentroidAABB = vector3(0.0f,0.0f,0.0f); //center of AABB
	minOBB = vector3(0.0f,0.0f,0.0f); //min vector of OBB
	maxOBB = vector3(0.0f,0.0f,0.0f); //max vector of OBB
	minAABB = vector3(0.0f,0.0f,0.0f); //min vector of AABB
	maxAABB = vector3(0.0f,0.0f,0.0f); //max vector of AABB
	m_v3ColorOBB = MEWHITE; //default color of OBB
	m_v3ColorAABB = MEWHITE; //default color of AABB
	m_mModelToWorld = matrix4(1.0f); //global matrix for the model
	visibilityOBB = false; //set intial visbility bool for OBB
	visibilityAABB = false; //set intial visibility bool for AABB

	//Get the singleton instance of the Model Manager
	m_pModelMngr = ModelManagerClass::GetInstance();
	m_sInstance = a_sInstanceName;
	//Identify the instance from the list inside of the Model Manager
	int nInstance = m_pModelMngr->IdentifyInstance(m_sInstance);
	//If there is no instance with that name the Identify Instance will return -1
	//In which case there is nothing to do here so we just return without allocating memory
	if(nInstance == -1)
		return;

	//Construct a Box with the dimensions of the instance, they will be allocated in the
	//corresponding member variables inside the method
	CalculateBox(m_sInstance);

	//Get the Model to World matrix associated with the Instance
	m_mModelToWorld = m_pModelMngr->GetModelMatrix(m_sInstance);

	//Create a new Box and initialize it using the member variables
	m_pMeshOBB = new PrimitiveWireClass(); //create wire class
	m_pMeshOBB->GenerateCube(1.0f, MEWHITE); //create uniform cube
	matrix4 scaleOBB = glm::scale(matrix4(1.0f),sizeOBB); //create mat4 for scale based on size from CalculateBox
	matrix4 translateOBB = glm::translate(m_mModelToWorld, m_v3CentroidOBB); //create mat4 for translate with centroid from CalculateBox
	m_pMeshOBB->SetModelMatrix(translateOBB * scaleOBB ); //multiple matrices for each of the matrices for correct size and translation

	//Create a new Box and initialize it using the member variables
	m_pMeshAABB = new PrimitiveWireClass(); //create wire class
	m_pMeshAABB->GenerateCube(1.0f, MEWHITE);  //create uniform cube
	matrix4 scaleAABB = glm::scale(matrix4(1.0f),sizeAABB); //create mat4 for scale based on size from CalculateBox
	matrix4 translateAABB = glm::translate(m_mModelToWorld, m_v3CentroidAABB); //create mat4 for translate with centroid from CalculateBox
	m_pMeshAABB->SetModelMatrix(translateAABB * scaleAABB); //multiple matrices for each of the matrices for correct size and translation
}

BoundingBox::BoundingBox(BoundingBox const& other)
{
	//Initialize the Box using other instance of it
	m_sInstance = other.m_sInstance;
	visibilityOBB = other.visibilityOBB;
	visibilityAABB = other.visibilityAABB;
	m_v3CentroidOBB = other.m_v3CentroidOBB;
	m_v3CentroidAABB = other.m_v3CentroidAABB;
	m_mModelToWorld = other.m_mModelToWorld;
	m_pModelMngr = other.m_pModelMngr;

	minOBB = other.minOBB;
	maxOBB = other.minOBB;

	minAABB = other.minAABB;
	maxAABB = other.maxAABB;

	m_v3ColorOBB = other.m_v3ColorOBB;
	m_v3ColorAABB = other.m_v3ColorAABB;

	CalculateBox(m_sInstance);

	m_pMeshOBB = new PrimitiveWireClass();
	m_pMeshOBB->GenerateCube(1.0f, MEWHITE);
	matrix4 scaleOBB = glm::scale(matrix4(1.0f),sizeOBB);
	matrix4 translateOBB = glm::translate(m_mModelToWorld, m_v3CentroidOBB);
	m_pMeshOBB->SetModelMatrix(scaleOBB * translateOBB);

	m_pMeshAABB = new PrimitiveWireClass();
	m_pMeshAABB->GenerateCube(1.0f, MEWHITE);
	matrix4 scaleAABB = glm::scale(matrix4(1.0f),sizeAABB);
	matrix4 translateAABB = glm::translate(m_mModelToWorld, m_v3CentroidAABB);
	m_pMeshAABB->SetModelMatrix(scaleAABB * translateAABB);
}

BoundingBox& BoundingBox::operator=(BoundingBox const& other)
{
	//If the incoming instance is the same as the current there is nothing to do here
	if(this != &other)
	{
		//Release the existing object
		Release();
		//Initialize the Box using other instance of it
		m_sInstance = other.m_sInstance;
		visibilityOBB = other.visibilityOBB;
		visibilityAABB = other.visibilityAABB;
		m_v3CentroidOBB = other.m_v3CentroidOBB;
		m_v3CentroidAABB = other.m_v3CentroidAABB;
		m_mModelToWorld = other.m_mModelToWorld;
		m_pModelMngr = other.m_pModelMngr;

		minOBB = other.minOBB;
		maxOBB = other.minOBB;

		minAABB = other.minAABB;
		maxAABB = other.maxAABB;

		m_v3ColorOBB = other.m_v3ColorOBB;
		m_v3ColorAABB = other.m_v3ColorAABB;

		CalculateBox(m_sInstance);

		m_pMeshOBB = new PrimitiveWireClass();
		matrix4 scaleOBB = glm::scale(matrix4(1.0f),sizeOBB);
		matrix4 translateOBB = glm::translate(m_mModelToWorld, m_v3CentroidOBB);
		m_pMeshOBB->SetModelMatrix(scaleOBB * translateOBB);


		m_pMeshAABB = new PrimitiveWireClass();
		matrix4 scaleAABB = glm::scale(matrix4(1.0f),sizeAABB);
		matrix4 translateAABB = glm::translate(m_mModelToWorld, m_v3CentroidAABB);
		m_pMeshAABB->SetModelMatrix(scaleAABB* translateAABB);

	}
	return *this;
}
BoundingBox::~BoundingBox(void)
{
	//Destroying the object requires releasing all the allocated memory first
	Release();
}

void BoundingBox::Release(void)
{
	//If the mesh exists release it
	if(m_pMeshOBB != nullptr)
	{
		delete m_pMeshOBB;
		m_pMeshOBB = nullptr;
	}

	//If the mesh exists release it
	if(m_pMeshAABB != nullptr)
	{
		delete m_pMeshAABB;
		m_pMeshAABB = nullptr;
	}

	//The job of releasing the Model Manager Instance is going to be the work
	//of another method, we can't assume that this class is the last class
	//that uses this singleton, so we do not release it, we just make the pointer
	//point at nothing.
	m_pModelMngr = nullptr;
}

//Accessors
vector3 BoundingBox::GetCentroidOBB(void){ return m_v3CentroidOBB; }
vector3 BoundingBox::GetCentroidAABB(void){ return m_v3CentroidOBB; }


vector3 BoundingBox::GetColorOBB(void){ return m_v3ColorOBB; }
void BoundingBox::SetColorOBB(vector3 a_v3Color){ m_v3ColorOBB = a_v3Color; }

vector3 BoundingBox::GetColorAABB(void){ return m_v3ColorAABB; }
void BoundingBox::SetColorAABB(vector3 a_v3Color){ m_v3ColorAABB = a_v3Color; }


matrix4 BoundingBox::GetModelMatrix(void){ return m_mModelToWorld; }

//passes global matrix into the model matrix variable and recalculates box 
void BoundingBox::SetModelMatrix(matrix4 a_mModelMatrix)
{
	//Sets the model matrix of the Sphere
	m_mModelToWorld = a_mModelMatrix;

	//recaluclate everytime matrix is changed
	CalculateBox(m_sInstance);

	//Sets the Model Matrix of the actual Box shape
	//(which is translated m_v3Centrod away from the origin of our box)
	matrix4 scaleOBB = glm::scale(matrix4(1.0f),sizeOBB);
	matrix4 translateOBB = glm::translate(m_mModelToWorld, m_v3CentroidOBB);
	m_pMeshOBB->SetModelMatrix(translateOBB * scaleOBB );

	matrix4 scaleAABB = glm::scale(matrix4(1.0f),sizeAABB);
	matrix4 translateAABB = glm::translate(m_v3CentroidAABB);
	m_pMeshAABB->SetModelMatrix(translateAABB * scaleAABB );
}

//additional Accessors
bool BoundingBox::GetVisibleOBB(void) { return visibilityOBB; }
void BoundingBox::SetVisibleOBB(bool a_bVisible) { visibilityOBB = a_bVisible; }

bool BoundingBox::GetVisibleAABB(void) { return visibilityAABB; }
void BoundingBox::SetVisibleAABB(bool a_bVisible) { visibilityAABB = a_bVisible; }

String BoundingBox::GetInstanceName(void){ return m_sInstance; }

vector3 BoundingBox::GetMinimumOBB(void){ return minOBB; }
vector3 BoundingBox::GetMaximumOBB(void){ return maxOBB; }

vector3 BoundingBox::GetMinimumAABB(void){ return minAABB; }
vector3 BoundingBox::GetMaximumAABB(void){ return maxAABB; }

vector3 BoundingBox::GetSizeOBB(void){ return sizeOBB;}
void BoundingBox::SetSizeOBB(vector3 newSize){ sizeOBB = newSize; }

vector3 BoundingBox::GetSizeAABB(void){ return sizeAABB;}
void BoundingBox::SetSizeAABB(vector3 newSize){ sizeAABB = newSize; }


//Calculates the OBB and AABB cordinates
void BoundingBox::CalculateBox(String a_sInstance)
{

	///Calculate OBB Cordinates and Size/////////////////////////////////////////////

	//Get the vertices List to calculate the maximum and minimum
	std::vector<vector3> vVertices = m_pModelMngr->GetVertices(a_sInstance);
	int nVertices = static_cast<int>(vVertices.size());

	//If the size of the List is 0 it means we dont have any vertices in this Instance
	//which means there is an error somewhere
	if(nVertices == 0)
		return;

	//Go one by one on each component and realize which one is the smallest one
	if(nVertices > 0)
	{
		//We assume the first vertex is the smallest one
		minOBB = vVertices[0];
		//And iterate one by one
		for(int nVertex = 1; nVertex < nVertices; nVertex++)
		{
			if(vVertices[nVertex].x < minOBB.x)
				minOBB.x = vVertices[nVertex].x;

			if(vVertices[nVertex].y < minOBB.y)
				minOBB.y = vVertices[nVertex].y;

			if(vVertices[nVertex].z < minOBB.z)
				minOBB.z = vVertices[nVertex].z;
		}
	}

	//Go one by one on each component and realize which one is the largest one
	if(nVertices > 0)
	{
		//We assume the first vertex is the largest one
		maxOBB = vVertices[0];
		//And iterate one by one
		for(int nVertex = 1; nVertex < nVertices; nVertex++)
		{
			if(vVertices[nVertex].x > maxOBB.x)
				maxOBB.x = vVertices[nVertex].x;

			if(vVertices[nVertex].y > maxOBB.y)
				maxOBB.y = vVertices[nVertex].y;

			if(vVertices[nVertex].z > maxOBB.z)
				maxOBB.z = vVertices[nVertex].z;
		}
	}

	//The centroid is going to be the point that is halfway of the min to the max
	m_v3CentroidOBB = minOBB + maxOBB;
	m_v3CentroidOBB /= 2.0f;

	//find the distance of min to max for use in scaling vector for primitive cube
	float distOBBx = glm::distance(minOBB.x, maxOBB.x);
	float distOBBy = glm::distance(minOBB.y, maxOBB.y);
	float distOBBz = glm::distance(minOBB.z, maxOBB.z);

	//assign scale vector values
	sizeOBB = vector3(distOBBx, distOBBy, distOBBz);


	

	////Calculate AABB coordinates and size////////////////////////////////////////////////////
	
	
	//Get the vertices List to calculate the maximum and minimum
	std::vector<vector4> vVerticesAABB = std::vector<vector4>(nVertices);

	//translate each model coordinate to the global matriz so that the box is Global Axis Aligned
	for(int i = 0; i < nVertices; i++)
	{
		vVerticesAABB[i] = vector4(vVertices[i].x, vVertices[i].y, vVertices[i].z, 1.0f);
		vVerticesAABB[i] = m_mModelToWorld * vVerticesAABB[i];
	}

	//Go one by one on each component and realize which one is the smallest one
	if(nVertices > 0)
	{
		//We assume the first vertex is the smallest one
		minAABB = static_cast<vector3>(vVerticesAABB[0]);
		//And iterate one by one
		for(int nVertex = 1; nVertex < nVertices; nVertex++)
		{
			if(vVerticesAABB[nVertex].x < minAABB.x)
				minAABB.x = vVerticesAABB[nVertex].x;

			if(vVerticesAABB[nVertex].y < minAABB.y)
				minAABB.y = vVerticesAABB[nVertex].y;

			if(vVerticesAABB[nVertex].z < minAABB.z)
				minAABB.z = vVerticesAABB[nVertex].z;
		}
	}

	//Go one by one on each component and realize which one is the largest one
	if(nVertices > 0)
	{
		//We assume the first vertex is the largest one
		maxAABB = static_cast<vector3>(vVerticesAABB[0]);
		//And iterate one by one
		for(int nVertex = 1; nVertex < nVertices; nVertex++)
		{
			if(vVerticesAABB[nVertex].x > maxAABB.x)
				maxAABB.x = vVerticesAABB[nVertex].x;

			if(vVerticesAABB[nVertex].y > maxAABB.y)
				maxAABB.y = vVerticesAABB[nVertex].y;

			if(vVerticesAABB[nVertex].z > maxAABB.z)
				maxAABB.z = vVerticesAABB[nVertex].z;
		}
	}

	//find centroid from half position of min and max
	m_v3CentroidAABB = minAABB + maxAABB;
	m_v3CentroidAABB /= 2.0f;

	//find distance values for min and max for scaling vector
	float distAABBx = glm::distance(minAABB.x, maxAABB.x);
	float distAABBy = glm::distance(minAABB.y, maxAABB.y);
	float distAABBz = glm::distance(minAABB.z, maxAABB.z);

	//apply scale vector values
	sizeAABB = vector3(distAABBx, distAABBy, distAABBz);

	//finish method
	return;

}

void BoundingBox::Render( vector3 a_vColor )
{

	if(!visibilityOBB && !visibilityAABB)
		return;
	//If the shape is visible render it
	//otherwise just return
	if(visibilityOBB)
	{
		//Calculate the color we want the shape to be
		vector3 vColor;
		//if the argument was MEDEFAULT just use the color variable in our class
		if(a_vColor == MEDEFAULT)
			vColor = m_v3ColorOBB;
		else //Otherwise use the argument
			vColor = a_vColor;

		//render the shape using a special case of the Shape Render method which uses the Color Shader.
		m_pMeshOBB->Render( matrix4(1.0f), vColor );
	}

	//If the shape is visible render it
	//otherwise just return
	if(visibilityAABB)
	{
		//Calculate the color we want the shape to be
		vector3 vColor;
		//if the argument was MEDEFAULT just use the color variable in our class
		if(a_vColor == MEDEFAULT)
			vColor = m_v3ColorAABB;
		else //Otherwise use the argument
			vColor = a_vColor;

		//render the shape using a special case of the Shape Render method which uses the Color Shader.
		m_pMeshAABB->Render( matrix4(1.0f), vColor );
	}



	
}
