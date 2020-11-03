using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Globalization;

public class PuzzleSettings : MonoBehaviour
{

    public GameObject gameSettings;
    public GameObject settingsScreen;

    public TMPro.TMP_InputField playerSpeedX;
    public TMPro.TMP_InputField playerSpeedY;
    public TMPro.TMP_InputField putTimer;
    public TMPro.TMP_InputField catchTimer;


    private string playerName;

    // Start is called before the first frame update
    public void Start()
    {
        System.Threading.Thread.CurrentThread.CurrentCulture = new CultureInfo("en-US");
        SetParam();
    }

    public void ComeBack()
    {
        if (!playerName.Equals("Test"))
        {
            PlayerPrefs.SetFloat(playerName + "PuzSpeedX", float.Parse(playerSpeedX.text));
            PlayerPrefs.SetFloat(playerName + "PuzSpeedY", float.Parse(playerSpeedY.text));
            PlayerPrefs.SetFloat(playerName + "PuzPutTimer", float.Parse(putTimer.text));
            PlayerPrefs.SetFloat(playerName + "PuzCatchTimer", float.Parse(catchTimer.text));
        }
        PlayerPrefs.Save();
        PlayerPrefs.SetString("Player", playerName);
        gameSettings.gameObject.SetActive(false);
        settingsScreen.gameObject.SetActive(true);
    }

    public void SetParam()
    {
        playerName = SettingsController.StringCutter(settingsScreen.GetComponent<SettingsController>().playername.text);
        playerSpeedX.text = PlayerPrefs.GetFloat(playerName + "PuzSpeedX", 0.17f).ToString();
        playerSpeedY.text = PlayerPrefs.GetFloat(playerName + "PuzSpeedY", 0.15f).ToString();
        putTimer.text = PlayerPrefs.GetFloat(playerName + "PuzPutTimer", 1.5f).ToString();
        catchTimer.text = PlayerPrefs.GetFloat(playerName + "PuzCatchTimer", 1.5f).ToString();
    }

}
