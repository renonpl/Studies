using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
namespace Puzzle
{
    public class Parameters : MonoBehaviour
    {
        public float playerSpeedx;
        public float playerSpeedy;

        public float catchTimer;
        public float putTimer;

        public float speedLeft;
        public float speedRight;
        public float speedFront;
        public float speedBack;
        public int checks;
        public int gameTimer;

        private string playerName;
        private void Start()
        {
            playerName = PlayerPrefs.GetString("Player", "Test");

            speedLeft = PlayerPrefs.GetFloat(playerName + "SpeedLeft", 1f);
            speedRight = PlayerPrefs.GetFloat(playerName + "SpeedRight", 1f);
            speedFront = PlayerPrefs.GetFloat(playerName + "SpeedFront", 1f);
            speedBack = PlayerPrefs.GetFloat(playerName + "SpeedBack", 1f);
            checks = PlayerPrefs.GetInt(playerName + "Checks", 1 << 9 - 1);

            catchTimer = PlayerPrefs.GetFloat(playerName + "dCatchTimer", 1.5f);
            putTimer = PlayerPrefs.GetFloat(playerName + "dPutTimer", 1.5f);

            playerSpeedx = PlayerPrefs.GetFloat(playerName + "dPlayerSpeedx", 0.17f);
            playerSpeedy = PlayerPrefs.GetFloat(playerName + "dPlayerSpeedy", 0.12f);

        }
    }
}
