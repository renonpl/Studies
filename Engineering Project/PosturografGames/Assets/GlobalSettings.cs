using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Globalization;

public class GlobalSettings : MonoBehaviour
{
    public GameObject gameSettings;
    public GameObject settingsScreen;

    public TMPro.TMP_InputField arkPlayerSpeed;
    public TMPro.TMP_InputField arkBallSpeed;
    public TMPro.TMP_InputField arkTime;

    public TMPro.TMP_InputField duckPlayerSpeed;
    public TMPro.TMP_InputField duckSpeed;
    public TMPro.TMP_InputField duckTimer;

    public TMPro.TMP_InputField flightSpeed;
    public TMPro.TMP_InputField flightTimer;

    public TMPro.TMP_InputField labSpeed;

    public TMPro.TMP_InputField puzzleSpeed;

    private string playerName;

    // Start is called before the first frame update
    public void SetParam()
    {
        playerName = SettingsController.StringCutter(settingsScreen.GetComponent<SettingsController>().playername.text);
        // Debug.Log(playerName);
        // Debug.Log(PlayerPrefs.GetFloat(playerName + "arkBallSpeed", 25426));
        arkPlayerSpeed.text = PlayerPrefs.GetFloat(playerName + "arkPlSpeed", 0.03f).ToString();
        arkBallSpeed.text = PlayerPrefs.GetFloat(playerName + "arkBallSpeed", 256).ToString();
        arkTime.text = PlayerPrefs.GetInt(playerName + "arkTimer", 120).ToString();

        duckPlayerSpeed.text = PlayerPrefs.GetFloat(playerName + "duckPlSpeed", 0.008f).ToString();
        duckSpeed.text = PlayerPrefs.GetFloat(playerName + "duckSpeed", 1.5f).ToString();
        duckTimer.text = PlayerPrefs.GetInt(playerName + "duckTimer", 120).ToString();

        flightSpeed.text = PlayerPrefs.GetFloat(playerName + "flightSpeed", 0.15f).ToString();
        flightTimer.text = PlayerPrefs.GetInt(playerName + "flightTimer", 120).ToString();

        labSpeed.text = PlayerPrefs.GetFloat(playerName + "labSpeed", 0.02f).ToString();

        puzzleSpeed.text = PlayerPrefs.GetFloat(playerName + "puzzleSpeed", 0.045f).ToString();
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
            PlayerPrefs.SetFloat(playerName + "arkPlSpeed", float.Parse(arkPlayerSpeed.text));
            PlayerPrefs.SetFloat(playerName + "arkBallSpeed", float.Parse(arkBallSpeed.text));
            PlayerPrefs.SetInt(playerName + "arkTimer", int.Parse(arkTime.text));

            PlayerPrefs.SetFloat(playerName + "duckPlSpeed", float.Parse(duckPlayerSpeed.text));
            PlayerPrefs.SetFloat(playerName + "duckSpeed", float.Parse(duckSpeed.text));
            PlayerPrefs.SetInt(playerName + "duckTimer", int.Parse(duckTimer.text));

            PlayerPrefs.SetFloat(playerName + "flightSpeed", float.Parse(flightSpeed.text));
            PlayerPrefs.SetInt(playerName + "flightTimer", int.Parse(flightTimer.text));

            PlayerPrefs.SetFloat(playerName + "labSpeed", float.Parse(labSpeed.text));

            PlayerPrefs.SetFloat(playerName + "puzzleSpeed", float.Parse(puzzleSpeed.text));
        }
        PlayerPrefs.Save();
        PlayerPrefs.SetString("Player", playerName);
        gameSettings.gameObject.SetActive(false);
        settingsScreen.gameObject.SetActive(true);
    }
}
