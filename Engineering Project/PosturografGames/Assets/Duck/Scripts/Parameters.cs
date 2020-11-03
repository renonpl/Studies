using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
namespace Duck
{
    public class Parameters : MonoBehaviour
    {
        public float playerSpeed;
        public float onTargetTimer;

        public float spawnRate;
        public int birdStayTimer;

        public float movingBirdSpeed;
        public float staticBirdSpeed;
        public float fallingBirdSpeed;

        public bool spawnStaticBird;
        public bool spawnMovingBird;

        public int gameTimer;
        public int checks;

        public string playerName;
        private void Start()
        {
            playerName = PlayerPrefs.GetString("Player", "Test");
            checks = PlayerPrefs.GetInt(playerName + "Checks", 1 << 9 - 1);

            spawnMovingBird = Convert.ToBoolean(PlayerPrefs.GetInt(playerName + "dMovingBird", 1));
            spawnStaticBird = Convert.ToBoolean(PlayerPrefs.GetInt(playerName + "dStaticBird", 1));
            movingBirdSpeed = PlayerPrefs.GetFloat(playerName + "dBirdSpeed", 1.5f);
            staticBirdSpeed = movingBirdSpeed * 5f / 3f;
            fallingBirdSpeed = movingBirdSpeed * 2;
            onTargetTimer = PlayerPrefs.GetFloat(playerName + "dTargetTimer", 2f);
            gameTimer = PlayerPrefs.GetInt(playerName + "dGameTimer", 120);
            birdStayTimer = PlayerPrefs.GetInt(playerName + "dBirdStay", 10);
            spawnRate = PlayerPrefs.GetFloat(playerName + "dSpawnRate", 4f);
            playerSpeed = PlayerPrefs.GetFloat(playerName + "dPlayerSpeed", 0.05f);
        }
    }
}
