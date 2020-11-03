using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Balance
{
    public class KeyController : MonoBehaviour
    {
        private string playerName;
        public float fScale;
        Vector3 offset;

        private void Start()
        {
            playerName = PlayerPrefs.GetString("Player", "Test");
            fScale = PlayerPrefs.GetFloat(playerName + "labSpeed", 0.02f);
        }
        void Update()
        {
            if (Input.GetKey(KeyCode.Escape))
            {
                Time.timeScale = 1;
                SceneManager.LoadScene("MainMenu");
            }


            /* transform.rotation *=
                         Quaternion.AngleAxis(Input.GetAxis("Horizontal") * 25.0f * Time.deltaTime, new Vector3(0, 0, 1));

            transform.rotation *=
         Quaternion.AngleAxis(Input.GetAxis("Vertical") * 25.0f * Time.deltaTime, new Vector3(1, 0, 0)); */

            float moveHorizontal = Client.Data.x * fScale + 180.0f;
            float moveVertical = -Client.Data.y * fScale;
            transform.rotation = Quaternion.identity;
            transform.Rotate(moveVertical, 0, moveHorizontal);
        }


    }
}