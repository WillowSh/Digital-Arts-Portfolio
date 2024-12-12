using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class EnterScene : MonoBehaviour
{
    // Start is called before the first frame update
    public void EnterGame()
    {
        SceneManager.LoadScene("SampleScene");

    }
    public void ExitGame()
    {
        Application.Quit();

    }
}
