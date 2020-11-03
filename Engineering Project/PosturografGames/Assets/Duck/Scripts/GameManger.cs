using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Duck
{
    public class GameManger : MonoBehaviour
    {
        public Transform leftSpawn;
        public Transform rightSpawn;
        public Transform upperSpawn;
        public Transform upperFly;

        public int distanceAhead;
        public float screenBorderX;
        public float screenBorderY;
        float screenBorderXLeft;
        float screenBorderYTop;
        float screenBorderXRight;
        float screenBorderYDown;

        float size;
        Vector3 offset;

        public Parameters param;
        public GameObject eagle;


        Vector3 spawnPosition;
        GameObject player;

        public AudioClip music;

        GameObject[] pointTable;

        private string playerName;

        void Start()
        {
            size = leftSpawn.transform.position.y;
            offset = new Vector3(0, size);
            player = GameObject.FindGameObjectWithTag("Player");

            pointTable = GameObject.FindGameObjectsWithTag("Points");
            playerName = PlayerPrefs.GetString("Player", "Test");
    

            MusicManager.Instance.PlayMusic(music);
            Invoke("CheckBorders", 0.5f);
            Invoke("SpawnEagle", 1f);
        }

        private void Update()
        {
            if (Input.GetKey(KeyCode.Escape))
            {
                Time.timeScale = 1;
                SceneManager.LoadScene("MainMenu");
            }
        }


        void SpawnEagle()
        {
            bool generating = true;
            while (generating)
            {
                int num = Random.Range(0, 2);
                switch (num)
                {
                    case 0:
                        if (param.spawnMovingBird)
                        {
                            SpawnMoving();
                            generating = false;
                        }
                        break;
                    case 1:
                        if (param.spawnStaticBird)
                        {
                            SpawnStatic();
                            generating = false;
                        }
                        break;
                }
            }
            Invoke("SpawnEagle", param.spawnRate);
        }

        void SpawnMoving()
        {
            Transform start, end;
            if (Random.Range(0, 2) == 0)
            {
                start = rightSpawn;
                end = leftSpawn;
            }
            else
            {
                start = leftSpawn;
                end = rightSpawn;
            }

            Vector3 vect = new Vector3(0, Random.Range(1, 2 * size));
            GameObject temp = Instantiate(eagle, start.transform.position - offset + vect, start.transform.rotation);
            TargetController controller = temp.GetComponent<TargetController>();
            controller.target = end.position;
            controller.movingBird = true;
            controller.target += vect - offset;
            controller.maxSpeed = PlayerPrefs.GetFloat(playerName + "duckSpeed", 1.5f);
            controller.fallingSpeed = param.fallingBirdSpeed;
            controller.gm = this;
        }

        void SpawnStatic()
        {
            spawnPosition = player.transform.position;
            spawnPosition.z += distanceAhead;
            spawnPosition.x = Random.Range(screenBorderXLeft, screenBorderXRight);
            spawnPosition.y = Random.Range(screenBorderYTop, screenBorderYDown) + 3f;

            Transform start = upperSpawn;
            GameObject temp = Instantiate(eagle, start.transform.position, start.transform.rotation);
            TargetController controller = temp.GetComponent<TargetController>();
           // controller.target = upperSpawn.transform;
            controller.target = spawnPosition;
            controller.staticBird = true;
            controller.maxSpeed = param.staticBirdSpeed;
            controller.fallingSpeed = param.fallingBirdSpeed;
            controller.birdStayTimer = param.birdStayTimer;
            controller.gm = this;
        }
   

    void CheckBorders()
    {
           
            screenBorderXLeft = -screenBorderX;
        screenBorderXRight = screenBorderX;
        screenBorderYTop = screenBorderY;
        screenBorderYDown = -screenBorderY;
            int checks = param.checks;
        if (!System.Convert.ToBoolean(checks & ChecksCounter.firstC))
        {
            if (!System.Convert.ToBoolean(checks & ChecksCounter.secondC))
                screenBorderXLeft = screenBorderX * 4.0f / 3.0f + (-1.0f * screenBorderX);
            else
                screenBorderXLeft = screenBorderX * 2.0f / 3.0f + (-1.0f * screenBorderX);
        }
        if (!System.Convert.ToBoolean(checks & ChecksCounter.thirdC))
        {
            if (!System.Convert.ToBoolean(checks & ChecksCounter.secondC))
                screenBorderXRight = screenBorderX - screenBorderX * 4.0f / 3.0f;
            else
                screenBorderXRight = screenBorderX - screenBorderX * 2.0f / 3.0f;
        }
        if (!System.Convert.ToBoolean(checks & ChecksCounter.firstV))
        {
            if (!System.Convert.ToBoolean(checks & ChecksCounter.secondV))
                screenBorderYTop = screenBorderY - screenBorderY * 4.0f / 3.0f;
            else
                screenBorderYTop = screenBorderY - screenBorderY * 2.0f / 3.0f;
        }


        if (!System.Convert.ToBoolean(checks & ChecksCounter.thirdV))
        {

                if (!System.Convert.ToBoolean(checks & ChecksCounter.secondV))
                screenBorderYDown = (-1.0f * screenBorderY) + screenBorderY * 4.0f / 3.0f;
            else
                screenBorderYDown = (-1.0f * screenBorderY) + screenBorderY * 2.0f / 3.0f;
        }

        }
}
}