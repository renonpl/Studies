using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using UnityEngine.SceneManagement;

namespace Arkanoid
{

    public class GameManager : MonoBehaviour
    {
        public Parameters param;
        public int timer;
        public int score;
        public TextMeshProUGUI timerText;
        public TextMeshProUGUI scoreText;

        public ParticleSystem scoreParticle;

        public EndGame eg;
        public AudioClip music;

        public AudioClip pointsUp;
        public GameObject playerBall;

        private string playerName;

        void Start()
        {
            playerName = PlayerPrefs.GetString("Player", "Test");
            timer = PlayerPrefs.GetInt(playerName + "arkTimer", 120);
            scoreText.text = "Punkty: " + score.ToString();
            timerText.text = "Czas: " + timer.ToString();
            score = 0;

            MusicManager.Instance.PlayMusic(music);
            Invoke("TimeUp", 1f);
        }

        private void Update()
        {
            if (Input.GetKey(KeyCode.Escape))
            {
                Time.timeScale = 1;
                SceneManager.LoadScene("MainMenu");
            }
        }

        public void TimeUp()
        {
            timer--;
            timerText.text = "Czas: " + timer.ToString();
            if (0 >= timer)
            {

                eg.End(score, param.playerName);
                Time.timeScale = 0f;
            }
            Invoke("TimeUp", 1f);
        }

        public void AddScore(int ammount)
        {
            score += ammount;
            MusicManager.Instance.PlayEffect(pointsUp);


            scoreText.text = "Punkty: " + score.ToString();
            GameObject[] brick = GameObject.FindGameObjectsWithTag("Brick");
            if (brick.Length == 0)
            {
                AddScore(timer);
                timer = 0;
            }
        }
    }
}