using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace MainMenu
{
    public class MainMenuManager : MonoBehaviour
    {
        public GameObject gameChooser;
        public GameObject settingsScreen;
        public GameObject firstMenu;

        void Start()
        {
            Time.timeScale = 1f;
            Time.fixedDeltaTime = 0.02f * Time.timeScale;
            MusicManager.Instance.StopMusic();

        }

        public void ChooseGame()
        {
            gameChooser.gameObject.SetActive(true);
            firstMenu.gameObject.SetActive(false);
        }

        public void ComeBack()
        {
            gameChooser.gameObject.SetActive(false);
            firstMenu.gameObject.SetActive(true);
        }

        public void SceneChooser(string sceneName)
        {
            SceneManager.LoadScene(sceneName);
        }

        public void Settings()
        {
            settingsScreen.gameObject.SetActive(true);
            settingsScreen.gameObject.GetComponent<SettingsController>().playername.text = PlayerPrefs.GetString("Player", "Test");
            firstMenu.gameObject.SetActive(false);
        }

        public void ExitGame()
        {
            Application.Quit();
        }
    }

}