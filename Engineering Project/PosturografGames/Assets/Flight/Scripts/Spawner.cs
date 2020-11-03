using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Flight
{
    public class Spawner : MonoBehaviour
    {

        public GameObject coin;
        public GameObject enemy;
        public int distanceAhead;
        public float screenBorderX;
        public float screenBorderY;
         float screenBorderXLeft;
         float screenBorderYTop;
         float screenBorderXRight;
         float screenBorderYDown;
        public float minDelay;
        public float maxDelay;
        public float coinSpeed;
        public float enemySpeed;
        public float enemySpawnRate;

        public float islandSpeed;
        public int islandSize;
        public GameObject[] island;

        float timer;
        Vector3 spawnPosition;
        GameObject playerPlane;

        public GameManager gm;


        void Start()
        {
            timer = Random.Range(minDelay, maxDelay);
            playerPlane = GameObject.FindGameObjectWithTag("Player");
            int temp = islandSize;
            islandSize = 0;

            SpawnIsland();
            islandSize = temp / 2;

            SpawnIsland();
            islandSize = temp;
            SpawnIsland();
            CheckBorders();
        }

        void Update()
        {
            timer -= Time.deltaTime;
            if (timer <= 0)
            {
                float t = Random.Range(0.0f, 1.0f);
                if (t < enemySpawnRate) SpawnEnemy();
                else SpawnCoin();
                timer = Random.Range(minDelay, maxDelay);
            }
        }

        void SpawnCoin()
        {
            while (true)
            { 
                spawnPosition = playerPlane.transform.position;
                spawnPosition.z += distanceAhead;
                spawnPosition.x = Random.Range(screenBorderXLeft, screenBorderXRight);
                spawnPosition.y = Random.Range(screenBorderYDown, screenBorderYTop);
                RaycastHit hit;
                Ray ray = new Ray(spawnPosition + new Vector3(0, 1f) * 100, Vector3.down);
                int layerMask = 1 << 9; //TerrainLayer
                if (Physics.Raycast(ray, out hit, 101, layerMask))
                {
                    if (hit.collider.CompareTag("Terrain"))
                    {
                        continue;
                    }
                }
                break;
             }
            GameObject coinObject = (GameObject)Instantiate(coin, spawnPosition, coin.transform.rotation);
            coinObject.GetComponent<Flight.PickUps>().speed = coinSpeed;
        }
        void SpawnEnemy()
        {
            while (true)
            {
                spawnPosition = playerPlane.transform.position;
                spawnPosition.z += distanceAhead;
                spawnPosition.x = Random.Range(screenBorderXLeft, screenBorderXRight);
                spawnPosition.y = Random.Range(screenBorderYDown, screenBorderYTop);
                bool next = true;
                foreach (GameObject sp in enemy.GetComponent<Enemy>().raycastPoints)
                {
                    RaycastHit hit;
                    Vector3 rayPoint = sp.transform.position - enemy.transform.position;
                    Ray ray = new Ray(spawnPosition + rayPoint, Vector3.back);
                    int layerMask = 1 << 9; //TerrainLayer
                   // Debug.DrawRay(spawnPosition + rayPoint, Vector3.back * distanceAhead, Color.white, 10.0f);
                    if (Physics.Raycast(ray, out hit, distanceAhead, layerMask))
                    {
                        //   Debug.Log(hit.collider.tag);
                        if (hit.collider.CompareTag("Terrain"))
                        {
                            next = false;
                            break;
                        }
                    }
                }
                if(next == true) break;
                continue;
            }
            GameObject enemyObject = (GameObject)Instantiate(enemy, spawnPosition, enemy.transform.rotation);
            enemyObject.GetComponent<Flight.Enemy>().speed = enemySpeed;
        }
        public void SpawnIsland()
        {
            int i = (int)Random.Range(0, island.Length);
            
            GameObject newIsland = (GameObject)Instantiate(island[i], new Vector3(-50,-10,2*islandSize), island[i].transform.rotation);
            newIsland.GetComponent<Flight.IslandController>().sp = this;
            newIsland.GetComponent<Flight.IslandController>().speed = islandSpeed;
        }

        void CheckBorders()
        {
            screenBorderXLeft = -screenBorderX;
            screenBorderXRight = screenBorderX;
            screenBorderYTop = screenBorderY;
            screenBorderYDown = -screenBorderY;
            int checks = gm.param.checks;
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