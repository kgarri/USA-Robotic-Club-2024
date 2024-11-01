using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CombineAsembly : MonoBehaviour
{
    [SerializeField] float rotateSpeed = 1;
    [SerializeField] float moveSpeed = 0.1f;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        //Change transform.position based on the axes
        Vector3 pos = transform.position;
        pos.x += moveSpeed * Time.deltaTime;
        transform.position = pos;

        //Rotate the ship to make it feel more dynamic
       transform.Rotate(0, 0, rotateSpeed);
    }
}
