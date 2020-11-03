using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Globalization;

public class SettingsController : MonoBehaviour
{
    public TMPro.TMP_InputField playername;
    public TMPro.TMP_InputField serwer;
    public TMPro.TMP_InputField port;
    public GameObject firstMenu;
    public GameObject checks;

    /*
    public TMPro.TMP_InputField playerSpeedLeft;
    public TMPro.TMP_InputField playerSpeedRight;
    public TMPro.TMP_InputField playerSpeedFront;
    public TMPro.TMP_InputField playerSpeedBack;*/


    public void Start()
    {
        System.Threading.Thread.CurrentThread.CurrentCulture = new CultureInfo("en-US");
        playername.text = PlayerPrefs.GetString("Player", "Test");
        serwer.text = PlayerPrefs.GetString("Server", "127.0.0.1");
        port.text = PlayerPrefs.GetString("Port", "5556");
    }

    public void ChosenGame(GameObject go)
    {
        PlayerPrefs.SetString("Player", name);
        PlayerPrefs.Save();

        this.gameObject.SetActive(false);
        go.gameObject.SetActive(true);
        if(go.gameObject.GetComponent<GlobalSettings>())
        {
            go.gameObject.GetComponent<GlobalSettings>().SetParam();
        }
    }

    public static string StringCutter(string s)
    {
        string temp = s;
        if (temp[temp.Length - 1] == 0) temp = temp.Remove(temp.Length - 1);
        return temp;
    }


    public void ComeBack()
    {
        string name = StringCutter(playername.text);
        /*
        if (!name.Equals("Test"))
        {
            PlayerPrefs.SetFloat(name + "SpeedLeft", float.Parse(playerSpeedLeft.text));
            PlayerPrefs.SetFloat(name + "SpeedRight", float.Parse(playerSpeedRight.text));
            PlayerPrefs.SetFloat(name + "SpeedFront", float.Parse(playerSpeedFront.text));
            PlayerPrefs.SetFloat(name + "SpeedBack", float.Parse(playerSpeedBack.text));
        }*/
        PlayerPrefs.SetString("Player", name);
        PlayerPrefs.SetString("Server", serwer.text);
        PlayerPrefs.SetString("Port", port.text);

        PlayerPrefs.SetInt(name + "Checks", checks.GetComponent<ChecksCounter>().Check());
        PlayerPrefs.Save();
        this.gameObject.SetActive(false);
        firstMenu.gameObject.SetActive(true);
    }

}
