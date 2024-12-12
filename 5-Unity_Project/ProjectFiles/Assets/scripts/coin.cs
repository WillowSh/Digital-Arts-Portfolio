using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class coin : MonoBehaviour
{
    private void OnTriggerEnter(Collider other){
        Destroy(this.gameObject);
    }
    
}
