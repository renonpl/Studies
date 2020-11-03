using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using TMPro;


namespace Puzzle
{

    public class PuzzlePlaceScript : MonoBehaviour
    {

        private Vector3 initialPosition;
        float put_timer;
        float put_timer1;
        public Transform put_LoadingBar;

        public static bool end; 
        public static int trial;
        
        private bool isCollision = false;

        public GameObject puzzel;
        public GameObject puzzelPlace;
        public GameObject puzzelhid;

        public AudioClip audioMatch;
        public AudioClip audioWin;

        public Text winText;
        public GameObject hand;

        public Parameters param;



        void Start()
        {
            put_LoadingBar.gameObject.SetActive(false);
            puzzelhid.GetComponent<Renderer>().enabled = false;
            puzzelhid.GetComponent<Collider2D>().enabled = false;
            put_timer = param.putTimer;
            put_timer1 = put_timer;
            trial = 1;
            end = false;


        }

        // Update is called once per frame
        void Update()
        {

            if (isCollision == true)
            {
                put_timer -= Time.deltaTime;
                put_LoadingBar.GetComponent<Image>().fillAmount = (put_timer) / put_timer1;

            }

            if (Input.GetKey(KeyCode.Escape))
            {
                Time.timeScale = 1;
                SceneManager.LoadScene("MainMenu");
            }


        }


        void OnTriggerEnter2D(Collider2D other)
        {


            if (other.gameObject.tag == gameObject.tag)
            {
                put_LoadingBar.gameObject.SetActive(true);
                //put_LoadingBar.transform.position = gameObject.transform.position;
                put_LoadingBar.transform.position = new Vector3(gameObject.transform.position.x, gameObject.transform.position.y, 0);
                isCollision = true;
            }




        }

        void OnTriggerStay2D(Collider2D other)
        {
            if (other.gameObject.tag == gameObject.tag && isCollision == true)
            {
                if (put_timer <= 0)
                {
                   // trial--;
                    put_LoadingBar.gameObject.SetActive(false);
                    gameObject.transform.position = other.gameObject.transform.position;
                    gameObject.transform.rotation = other.gameObject.transform.rotation;

                    MusicManager.Instance.PlayEffect(audioMatch);
                    if (trial == 1) GameManager.score += 3;
                    else if (trial == 2) GameManager.score += 2;
                    else if (trial == 3) GameManager.score += 1;
                    trial = 0;


                    if (other.gameObject.tag == "Puzzle1")
                    {
                        MusicManager.Instance.PlayEffect(audioWin);
                        end = true;
                    }
                    Destroy(gameObject);
                    Destroy(other.gameObject);

                    puzzelhid.GetComponent<Renderer>().enabled = true;
                    puzzelhid.GetComponent<Collider2D>().enabled = true;

                    PuzzelScript.notBusy = true;
                }

            }


        }

        void OnTriggerExit2D(Collider2D other)
        {
            if (other.gameObject.tag == gameObject.tag)
            {
                trial++;
                put_LoadingBar.gameObject.SetActive(false);
                isCollision = false;
                put_timer = put_timer1;
            }


        }


    }

}