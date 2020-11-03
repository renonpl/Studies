using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;
using UnityEngine.UI;

namespace Arkanoid
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
            int points = PlayerPrefs.GetInt("ArkFirst", 0);
            string player = PlayerPrefs.GetString("ArkFirstP", "...");
            if(score > points)
            {
                first.text = "1." + playerName + " " + score.ToString();
                PlayerPrefs.SetInt("ArkFirst", score);
                PlayerPrefs.SetString("ArkFirstP", playerName);
                score = points;
                playerName = player;
            }
            else
            {
                first.text = "1." + player + " " + points.ToString();
            }
            points = PlayerPrefs.GetInt("ArkSec", 0);
            player = PlayerPrefs.GetString("ArkSecP", "...");
            if (score > points)
            {
                second.text = "2." + playerName + " " + score.ToString();
                PlayerPrefs.SetInt("ArkSec", score);
                PlayerPrefs.SetString("ArkSecP", playerName);
                score = points;
                playerName = player;
            }
            else
            {
                second.text = "2." + player + " " + points.ToString();
            }
            points = PlayerPrefs.GetInt("ArkThird", 0);
            player = PlayerPrefs.GetString("ArkThirdP", "...");
            if (score > points)
            {
                third.text = "3." + playerName + " " + score.ToString();
                PlayerPrefs.SetInt("ArkThird", score);
                PlayerPrefs.SetString("ArkThirdP", playerName);
                score = points;
                playerName = player;
            }
            else
            {
                third.text = "3." + player + " " + points.ToString();
            }
            points = PlayerPrefs.GetInt("ArkFourth", 0);
            player = PlayerPrefs.GetString("ArkFourthP", "...");
            if (score > points)
            {
                fourth.text = "4." + playerName + " " + score.ToString();
                PlayerPrefs.SetInt("ArkFourth", score);
                PlayerPrefs.SetString("ArkFourthP", playerName);
                score = points;
                playerName = player;
            }
            else
            {
                fourth.text = "4." + player + " " + points.ToString();
            }
            points = PlayerPrefs.GetInt("ArkFifth", 0);
            player = PlayerPrefs.GetString("ArkFifthP", "...");
            if (score > points)
            {
                fifth.text = "5." + playerName + " " + score.ToString();
                PlayerPrefs.SetInt("ArkFifth", score);
                PlayerPrefs.SetString("ArkFithP", playerName);
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
