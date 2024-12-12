using System.Collections;
using System.Collections.Generic;
using JetBrains.Annotations;
using UnityEngine;
using UnityEngine.UI;

public class man : MonoBehaviour
{
    public Animator manAnimator;
    public float speed;
    public CharacterController manCon;
    public Slider slider;
    public bool go;
    // Start is called before the first frame update
    void Start()
    {
        manAnimator=GetComponent<Animator>();
        manCon=GetComponent<CharacterController>();
        speed=2;
    }

    // Update is called once per frame
    void Update()
    {
        if(Input.GetKey(KeyCode.W)){
            manAnimator.SetBool("run",true);
            manCon.SimpleMove(transform.forward*speed);
            //transform.Translate(transform.forward*Time.deltaTime*speed);
        }
        else if(Input.GetKey(KeyCode.S)){
            manAnimator.SetBool("back",true);
            manCon.SimpleMove(-transform.forward*speed);
            //transform.Translate(transform.forward*Time.deltaTime*speed);
        }
        else if(Input.GetKey(KeyCode.A)){
            transform.Rotate(0,-30*Time.deltaTime,0);
        }
        else if(Input.GetKey(KeyCode.D)){
            transform.Rotate(0,30*Time.deltaTime,0);
        }
        else{
            manAnimator.SetBool("run",false);
            manAnimator.SetBool("back",false);
        }
        if(go){
            manAnimator.SetBool("run",true);
            manCon.SimpleMove(transform.forward*speed);
        }
    }
    private void OnTriggerEnter(Collider other){
        slider.value-=0.1f;
        Destroy(other.gameObject);
    }
    public void GoForward(){
        go=!go;
    }
    public void StopGo(){
        go=false;
    }
}

