#include "BoundingBoxManager.h"
//Author: David Amata and Christian Gileski
//Date: November 9, 2014
//

//methods to create singleton manager
BoundingBoxManager* BoundingBoxManager::m_pInstance = nullptr;

//grabs pointer to single instance of manager
BoundingBoxManager* BoundingBoxManager::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new BoundingBoxManager();
	}
	return m_pInstance;
}

//releases data at end of program
void BoundingBoxManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

//establishes intial values 
void BoundingBoxManager::Init(void)
{
	m_pModelMngr = ModelManagerClass::GetInstance(); //grab singleton of model manager
	m_vCollidingNamesOBB.clear(); //clear OBB collision names
	m_vCollidingNamesAABB.clear(); //clear AABB collision names
	m_nBoxes = 0; //number of boxes set to zero
}

//clears heap memory for each bounding box
void BoundingBoxManager::Release(void)
{
	RemoveBox("ALL");
	return;
}


//The big 3
BoundingBoxManager::BoundingBoxManager(){Init();}
BoundingBoxManager::BoundingBoxManager(BoundingBoxManager const& other){ }
BoundingBoxManager& BoundingBoxManager::operator=(BoundingBoxManager const& other) { return *this; }
BoundingBoxManager::~BoundingBoxManager(){Release();};
//Accessors
int BoundingBoxManager::GetNumberOfBoxes(void){ return m_nBoxes; }


//--- Non Standard Singleton Methods

// makes an individual or all bounding boxes to be visibile
void BoundingBoxManager::SetVisible(bool a_bVisibleOBB, bool a_bVisibleAABB, String a_sInstance)
{
	if(a_sInstance == "ALL")
	{
		int nBoxes = GetNumberOfBoxes();
		for(int nBox = 0; nBox < nBoxes; nBox++)
		{
			m_vBoundingBox[nBox]->SetVisibleOBB(a_bVisibleOBB);
			m_vBoundingBox[nBox]->SetVisibleAABB(a_bVisibleAABB);
		}
	}
	else
	{
		int nBox = m_pModelMngr->IdentifyInstance(a_sInstance);
		if(nBox < 0 || nBox < m_nBoxes)
			m_vBoundingBox[nBox]->SetVisibleOBB(a_bVisibleOBB);
			m_vBoundingBox[nBox]->SetVisibleAABB(a_bVisibleAABB);
	}
}

//passes in color values to boxes 
void BoundingBoxManager::SetColor(vector3 a_v3ColorOBB, vector3 a_v3ColorAABB, String a_sInstance)
{
	if(a_sInstance == "ALL")
	{
		int nBoxes = GetNumberOfBoxes();
		for(int nBox = 0; nBox < nBoxes; nBox++)
		{
			m_vBoundingBox[nBox]->SetColorOBB(a_v3ColorOBB);
			m_vBoundingBox[nBox]->SetColorAABB(a_v3ColorAABB);
		}
	}
	else
	{
		int nBox = m_pModelMngr->IdentifyInstance(a_sInstance);
		if(nBox < 0 || nBox < m_nBoxes)
			m_vBoundingBox[nBox]->SetColorOBB(a_v3ColorOBB);
			m_vBoundingBox[nBox]->SetColorAABB(a_v3ColorAABB);
	}
}

//passes model matrix from model manager to bounding boxes
void BoundingBoxManager::SetModelMatrix(matrix4 a_mModelMatrix, String a_sInstance)
{
	if(a_sInstance == "ALL")
	{
		int nBoxes = GetNumberOfBoxes();
		for(int nBox = 0; nBox < nBoxes; nBox++)
		{
			m_vBoundingBox[nBox]->SetModelMatrix(a_mModelMatrix);
		}
	}
	else
	{
		int nBox = m_pModelMngr->IdentifyInstance(a_sInstance);
		if(nBox < 0 || nBox < m_nBoxes)
			m_vBoundingBox[nBox]->SetModelMatrix(a_mModelMatrix);
	}
}

//makes an individual bounding box visible
void BoundingBoxManager::Render(String a_sInstance)
{
	
	if(a_sInstance == "ALL")
	{
		int nBoxes = GetNumberOfBoxes();
		for(int nBox = 0; nBox < nBoxes; nBox++)
		{
			m_vBoundingBox[nBox]->Render(MEDEFAULT);
		}
	}
	else
	{
		int nBox = m_pModelMngr->IdentifyInstance(a_sInstance);
		if(nBox < 0 || nBox < m_nBoxes)
			m_vBoundingBox[nBox]->Render(MEDEFAULT);
	}
}

//adds a bounding box to the manager's control
void BoundingBoxManager::AddBox(String a_sInstanceName)
{
	BoundingBox* oBox = new BoundingBox(a_sInstanceName);
	m_vBoundingBox.push_back(oBox);
	m_nBoxes++;
	//set the model matrix of the individual box intially when added
	oBox->SetModelMatrix(m_pModelMngr->GetModelMatrix(a_sInstanceName)); 
}

