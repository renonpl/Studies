using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.UI;

namespace Duck
{
    public class MainController : MonoBehaviour
    {
        float speed;
        float countdownTimer;
        public Camera cam;

        bool onTarget;
        float countdown;

        int score;
        public TextMeshProUGUI scoreText;
        public TextMeshProUGUI timerText;
        public TextMeshProUGUI finalText;

        public Parameters param;
        public Image bar;
        int timer;

        Vector3 offset;

        public EndGame eg;
        private string playerName;

        void Start()
        {
            playerName = PlayerPrefs.GetString("Player", "Test");
            offset = transform.position;
            speed = PlayerPrefs.GetFloat(playerName + "duckPlSpeed", 0.008f);
            countdownTimer = param.onTargetTimer;
            timer = PlayerPrefs.GetInt(playerName + "duckTimer", 120);
            score = 0;
            onTarget = false;
            countdown = countdownTimer;
            Invoke("Countdown", 0);
            scoreText.text = "Punkty: " + score.ToString();
        }

        void Update()
        {
            /*
                float moveHorizontal = Input.GetAxis("Horizontal");
                float moveVertical = Input.GetAxis("Vertical");
            */
            float moveHorizontal = Client.Data.x;
            float moveVertical = Client.Data.y;
            transform.position = new Vector3(moveHorizontal, moveVertical, 0f) * speed + offset;

            CheckTarget();
        }

        void CheckTarget()
        {
            RaycastHit hit;
            if (Physics.Raycast(cam.transform.position, transform.position - cam.transform.position, out hit))
            {
                if (hit.collider.CompareTag("Enemy"))
                {
                    if (hit.collider.GetComponent<TargetController>().dead) return;
                    if (onTarget == false)
                    {
                        onTarget = true;
                        countdown = countdownTimer;

                    }
                    else
                    {
                        float amount = (countdownTimer - countdown) / countdownTimer;
                        bar.fillAmount = amount;
                        countdown -= Time.deltaTime;
                        if (countdown <= 0) Shoot(hit);
                    }

                }
                else
                {
                    bar.fillAmount = 0;
                    onTarget = false;
                }
            }
            else onTarget = false;
            Vector3 forward = transform.TransformDirection(Vector3.forward) * 400;
            //  Debug.DrawRay(cam.transform.position, (transform.position - cam.transform.position)*400, Color.green);
        }

        void Shoot(RaycastHit hit)
        {
            bar.fillAmount = 0;
            score++;
            scoreText.text = "Punkty: " + score.ToString();
            Debug.Log("Zastrzelony");
            hit.collider.gameObject.GetComponent<TargetController>().Die();
            countdown = countdownTimer;
        }

        void Countdown()
        {
            timer--;
            timerText.text = timer.ToString();
            if (timer <= 0)
            {
                EndGame();
                return;
            }
            Invoke("Countdown", 1f);
        }

        void EndGame()
        {
            Time.timeScale = 0;
            eg.End(score, param.playerName);
        }
    }

}