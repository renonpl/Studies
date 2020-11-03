using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;
using UnityEngine.UI;

namespace Puzzle
{
    public class GameManager : MonoBehaviour
    {
        public TextMeshProUGUI scoreText;
        public TextMeshProUGUI timerText;
        public TextMeshProUGUI finalText;
        public TextMeshProUGUI trialText;
        public static int scoreOnText;


        public AudioClip music;

        public Puzzle.Parameters param;
        public static int timer;

        public static int score;
        // Start is called before the first frame update
        void Start()
        {

            trialText.gameObject.SetActive(true);
            timer = param.gameTimer;
            score = 0;
            scoreText.text = "Punkty: " + score.ToString();
            scoreOnText = 0;
            Countdown();
            MusicManager.Instance.PlayMusic(music);
            Invoke("UpdateScore", 0.5f);
            UpdateTrial();


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

        void UpdateScore()
        {
            if (scoreOnText < GameManager.score) scoreOnText++;
            scoreText.text = "Punkty: " + scoreOnText.ToString();
            if (!PuzzlePlaceScript.end)
            {
                Invoke("UpdateScore", 0.25f);
            }
            else{
                Invoke("UpdateScore", 0.0f);
            }
        }

        void UpdateTrial()
        {
            trialText.text = "Proba: " + PuzzlePlaceScript.trial.ToString();

            Invoke("UpdateTrial", 0.25f);

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

        void Countdown()
        {
            timer--;
            timerText.text = timer.ToString(); ;
            if (timer <= 0 || PuzzlePlaceScript.end)
            {
                EndGame();
                return;
            }
            Invoke("Countdown", 1f);
        }

        void TimeToScore() {

            timer--;
            timerText.text = timer.ToString();
            score++;
        }

        void EndGame()
        {
            trialText.gameObject.SetActive(false);
            TimeToScore();
            if (timer == 0)
            {
                Time.timeScale = 0;
                finalText.gameObject.SetActive(true);
                finalText.text = "Wynik: " + score.ToString();


            }
            if (timer > 0)
            {
                Invoke("EndGame", 0.1f);
            }
        }
    }

}