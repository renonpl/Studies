using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;
using UnityEngine.UI;

namespace Duck
{
    public class EndGame : MonoBehaviour
    {
        public TextMeshProUGUI first;
        public TextMeshProUGUI second;
        public TextMeshProUGUI third;
        public TextMeshProUGUI fourth;
        public TextMeshProUGUI fifth;
        public TextMeshProUGUI yourScore;

        public GameObject movingBlocks;
        public float speed;
        private float offset;
        // Start is called before the first frame update
        void Start()
        {
            offset = movingBlocks.transform.localPosition.y;
        }

        // Update is called once per frame
        void Update()
        {
            if (movingBlocks.transform.localPosition.y - offset > 700) speed = 0;
            movingBlocks.transform.Translate(Vector3.up * speed * Time.unscaledDeltaTime);
        }

        public void End(int score, string playerName)
        {
            this.gameObject.SetActive(true);
            yourScore.text = "Twój Wynik: " + score.ToString();
            int points = PlayerPrefs.GetInt("DuckFirst", 0);
            string player = PlayerPrefs.GetString("DuckFirstP", "...");
            if(score > points)
            {
                first.text = "1." + playerName + " " + score.ToString();
                PlayerPrefs.SetInt("DuckFirst", score);
                PlayerPrefs.SetString("DuckFirstP", playerName);
                score = points;
                playerName = player;
            }
            else
            {
                first.text = "1." + player + " " + points.ToString();
            }
            points = PlayerPrefs.GetInt("DuckSec", 0);
            player = PlayerPrefs.GetString("DuckSecP", "...");
            if (score > points)
            {
                second.text = "2." + playerName + " " + score.ToString();
                PlayerPrefs.SetInt("DuckSec", score);
                PlayerPrefs.SetString("DuckSecP", playerName);
                score = points;
                playerName = player;
            }
            else
            {
                second.text = "2." + player + " " + points.ToString();
            }
            points = PlayerPrefs.GetInt("DuckThird", 0);
            player = PlayerPrefs.GetString("DuckThirdP", "...");
            if (score > points)
            {
                third.text = "3." + playerName + " " + score.ToString();
                PlayerPrefs.SetInt("DuckThird", score);
                PlayerPrefs.SetString("DuckThirdP", playerName);
                score = points;
                playerName = player;
            }
            else
            {
                third.text = "3." + player + " " + points.ToString();
            }
            points = PlayerPrefs.GetInt("DuckFourth", 0);
            player = PlayerPrefs.GetString("DuckFourthP", "...");
            if (score > points)
            {
                fourth.text = "4." + playerName + " " + score.ToString();
                PlayerPrefs.SetInt("DuckFourth", score);
                PlayerPrefs.SetString("DuckFourthP", playerName);
                score = points;
                playerName = player;
            }
            else
            {
                fourth.text = "4." + player + " " + points.ToString();
            }
            points = PlayerPrefs.GetInt("DuckFifth", 0);
            player = PlayerPrefs.GetString("DuckFifthP", "...");
            if (score > points)
            {
                fifth.text = "5." + playerName + " " + score.ToString();
                PlayerPrefs.SetInt("DuckFifth", score);
                PlayerPrefs.SetString("DuckFithP", playerName);
                score = points;
                playerName = player;
            }
            else
            {
                fifth.text = "5." + player + " " + points.ToString();
            }
            PlayerPrefs.Save();
        }
    }
}
