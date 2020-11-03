using UnityEngine;
using UnityEngine.UI;

namespace Puzzle
{

    public class PuzzelScript : MonoBehaviour
    {

        private Vector2 initialPosition;
        float timer;
        float timer1;
        public Transform LoadingBar;



        private bool isCollision = false;

        public static bool notBusy = true;

        public AudioClip audioFail;

        public GameObject hand;

        public Parameters param;



        void Start()
        {

            initialPosition = gameObject.transform.position;
            timer = param.catchTimer;
            timer1 = timer;
            LoadingBar.gameObject.SetActive(false);




        }

        // Update is called once per frame
        void Update()
        {

            if (isCollision == true)
            {

                timer -= Time.deltaTime;

                LoadingBar.GetComponent<Image>().fillAmount = (timer) / timer1;

            }





        }

        void OnTriggerEnter2D(Collider2D other)
        {

            if (other.gameObject.tag != gameObject.tag && other.gameObject.tag != "Player")
            {

                MusicManager.Instance.PlayEffect(audioFail);
                gameObject.transform.position = initialPosition;
                notBusy = true;
                PuzzlePlaceScript.trial++;

            }
            if (other.gameObject.tag == "Player" && notBusy)
            {
                LoadingBar.gameObject.SetActive(true);
                //LoadingBar.transform.position = gameObject.transform.position;
                LoadingBar.transform.position = new Vector3(gameObject.transform.position.x, gameObject.transform.position.y, 0);
                isCollision = true;
            }



        }

        void OnTriggerStay2D(Collider2D other)
        {
            if (other.gameObject.tag == "Player" && isCollision == true)
            {
                if (timer <= 0)
                {
                    LoadingBar.gameObject.SetActive(false);

                    gameObject.transform.position = new Vector3(hand.transform.position.x+0.96f, hand.transform.position.y + 2.75f, 0);
                    gameObject.transform.rotation = hand.transform.rotation;

                    notBusy = false;
                }

            }


        }

        void OnTriggerExit2D(Collider2D other)
        {
            if (other.gameObject.tag == "Player")

            {
                gameObject.transform.position = initialPosition;
                LoadingBar.gameObject.SetActive(false);
                notBusy = true;
                isCollision = false;
                timer = timer1;
            }


        }
    }

}