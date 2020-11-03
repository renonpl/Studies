using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MusicManager : MonoBehaviour
{
    private static MusicManager _instance;
    public bool primary = false;

    public AudioSource musicSource;
    public AudioSource effectSource;

    public static MusicManager Instance
    {
        get
        {
            if (_instance == null)
            {
                MusicManager[] instances = FindObjectsOfType<MusicManager>();
                _instance = instances[0];
                Debug.Log(instances.Length);
                for (int i = 1; i < instances.Length; i++)
                {
                    Destroy(instances[i].gameObject);
                }
            }
            return _instance;
        }
    }
    
    public void PlayMusic(AudioClip clip)
    {
        musicSource.clip = clip;
        musicSource.Play();
    }

    public void PlayEffect(AudioClip clip)
    {
        effectSource.clip = clip;
        effectSource.Play();
    }

    public void StopMusic()
    {
        musicSource.Stop();
    }

    private void Awake()
    {
        DontDestroyOnLoad(gameObject);
    }

    // Start is called before the first frame update
    void Start()
    {
        MusicManager[] instances = FindObjectsOfType<MusicManager>();
        if (instances.Length == 1)
            instances[0].primary = true;
        else
            for (int i = 0; i < instances.Length; i++)
                if(!instances[i].primary)
                    Destroy(instances[i].gameObject);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
