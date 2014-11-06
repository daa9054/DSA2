#pragma once

#include "ME\Mesh\shape\PrimitiveWireClass.h"
#include "ME\Mesh\shape\ModelManagerClass.h"
using namespace MyEngine;

class BoundingBox
{
	String m_sInstance;//The name of the instance related to this sphere
	vector3 m_v3CentroidOBB;//Centroid of the Sphere
	vector3 m_v3CentroidAABB;//Centroid of the Sphere
	vector3 m_v3ColorOBB;//Color of the Sphere
	vector3 m_v3ColorAABB;//Color of the Sphere
	matrix4 m_mModelToWorld;//Model matrix of the sphere
	PrimitiveWireClass* m_pMeshOBB;//Bounding Box Mesh
	PrimitiveWireClass* m_pMeshAABB;//Bounding Box mesh
	ModelManagerClass* m_pModelMngr;//ModelManager instance
	vector3 minOBB;
	vector3 maxOBB;
	vector3 minAABB;
	vector3 maxAABB;
	bool visbilityOBB;
	bool visbilityAABB;

public:
	/* Constructor 	*/
	BoundingBox(String a_sInstanceName);
	/* Copy Constructor */
	BoundingBox(BoundingBox const& other);
	/* Copy Assignment Operator	*/
	BoundingBox& operator=(BoundingBox const& other);
	/*	Destructor	*/
	~BoundingBox(void);
	/* Gets the visibility of the Sphere (whether or not it is going to be drawn in render) */
	bool GetVisibleOBB(void);
	/*Sets the visibility of the Sphere (whether or not it is going to be drawn in render)
	Args:
		bool a_bVisible -> true for draw false for not draw*/
	void SetVisibleOBB(bool a_bVisible);
	/* Property:
	GetVisible() or GetVisible()*/
	__declspec(property(get = GetVisibleOBB, put = SetVisibleOBB)) bool VisibleOBB;
	bool GetVisibleAABB(void);
	/*Sets the visibility of the Sphere (whether or not it is going to be drawn in render)
	Args:
		bool a_bVisible -> true for draw false for not draw*/
	void SetVisibleAABB(bool a_bVisible);
	/* Property:
	GetVisible() or GetVisible()*/
	__declspec(property(get = GetVisibleAABB, put = SetVisibleAABB)) bool VisibleAABB;

	/* Gets the name of the model associated with this bounding sphere from model manager */
	String GetInstanceName(void);
	/* Property:
	GetInstanceName()*/
	__declspec(property(get = GetInstanceName)) String InstanceName;

	/* Gets the centroid the bounding sphere */
	vector3 GetCentroidOBB(void);
	/* Property:
	GetCentroid()*/
	__declspec(property(get = GetCentroidOBB)) vector3 CentroidOBB;
	/* Gets the centroid the bounding sphere */
	vector3 GetCentroidAABB(void);
	/* Property:
	GetCentroid()*/
	__declspec(property(get = GetCentroidAABB)) vector3 CentroidAABB;

	/* Gets the "ModelToWorld" matrix associated with the bounding sphere */
	matrix4 GetModelMatrix(void);
	/* Sets the "ModelToWorld" matrix associated with the bounding sphere */
	void SetModelMatrix(matrix4 a_ModelMatrix);
	/* "ModelToWorld"
	GetModelMatrix() or SetModelMatrix() */
	__declspec(property(get = GetModelMatrix, put = SetModelMatrix)) matrix4 ModelMatrix;

	/* Gets the color vector of this bounding sphere (the default color in which is going to be rendered) */
	vector3 GetColorOBB(void);
	/* Sets the color vector of this bounding sphere (the default color in which is going to be rendered) */
	void SetColorOBB(vector3 a_v3Color);
	/* Property:
	GetColor() or SetColor() */
	__declspec(property(get = GetColorOBB, put = SetColorOBB)) vector3 ColorOBB;
	/* Gets the color vector of this bounding sphere (the default color in which is going to be rendered) */
	vector3 GetColorAABB(void);
	/* Sets the color vector of this bounding sphere (the default color in which is going to be rendered) */
	void SetColorAABB(vector3 a_v3Color);
	/* Property:
	GetColor() or SetColor() */
	__declspec(property(get = GetColorAABB, put = SetColorAABB)) vector3 ColorAABB;

	vector3 GetMinimumOBB(void);
	vector3 GetMaximumOBB(void);
	vector3 GetMinimumAABB(void);
	vector3 GetMaximumAABB(void);


	/* Renders the bounding sphere
		Args:
			a_vColor -> determinate the color of the sphere to be rendered, if MEDEFAULT
			it will render the shape in the constructed color (white) */
	void Render( vector3 a_vColor = MEDEFAULT);

private:
	/* Released Memory and objects allocated. */
	void Release(void);
	/* Calculates the Box from the instance
	Args:
		a_sInstance: The name of the instance for which the bounding box is going to be calculated */
	void CalculateBox(String a_sInstance);
};

