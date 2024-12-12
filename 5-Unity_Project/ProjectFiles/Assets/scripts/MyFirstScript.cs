using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MyFirstScript : MonoBehaviour
{
    #region Atrributes

    public int a ;
    public float b;
    public bool c;
    public string d;

    public GameObject ob;
    public Transform oc;


    #endregion

    #region function
    private void Awake(){
    }

    // Start is called before the first frame update
    void Start()
    {
        a=5;
        print(a);
        print(d);
        //ob.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        //ob.transform.Rotate(0,30*Time.deltaTime,0);
        //oc.Rotate(0,50*Time.deltaTime,0);
        // oc.gameObject;
        if(Input.GetKeyDown(KeyCode.W)){
            print("w按下");
        }
        if(Input.GetMouseButtonDown(0)){
            Debug.Log("鼠标左键按下");
        }
        if(Input.GetMouseButtonDown(1)){
            Debug.Log("鼠标右键按下");
        }
        if(Input.GetMouseButtonDown(2)){
            Debug.Log("鼠标中键按下");
        }
        //print(oc.name);

    }
    private void OnMouseEnter(){
        Debug.Log("鼠标进入Cube");
        GetComponent<MeshRenderer>().material.color=Color.blue;
        ob.GetComponent<MeshRenderer>().material.color=Color.green;
        transform.localScale=new Vector3(1.2f, 1.2f, 1.2f);
    }

    private void OnMouseExit(){
        Debug.Log("鼠标离开Cube");
        GetComponent<MeshRenderer>().material.color=Color.red;
        transform.localScale=new Vector3(1f, 1f, 1f);
    }
    #endregion
}
