using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Arkanoid
{

    public class Parameters : MonoBehaviour
    {
        public float playerSpeed;
        public float ballSpeed;
        public float ballMass;
        public int timeCounter;

        public string playerName;

        private void Start()
        {
            /*
            Debug.Log(PlayerPrefs.HasKey("RenonarkBallSpeed"));
            Debug.Log(PlayerPrefs.GetFloat("RenonarkBallSpeed", 6));*/
            playerName = PlayerPrefs.GetString("Player", "Test");
            playerSpeed = PlayerPrefs.GetFloat(playerName + "arkPlSpeed", 0.1f);
            ballSpeed = PlayerPrefs.GetFloat(playerName + "arkBallSpeed", 256);
            timeCounter = PlayerPrefs.GetInt(playerName + "arkTimer", 120);
        }

    }

}