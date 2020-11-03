using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Flight
{
    public class PlayerController : MonoBehaviour
    {
        public float speed;
        Vector3 offset;
        public Parameters param;
        //Rigidbody rb;
        //float plane_speed = 10.0f;

        private string playerName;

        void Start()
        {
            playerName = PlayerPrefs.GetString("Player", "Test");
            speed = PlayerPrefs.GetFloat(playerName + "flightSpeed", 0.15f);
            offset = transform.position;
            //rb = GetComponent<Rigidbody>();
        }
        // Update is called once per frame
        void Update()
        {
           // rb.velocity = transform.forward * plane_speed;
            float moveHorizontal = Client.Data.x;
            float moveVertical =  Client.Data.y;
            // float z = transform.position.z;
            transform.position = new Vector3(moveHorizontal, moveVertical, 0f) * speed + offset;// + new Vector3(0f,0f,z);
            if(transform.position.y < -6.5f)
            {
                transform.position = new Vector3(moveHorizontal, 0f, 0f) * speed + offset - new Vector3(0f,6.5f,0f);
            }
        }
    }
}