using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;
using UnityEngine.UI;

namespace Flight
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
            int points = PlayerPrefs.GetInt("FlightFirst", -1000);
            string player = PlayerPrefs.GetString("FlightFirstP", "...");
            if(score > points)
            {
                first.text = "1." + playerName + " " + score.ToString();
                PlayerPrefs.SetInt("FlightFirst", score);
                PlayerPrefs.SetString("FlightFirstP", playerName);
                score = points;
                playerName = player;
            }
            else
            {
                first.text = "1." + player + " " + points.ToString();
            }
            points = PlayerPrefs.GetInt("FlightSec", -1000);
            player = PlayerPrefs.GetString("FlightSecP", "...");
            if (score > points)
            {
                second.text = "2." + playerName + " " + score.ToString();
                PlayerPrefs.SetInt("FlightSec", score);
                PlayerPrefs.SetString("FlightSecP", playerName);
                score = points;
                playerName = player;
            }
            else
            {
                second.text = "2." + player + " " + points.ToString();
            }
            points = PlayerPrefs.GetInt("FlightThird", -1000);
            player = PlayerPrefs.GetString("FlightThirdP", "...");
            if (score > points)
            {
                third.text = "3." + playerName + " " + score.ToString();
                PlayerPrefs.SetInt("FlightThird", score);
                PlayerPrefs.SetString("FlightThirdP", playerName);
                score = points;
                playerName = player;
            }
            else
            {
                third.text = "3." + player + " " + points.ToString();
            }
            points = PlayerPrefs.GetInt("FlightFourth", -1000);
            player = PlayerPrefs.GetString("FlightFourthP", "...");
            if (score > points)
            {
                fourth.text = "4." + playerName + " " + score.ToString();
                PlayerPrefs.SetInt("FlightFourth", score);
                PlayerPrefs.SetString("FlightFourthP", playerName);
                score = points;
                playerName = player;
            }
            else
            {
                fourth.text = "4." + player + " " + points.ToString();
            }
            points = PlayerPrefs.GetInt("FlightFifth", -1000);
            player = PlayerPrefs.GetString("FlightFifthP", "...");
            if (score > points)
            {
                fifth.text = "5." + playerName + " " + score.ToString();
                PlayerPrefs.SetInt("FlightFifth", score);
                PlayerPrefs.SetString("FlightFithP", playerName);
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