//removes and individual box from the list
void BoundingBoxManager::RemoveBox(String a_sInstanceName)
{
	if(a_sInstanceName == "ALL")
	{
		//Clear the vector's element first otherwise there is a memory leak
		for(int nBox = 0; nBox < m_nBoxes; nBox++)
		{
			BoundingBox* pBS = m_vBoundingBox[nBox];
			delete pBS;
		}
		m_vBoundingBox.clear();
		m_nBoxes = 0;
		return;
	}
	std::vector<BoundingBox*> vTemp;
	int nBox = m_pModelMngr->IdentifyInstance(a_sInstanceName);
	if(nBox < 0 || nBox < m_nBoxes)
	{
		for(int nBox = 0; nBox < m_nBoxes; nBox++)
		{
			if(nBox != nBox)
			{
				vTemp.push_back(m_vBoundingBox[nBox]);
			}
			else
			{
				BoundingBox* pBS = m_vBoundingBox[nBox];
				delete pBS;
			}
		}
	}
	m_vBoundingBox = vTemp;
	m_nBoxes++;
}

//update loop for calculations and rendering
void BoundingBoxManager::Update(void)
{
	//clear the colliding box list
	m_vCollidingNamesOBB.clear();
	m_vCollidingNamesAABB.clear();
	//set to default color of white
	for(int nBox = 0; nBox < m_nBoxes; nBox++)
	{
		m_vBoundingBox[nBox]->SetColorOBB(MEWHITE);
		m_vBoundingBox[nBox]->SetColorAABB(MEWHITE);
	}
	//check for collisions
	CollisionCheck();
	//respond to the colliding objects by chaning color
	CollisionResponse();
}

//calculates collisions for AABB to AABB
void BoundingBoxManager::CollisionCheck(void)
{
	//loop through twice without checking itself (n^2 -n)
	for(int nBox = 0; nBox < m_nBoxes; nBox++)
	{
		for(int nBox2 = 0; nBox2 < m_nBoxes; nBox2++)
		{
			//make sure its not itself 
			if(nBox != nBox2)
			{
				//assume its not colliding
				bool AABBtoAABB = false;

				//retrive min and max values
				vector3 min1 = m_vBoundingBox[nBox]->GetMinimumAABB();
				vector3 max1 = m_vBoundingBox[nBox]->GetMaximumAABB();
				vector3 min2 = m_vBoundingBox[nBox2]->GetMinimumAABB();
				vector3 max2 = m_vBoundingBox[nBox2]->GetMaximumAABB();

				//translate the min and max coordinates to their location in reference to centroid
				matrix4 mMatrix1 = m_vBoundingBox[nBox]->GetModelMatrix();
				vector3 vCentroid1 = m_vBoundingBox[nBox]->GetCentroidAABB();
				//vector3 fOrigin1 = static_cast<vector3>(glm::translate(vCentroid1) * vector4(0.0f, 0.0f, 0.0f, 1.0f));
				min1 = static_cast<vector3>(glm::translate(vCentroid1) * vector4(min1.x, min1.y, min1.z, 1.0f));
				max1 = static_cast<vector3>(glm::translate(vCentroid1) * vector4(max1.x, max1.y, max1.z, 1.0f));

				matrix4 mMatrix2 = m_vBoundingBox[nBox2]->GetModelMatrix();
				vector3 vCentroid2 = m_vBoundingBox[nBox2]->GetCentroidAABB();
				//vector3 fOrigin2 = static_cast<vector3>(glm::translate(vCentroid2) * vector4(0.0f, 0.0f, 0.0f, 1.0f));
				min2 = static_cast<vector3>(glm::translate(vCentroid2) * vector4(min2.x, min2.y, min2.z, 1.0f));
				max2 = static_cast<vector3>(glm::translate(vCentroid2) * vector4(max2.x, max2.y, max2.z, 1.0f));

				//if max is greater than min in all instances a collision has occured
				if(max1.x > min2.x && min1.x < max2.x &&
					max1.y > min2.y && min1.y < max2.y && 
					max1.z > min2.z && min1.z < max2.z) 
				{
					AABBtoAABB = true;
				}

				//if a collision has occured add name to the list.
				if(AABBtoAABB == true)
				{
					m_vCollidingNamesAABB.push_back(m_vBoundingBox[nBox]->GetInstanceName());
					m_vCollidingNamesAABB.push_back(m_vBoundingBox[nBox2]->GetInstanceName());
				}

			}
		}
	}



}

//check if name is in list and return true or false
bool BoundingBoxManager::CheckForNameInListOBB(String a_sName)
{
	int nNames = static_cast<int>(m_vCollidingNamesOBB.size());
	for(int nName = 0; nName < nNames; nName++)
	{
		if(m_vCollidingNamesOBB[nName] == a_sName)
			return true;
	}
	return false;
}

//check if name is in list and return true or false
bool BoundingBoxManager::CheckForNameInListAABB(String a_sName)
{
	int nNames = static_cast<int>(m_vCollidingNamesAABB.size());
	for(int nName = 0; nName < nNames; nName++)
	{
		if(m_vCollidingNamesAABB[nName] == a_sName)
			return true;
	}
	return false;
}

//responds to collisions by changing box colors
void BoundingBoxManager::CollisionResponse(void)
{
	//loop through list if box has considered to be colliding change color to collision color.
	for(int nBox = 0; nBox < m_nBoxes; nBox++)
	{
		
		if(CheckForNameInListOBB(m_vBoundingBox[nBox]->GetInstanceName())){
			m_vBoundingBox[nBox]->SetColorOBB(MEBLUE);
		}
		if(CheckForNameInListAABB(m_vBoundingBox[nBox]->GetInstanceName())){
			m_vBoundingBox[nBox]->SetColorAABB(MEGREEN);
		}
	}
}