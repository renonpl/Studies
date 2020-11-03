using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Puzzle
{
    public class Hand : MonoBehaviour
    {

        private Vector3 initialPosition;
        float speed_x;
        float speed_y;
        Vector3 offset;
        public Parameters param;
        public float fScale;

        public AudioClip music;
        private string playerName;



        void Start()
        {
            playerName = PlayerPrefs.GetString("Player", "Test");
            fScale = PlayerPrefs.GetFloat(playerName + "puzzleSpeed", 0.045f);
            offset = transform.position;
            speed_x = fScale;
            speed_y = fScale * 0.88f;

            MusicManager.Instance.PlayMusic(music);

/*
            speed_x = param.playerSpeedx;
            speed_y = param.playerSpeedy;
            */
        }

        // Update is called once per frame
        void Update()
        {
            /* if (Input.GetKey(KeyCode.LeftArrow))
             {
                 transform.position += Vector3.left * speed * Time.deltaTime;
             }
             if (Input.GetKey(KeyCode.RightArrow))
             {
                 transform.position += Vector3.right * speed * Time.deltaTime;
             }
             if (Input.GetKey(KeyCode.UpArrow))
             {
                 transform.position += Vector3.up * speed * Time.deltaTime;
             }
             if (Input.GetKey(KeyCode.DownArrow))
             {
                 transform.position += Vector3.down * speed * Time.deltaTime;
             } */
            float moveHorizontal = Client.Data.x;
            float moveVertical = Client.Data.y;
            transform.position = new Vector3(moveHorizontal * speed_x, moveVertical * speed_y, 0f) + offset;

        }

    }
}