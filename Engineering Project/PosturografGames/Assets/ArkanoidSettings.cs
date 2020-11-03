using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Globalization;

public class ArkanoidSettings : MonoBehaviour
{

    public GameObject gameSettings;
    public GameObject settingsScreen;

    public TMPro.TMP_InputField playerSpeed;
    public TMPro.TMP_InputField ballSpeed;
    public TMPro.TMP_InputField timeCounter;

    private string playerName;

    // Start is called before the first frame update
    public void SetParam()
    {
        playerName = SettingsController.StringCutter(settingsScreen.GetComponent<SettingsController>().playername.text);
       // Debug.Log(playerName);
       // Debug.Log(PlayerPrefs.GetFloat(playerName + "arkBallSpeed", 25426));
        playerSpeed.text = PlayerPrefs.GetFloat(playerName + "arkPlSpeed", 0.0002f).ToString();
        ballSpeed.text = PlayerPrefs.GetFloat(playerName + "arkBallSpeed", 256).ToString();
        timeCounter.text = PlayerPrefs.GetInt(playerName + "arkTimer", 120).ToString();
    }

    public void Start()
    {
        System.Threading.Thread.CurrentThread.CurrentCulture = new CultureInfo("en-US");
        SetParam();
    }

    public void ComeBack()
    {
        if (!playerName.Equals("Test"))
        {
            PlayerPrefs.SetFloat(playerName + "arkPlSpeed", float.Parse(playerSpeed.text));
            PlayerPrefs.SetFloat(playerName + "arkBallSpeed", float.Parse(ballSpeed.text));
            PlayerPrefs.SetInt(playerName + "arkTimer", int.Parse(timeCounter.text));
        }
        PlayerPrefs.Save();
        PlayerPrefs.SetString("Player", playerName);
        gameSettings.gameObject.SetActive(false);
        settingsScreen.gameObject.SetActive(true);
    }
}
