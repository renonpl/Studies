using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Balance
{
    public class GameManger : MonoBehaviour
    {

        public AudioClip music;
        // Start is called before the first frame update
        void Start()
        {

            MusicManager.Instance.PlayMusic(music);
        }

        // Update is called once per frame
        void Update()
        {
            if (Input.GetKey(KeyCode.Escape))
            {
                Time.timeScale = 1;
                SceneManager.LoadScene("MainMenu");
            }
        }
    }
}
