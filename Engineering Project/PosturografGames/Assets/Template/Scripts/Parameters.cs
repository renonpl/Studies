using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Template
{
    public class Parameters : MonoBehaviour
    {
        private string playerName;

        public float speedLeft;
        public float speedRight;
        public float speedFront;
        public float speedBack;
        public int checks;
        public int gameTimer;
        // Start is called before the first frame update
        void Start()
        {
            playerName = PlayerPrefs.GetString("Player", "Test");
            speedLeft = PlayerPrefs.GetFloat(playerName + "SpeedLeft", 1f);
            speedRight = PlayerPrefs.GetFloat(playerName + "SpeedRight", 1f);
            speedFront = PlayerPrefs.GetFloat(playerName + "SpeedFront", 1f);
            speedBack = PlayerPrefs.GetFloat(playerName + "SpeedBack", 1f);
            checks = PlayerPrefs.GetInt(playerName + "Checks", 1 << 9 - 1);
            //Debug.Log(speedBack);
        }
    }
}