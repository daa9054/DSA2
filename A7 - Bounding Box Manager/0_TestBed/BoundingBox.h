#ifndef __BOUNDINGBOX_H_
#define __BOUNDINGBOX_H_



#include "ME\Mesh\shape\PrimitiveWireClass.h"
#include "ME\Mesh\shape\ModelManagerClass.h"


using namespace MyEngine;
class BoundingBox
{
	String m_sInstance;//The name of the instance related to this sphere
	bool m_bVisibleOBB;//Flag for rendering or not
	bool m_bVisibleAABB;//Flag for rendering or not
	//float m_fRadius;//Radius of the Sphere
	vector3 m_v3CentroidOBB;//Centroid of the Sphere
	vector3 m_v3CentroidAABB;//Centroid of the Sphere
	vector3 m_v3ColorOBB;//Color of the Sphere
	vector3 m_v3ColorAABB;//Color of the Sphere

	matrix4 m_mModelToWorldAABB;//Model matrix of the sphere
	PrimitiveWireClass* m_pMeshAABB;//Sphere Mesh
	ModelManagerClass* m_pModelMngrAABB;//ModelManager instance

	matrix4 m_mModelToWorldOBB;//Model matrix of the sphere
	PrimitiveWireClass* m_pMeshOBB;//Sphere Mesh
	ModelManagerClass* m_pModelMngrOBB;//ModelManager instance
	vector3 minOBB;
	vector3 maxOBB;
	vector3 minAABB;
	vector3 maxAABB;


public:
	/* Constructor 	*/
	BoundingBox(String a_sInstanceName);
	/* Copy Constructor */
	BoundingBox(BoundingBox const& other);
	/* Copy Assignment Operator	*/
	BoundingBox& operator=(BoundingBox const& other);
	/*	Destructor	*/
	~BoundingBox(void);


		
		/* Gets the name of the model associated with this bounding sphere from model manager */
	String GetInstanceName(void);
	/* Property:
	GetInstanceName()*/
	__declspec(property(get = GetInstanceName)) String InstanceName;

	/* Gets the visibility of the Sphere (whether or not it is going to be drawn in render) */
	bool GetVisibleOBB(void);
	/*Sets the visibility of the Sphere (whether or not it is going to be drawn in render)
	Args:
		bool a_bVisible -> true for draw false for not draw*/
	void SetVisibleOBB(bool a_bVisibleOBB);
	/* Property:
	GetVisible() or GetVisible()*/
	__declspec(property(get = GetVisibleOBB, put = SetVisibleOBB)) bool VisibleOBB;

	/* Gets the centroid the bounding sphere */
	vector3 GetCentroidOBB(void);
	/* Property:
	GetCentroid()*/
	__declspec(property(get = GetCentroidOBB)) vector3 CentroidOBB;

	/* Gets the "ModelToWorld" matrix associated with the bounding sphere */
	matrix4 GetModelMatrixOBB(void);
	/* Sets the "ModelToWorld" matrix associated with the bounding sphere */
	void SetModelMatrixOBB(matrix4 a_ModelMatrixOBB);
	/* "ModelToWorld"
	GetModelMatrix() or SetModelMatrix() */
	__declspec(property(get = GetModelMatrixOBB, put = SetModelMatrixOBB)) matrix4 ModelMatrixOBB;

	/* Gets the color vector of this bounding sphere (the default color in which is going to be rendered) */
	vector3 GetColorOBB(void);
	/* Sets the color vector of this bounding sphere (the default color in which is going to be rendered) */
	void SetColorOBB(vector3 a_v3ColorOBB);
	/* Property:
	GetColor() or SetColor() */
	__declspec(property(get = GetColorOBB, put = SetColorOBB)) vector3 ColorOBB;

		/* Gets the visibility of the Sphere (whether or not it is going to be drawn in render) */
	bool GetVisibleAABB(void);
	/*Sets the visibility of the Sphere (whether or not it is going to be drawn in render)
	Args:
		bool a_bVisible -> true for draw false for not draw*/
	void SetVisibleAABB(bool a_bVisibleAABB);
	/* Property:
	GetVisible() or GetVisible()*/
	__declspec(property(get = GetVisibleAABB, put = SetVisibleAABB)) bool VisibleAABB;

	/* Gets the centroid the bounding sphere */
	vector3 GetCentroidAABB(void);
	/* Property:
	GetCentroid()*/
	__declspec(property(get = GetCentroidAABB)) vector3 CentroidAABB;

	/* Gets the "ModelToWorld" matrix associated with the bounding sphere */
	matrix4 GetModelMatrixAABB(void);
	/* Sets the "ModelToWorld" matrix associated with the bounding sphere */
	void SetModelMatrixAABB(matrix4 a_ModelMatrixAABB);
	/* "ModelToWorld"
	GetModelMatrix() or SetModelMatrix() */
	__declspec(property(get = GetModelMatrixAABB, put = SetModelMatrixAABB)) matrix4 ModelMatrixAABB;

	/* Gets the color vector of this bounding sphere (the default color in which is going to be rendered) */
	vector3 GetColorAABB(void);
	/* Sets the color vector of this bounding sphere (the default color in which is going to be rendered) */
	void SetColorAABB(vector3 a_v3ColorAABB);
	/* Property:
	GetColor() or SetColor() */
	__declspec(property(get = GetColorAABB, put = SetColorAABB)) vector3 ColorABB;

	/* Gets the minimum of the OBB */
	vector3 GetMinimumOBB(void);
	/* Property:
	GetCentroid()*/
	__declspec(property(get = GetMinimumOBB)) vector3 MinimumOBB;

		/* Gets the maximum of the OBB */
	vector3 GetMaximumBB(void);
	/* Property:
	GetCentroid()*/
	__declspec(property(get = GetMaximmumOBB)) vector3 MaximumOBB;

		/* Gets the minimum of the AABB */
	vector3 GetMinimumAABB(void);
	/* Property:
	GetCentroid()*/
	__declspec(property(get = GetCMinimumAABB)) vector3 MinimumAABB;

		/* Gets the maximum of the AABB*/
	vector3 GetMaximumAABB(void);
	/* Property:
	GetCentroid()*/
	__declspec(property(get = GetMaximumAABB)) vector3 MaximumAABB;


	/* Renders the bounding sphere
		Args:
			a_vColor -> determinate the color of the sphere to be rendered, if MEDEFAULT
			it will render the shape in the constructed color (white) */
	void Render( vector3 a_vColor = MEDEFAULT);



private:
	void Release(void);
	void CalculateBox(String a_sInstance);



};

#endif //__BoundingBox_H__

