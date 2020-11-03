using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Globalization;

public class DuckController : MonoBehaviour
{
    public GameObject gameSettings;
    public GameObject settingsScreen;

    public TMPro.TMP_InputField duckMoving;
    public TMPro.TMP_InputField duckStatic;
    public TMPro.TMP_InputField duckMovingSpeed;
    public TMPro.TMP_InputField onTargetTimer;
    public TMPro.TMP_InputField timeCounter;
    public TMPro.TMP_InputField birdStayTimer;
    public TMPro.TMP_InputField spawnRate;
    public TMPro.TMP_InputField playerSpeed;

    private string playerName;

    public void SetParam()
    {
        playerName = SettingsController.StringCutter(settingsScreen.GetComponent<SettingsController>().playername.text);

        duckMoving.text = PlayerPrefs.GetInt(playerName + "dMovingBird", 1).ToString();
        duckStatic.text = PlayerPrefs.GetInt(playerName + "dStaticBird", 1).ToString();
        duckMovingSpeed.text = PlayerPrefs.GetFloat(playerName + "dBirdSpeed", 1.5f).ToString();
        onTargetTimer.text = PlayerPrefs.GetFloat(playerName + "dTargetTimer", 1f).ToString();
        timeCounter.text = PlayerPrefs.GetInt(playerName + "dGameTimer", 120).ToString();
        birdStayTimer.text = PlayerPrefs.GetInt(playerName + "dBirdStay", 10).ToString();
        spawnRate.text = PlayerPrefs.GetFloat(playerName + "dSpawnRate", 2f).ToString();
        playerSpeed.text = PlayerPrefs.GetFloat(playerName + "dPlayerSpeed", 0.01f).ToString();        //0,005
    }

    private void Start()
    {
        System.Threading.Thread.CurrentThread.CurrentCulture = new CultureInfo("en-US");
        SetParam();
    }


    public void ComeBack()
    {

        Debug.Log(playerSpeed.text);
        if (!playerName.Equals("Test"))
        {
            PlayerPrefs.SetInt(playerName + "dMovingBird", int.Parse(duckMoving.text));
            PlayerPrefs.SetInt(playerName + "dStaticBird", int.Parse(duckStatic.text));
            PlayerPrefs.SetFloat(playerName + "dBirdSpeed", float.Parse(duckMovingSpeed.text));
            PlayerPrefs.SetFloat(playerName + "dTargetTimer", float.Parse(onTargetTimer.text));
            PlayerPrefs.SetInt(playerName + "dGameTimer", int.Parse(timeCounter.text));
            PlayerPrefs.SetInt(playerName + "dBirdStay", int.Parse(birdStayTimer.text));
            PlayerPrefs.SetFloat(playerName + "dSpawnRate", float.Parse(spawnRate.text));
            PlayerPrefs.SetFloat(playerName + "dPlayerSpeed", float.Parse(playerSpeed.text));
        }
        Debug.Log(PlayerPrefs.GetFloat(playerName + "dPlayerSpeed", 0));
        PlayerPrefs.Save();
        PlayerPrefs.SetString("Player", playerName);
        gameSettings.gameObject.SetActive(false);
        settingsScreen.gameObject.SetActive(true);
    }
}
