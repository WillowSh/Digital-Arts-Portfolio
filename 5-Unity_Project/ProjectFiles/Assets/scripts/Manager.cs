using System;
using System.Collections;
using System.Collections.Generic;
using JetBrains.Annotations;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.UI;

public class Manager : MonoBehaviour
{
    public GameObject panel;
    public AudioSource audioSource;
    public Slider musicSlider;
    //public AudioClip[] audioClip;
    public Text content;
    public string[] contents;
    public int contentID;
    public GameObject sound;
    private void Start(){
        audioSource=GetComponent<AudioSource>();
        content.text=contents[0];
    }
    // Update is called once per frame
    private void Update()
    {
        if(Input.GetKeyDown(KeyCode.Escape)){
            panel.SetActive(!panel.activeSelf);
        }
        if(musicSlider.gameObject.activeSelf){
            audioSource.volume=musicSlider.value;
        }
        if(Input.GetKeyDown(KeyCode.Alpha1)){
            PlaySound(sound.GetComponent<Sound>().audioClips[0]);
            //PlaySound(audioClip[0]);
        }
        if(Input.GetKeyDown(KeyCode.Alpha2)){
            PlaySound(sound.GetComponent<Sound>().audioClips[1]);
            //PlaySound(audioClip[1]);
        }
        if(Input.GetKeyDown(KeyCode.Alpha3)){
            PlaySound(sound.GetComponent<Sound>().audioClips[2]);
            //PlaySound(audioClip[2]);
        }
        if(Input.GetKeyDown(KeyCode.Space)){
            
            contentID++;
            if(contentID>2){
                contentID=0;
            }
            content.text=contents[contentID];
        }
       
    }
     public void PlaySound(AudioClip clip){
            audioSource.clip=clip;
            audioSource.Play();
        }

}
