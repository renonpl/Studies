using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;
using UnityEngine.UI;

namespace Flight
{
    public class GameManager : MonoBehaviour
    {
        public TextMeshProUGUI scoreText;
        public TextMeshProUGUI timerText;

        public ParticleSystem scoreParticle;
        public Flight.Parameters param;
        int timer;

        public AudioClip music;
        public AudioClip pointsUp;

        public int score;
        private int scoreOnText;
        public EndGame eg;
        private string playerName;
        // Start is called before the first frame update
        void Start()
        {
            playerName = PlayerPrefs.GetString("Player", "Test");
            timer = PlayerPrefs.GetInt(playerName + "flightTimer", 120);
            score = 0;
            scoreOnText = 0;
            scoreText.text = "Punkty: " + scoreOnText.ToString();
            Countdown();
            MusicManager.Instance.PlayMusic(music);
            Invoke("UpdateScore", 0.5f);
        }

        // Update is called once per frame
        private void Update()
        {

            if (Input.GetKey(KeyCode.Escape))
            {
                ReturnToMenu();
            }

            if (Input.GetKey(KeyCode.Space))
            {
                PauseGame();
            }
        } 

        private void ReturnToMenu()
        {
            Time.timeScale = 1;
            SceneManager.LoadScene("MainMenu");
        }
        private void PauseGame()
        {
            if (Time.timeScale == 0)
            {
                Time.timeScale = 1;
                return;
            }
            Time.timeScale = 0;
        }

        public void  AddScore(int n)
        {
            if (n > 0)
            {
                ParticleSystem exp = Instantiate(scoreParticle, scoreText.transform.position, scoreParticle.transform.rotation);
                exp.Play();
                MusicManager.Instance.PlayEffect(pointsUp);
            }
            score += n;
        }

        void UpdateScore()
        {
            if (scoreOnText < score) scoreOnText++;
            if (scoreOnText > score) scoreOnText--;
            scoreText.text = "Punkty: " + scoreOnText.ToString();
            Invoke("UpdateScore", 0.25f);
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