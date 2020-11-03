using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Arkanoid
{

    public class PlayerController : MonoBehaviour
    {
        public float speed;
        Vector3 offset;
        private string playerName;

        public Parameters param;

        // Start is called before the first frame update
        void Start()
        {
            offset = transform.position;
            //speed = param.playerSpeed;
           // Invoke("CheckPar", 0.5f);
            playerName = PlayerPrefs.GetString("Player", "Test");
            speed = PlayerPrefs.GetFloat(playerName + "arkPlSpeed", 0.03f);
        }

        void CheckPar()
        {
            speed = param.playerSpeed;
        }
        // Update is called once per frame
        void Update()
        {
            float moveHorizontal = Client.Data.x;
            // float moveVertical =  Client.Data.y;
            transform.position = new Vector3(moveHorizontal, 0f, 0f) * speed + offset;
            if (transform.position.x > 12.0f) transform.position = new Vector3(12.0f, 0) + offset;
            if (transform.position.x < -12.0f) transform.position = new Vector3(-12.0f, 0) + offset;

        }
    }

}