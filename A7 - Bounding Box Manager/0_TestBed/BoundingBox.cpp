#include "BoundingBox.h"
//The big 3
BoundingBox::BoundingBox(String a_sInstanceName)
{
	//Initialize variables
	m_pMeshOBB = nullptr;
	m_pMeshAABB = nullptr;
	m_v3CentroidOBB = vector3(0.0f,0.0f,0.0f);
	m_v3CentroidAABB = vector3(0.0f,0.0f,0.0f);
	m_v3ColorOBB = MEGREEN;
	m_v3ColorAABB = MEBLUE;
	m_mModelToWorldOBB = matrix4(1.0f);
	m_mModelToWorldAABB = matrix4(1.0f);
	m_bVisibleOBB = false;
	m_bVisibleAABB = false;
	minOBB = vector3(0.0f,0.0f,0.0f);
	maxOBB = vector3(1.0f,1.0f,1.0f);
	minAABB = vector3(0.0f,0.0f,0.0f);
	maxAABB = vector3(1.0f,1.0f,1.0f);


	//Get the singleton instance of the Model Manager
	m_pModelMngrOBB = ModelManagerClass::GetInstance();
	m_pModelMngrAABB = ModelManagerClass::GetInstance();
	m_sInstance = a_sInstanceName;
	//Identify the instance from the list inside of the Model Manager
	int nInstance = m_pModelMngrOBB->IdentifyInstance(m_sInstance);
	int nInstance2 = m_pModelMngrAABB->IdentifyInstance(m_sInstance);
	//If there is no instance with that name the Identify Instance will return -1
	//In which case there is nothing to do here so we just return without allocating memory
	if(nInstance == -1)
		return;

	if(nInstance2 == -1)
		return;

	//Construct a sphere with the dimensions of the instance, they will be allocated in the
	//corresponding member variables inside the method
	CalculateBox(m_sInstance);
	//Get the Model to World matrix associated with the Instance
	m_mModelToWorldOBB = m_pModelMngrOBB->GetModelMatrix(m_sInstance);
	m_mModelToWorldAABB = m_pModelMngrAABB->GetModelMatrix(m_sInstance);
	//If the size of the radius is 0 it means that there are no points or all of them are allocated
	//right at the origin, which will cause an issue, so we just return with no allocations

	//Crete a new Box and initialize it using the member variables
	m_pMeshOBB = new PrimitiveWireClass();
	m_pMeshOBB->GenerateSphere(m_fRadius, 5, MEWHITE);
	m_pMeshOBB->SetModelMatrix(glm::translate(m_mModelToWorldOBB, m_v3CentroidOBB));

	//Crete a new Box and initialize it using the member variables
	m_pMeshAABB = new PrimitiveWireClass();
	m_pMeshAABB->GenerateSphere(m_fRadius, 5, MEWHITE);
	m_pMeshAABB->SetModelMatrix(glm::translate(m_mModelToWorldAABB, m_v3CentroidAABB));


















}