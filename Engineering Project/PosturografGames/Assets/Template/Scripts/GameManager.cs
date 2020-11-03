using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;
using UnityEngine.UI;

namespace Template
{
    public class GameManager : MonoBehaviour
    {
        public TextMeshProUGUI scoreText;
        public TextMeshProUGUI timerText;
        public TextMeshProUGUI finalText;

        public AudioClip music;

        public Template.Parameters param;
        int timer;

        public int score;
        // Start is called before the first frame update
        void Start()
        {

            timer = param.gameTimer;
            score = 0;
            scoreText.text = "Punkty: " + score.ToString();
            Countdown();
            MusicManager.Instance.PlayMusic(music);

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
        public void AddScore(int n)
        {
            score += n;
            scoreText.text = "Punkty: " + score.ToString();
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
            finalText.gameObject.SetActive(true);
            finalText.text = "Wynik: " + score.ToString();
        }
    }

}