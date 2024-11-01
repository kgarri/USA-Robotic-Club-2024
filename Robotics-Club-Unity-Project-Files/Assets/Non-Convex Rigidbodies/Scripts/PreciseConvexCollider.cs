//----------------------------------------------
//          Non-Convex Rigidbodies
//
// Copyright © 2023 A.C.E.Y.T.X
// The Redistribution/Resale of this script in any form is strictly prohibited
// Aneesh Balaji
//
//----------------------------------------------

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DigitalGlitch.AccurateMesh
{

    [ExecuteAlways]
    [RequireComponent(typeof(MeshFilter))]
   
    public class PreciseConvexCollider : MonoBehaviour
    {               
        // Helper Function to Add Elements to an Array
        Mesh[] AddToArray(Mesh[] array, Mesh element)
        {
            Mesh[] newArray = new Mesh[array.Length + 1];
            array.CopyTo(newArray, 0);
            newArray[array.Length] = element;
            return newArray;
        }        

        // Function to Create the Meshes and the Components
        public void Split(Mesh inMesh)
        {
            Vector3[] vertices = inMesh.vertices;
            int[] triangles = inMesh.triangles;

            // create an array to store the convex parts of the mesh
            Mesh[] convexMeshes = new Mesh[0];
            int convexMeshCount = 0;

            // create a convex hull for each set of triangles
            for (int i = 0; i < triangles.Length; i += 3)
            {
                Vector3[] convexVertices = new Vector3[4];
                convexVertices[0] = vertices[triangles[i]];
                convexVertices[1] = vertices[triangles[i + 1]];
                convexVertices[2] = vertices[triangles[i + 2]];
                convexVertices[3] = convexVertices[2] + new Vector3(0, 0.0001f, 0);
                Mesh convexMesh = new Mesh();
                convexMesh.vertices = convexVertices;
                convexMesh.triangles = new int[] { 0, 1, 2 };
                convexMesh.RecalculateNormals();
                convexMeshes = AddToArray(convexMeshes, convexMesh);
                convexMeshCount++;
            }


            GameObject convexObjectHolder = new GameObject("Precise Convex Collider");
            convexObjectHolder.hideFlags = HideFlags.HideInHierarchy;            
            convexObjectHolder.transform.parent = transform;
            // create gameobjects for each convex part and add mesh colliders
            for (int i = 0; i < convexMeshCount; i++)
            {
                GameObject convexObject = new GameObject("Convex Part " + i);
                convexObject.transform.position = transform.position;
                convexObject.transform.rotation = transform.rotation;
                convexObject.transform.localScale = transform.lossyScale;
                convexObject.transform.parent = convexObjectHolder.transform;
                MeshFilter meshFilter = convexObject.AddComponent<MeshFilter>();
                meshFilter.mesh = convexMeshes[i];
                MeshCollider meshCollider = convexObject.AddComponent<MeshCollider>();
                meshCollider.convex = true;
                //MeshRenderer meshRenderer = convexObject.AddComponent<MeshRenderer>();
                //meshRenderer.sharedMaterial = ConvexObjectMaterial;
                convexObject.AddComponent<ConvexObject>();
            }
        }

        // Function to Merge the Convex Components
        public void MergeColliders(List<MeshCollider> colsToMerge)
        {
            if (colsToMerge == null)
            {
                Debug.LogError("No meshes are selected");
            }
            else
            {
                Mesh newMesh = new Mesh();
                List<Vector3> vertices = new List<Vector3>();
                List<int> triangles = new List<int>();
                foreach (MeshCollider item in colsToMerge)
                {
                    vertices.Add(item.sharedMesh.vertices[0]);
                    vertices.Add(item.sharedMesh.vertices[1]);
                    vertices.Add(item.sharedMesh.vertices[2]);
                    triangles.Add(item.sharedMesh.triangles[0]);
                    triangles.Add(item.sharedMesh.triangles[1]);
                    triangles.Add(item.sharedMesh.triangles[2]);
                    item.gameObject.SetActive(false);
                }
                newMesh.vertices = vertices.ToArray();
                newMesh.triangles = triangles.ToArray();
                newMesh.RecalculateNormals();
                GameObject co = new GameObject("Large Convex Part");
                co.transform.parent = transform.Find("Precise Convex Collider");
                co.transform.position = transform.position;
                co.transform.rotation = transform.rotation;
                co.transform.localScale = transform.lossyScale;
                co.AddComponent<MeshCollider>().sharedMesh = newMesh;
                co.GetComponent<MeshCollider>().convex = true;
                colsToMerge = new List<MeshCollider>();
            }

        }

        //Function to Delete the Objects
        public void DeleteColliders()
        {
            DestroyImmediate(transform.Find("Precise Convex Collider").gameObject);
        }

        //OnStart is used instead of OnAwake to regenerate the collider in case the convex object holder is deleted.
        public void Start()
        {
            if (!transform.Find("Precise Convex Collider"))
            {                         
                Split(GetComponent<MeshFilter>().sharedMesh);
            }            
        }

        public void OnDestroy()
        {
            DeleteColliders();
        }
    }
}
