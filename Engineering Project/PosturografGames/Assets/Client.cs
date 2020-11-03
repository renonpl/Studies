#if (UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN)
using NetMQ;
using NetMQ.Sockets;
#endif
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;
using System.Threading;
using UnityEngine.UI;


    public class Client : MonoBehaviour
    {
        private static Vector2 data;
        public static Vector2 Data { get => data; }
        public Canvas can;
        public GameObject panel;

#if (UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX)

             private RectTransform rtrans;
             private Vector3 offset;

             void Start()
             {
                 panel.gameObject.SetActive(true);
                 rtrans = panel.GetComponent<RectTransform>();
                 offset = panel.transform.position;
                 data = new Vector2(0, 0);
             }

             void Update()
             {
                 if (Input.GetMouseButton(0)) ReadInput();
             }

             void ReadInput()
             {
                 Vector2 mousePos = Input.mousePosition - offset;
                 float currentX = mousePos.x * 200 / rtrans.rect.width; //200, because server operates with ints in range [-100,100]
                 float currentY = mousePos.y * 200 / rtrans.rect.height;
                 if (currentX >= -100 && currentX <= 100 && currentY >= -100 && currentY <= 100)
                 {
                     data = new Vector2((int)currentX, (int)currentY);
                 }
                 //Debug.Log(data.ToString());
             }
#endif
#if (UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN)

    bool _threadRunning;
    Thread _thread;
    private static Client _instance;
    private static SubscriberSocket client;
    public bool primary = false;

    public static Client Instance
    {
        get
        {
            if (_instance == null)
            {
                Client[] instances = FindObjectsOfType<Client>();
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

    private static void StartClient(string server_address = "127.0.0.1", int port = 5556)
    {
        try
        {
            AsyncIO.ForceDotNet.Force();
            client = new NetMQ.Sockets.SubscriberSocket();
            string connect_to = "tcp://" + server_address + ":" + port.ToString();
            client.Connect(connect_to);
            Debug.Log(connect_to);
            client.Subscribe("");
            Debug.Log("Server connected!");

        }
        catch (Exception e)
        {
            //Console.WriteLine(e.ToString());
            Debug.Log(e.ToString());
            Debug.Log("Error, server not connected");
        }
    }

        /*download data as long as possible*/   
    private static void ReadData()
    {
        string reply;
        try
        {

           // Debug.Log("1");
            /*
            Msg m = new Msg();
            m.InitEmpty();
            TimeSpan span = new TimeSpan(1l);
            Debug.Log(client.TryReceiveFrameString(out reply));
            Debug.Log(reply);
            
            TimeSpan span = new TimeSpan(50l);
            reply = client.ReceiveFrameString();
            Debug.Log(reply);
           */
            while (client.TryReceiveFrameString(out reply))
            {
                Debug.Log("re" + reply);
                string[] s = reply.Split(' ');
                int i = 0;
                while (s[i].Length < 1) i++;
                data.x = Convert.ToInt32(s[i]); i++;
                while (s[i].Length < 1) i++;
                data.y = Convert.ToInt32(s[i]);
            }
            //  Debug.Log("2e");
        }
        catch (Exception e)
        {
            Debug.Log(e.ToString());
            Debug.Log("Error przy czytaniu");
        }
    }


    void Start()
    {
        Client[] instances = FindObjectsOfType<Client>();
        if (instances.Length == 1)
        {
            if(!instances[0].primary)
            {
                string server = PlayerPrefs.GetString("Server", "127.0.0.1");
                int port = int.Parse(PlayerPrefs.GetString("Port", "5556"));
                //127.0.0.1
                //192.168.1.106
                StartClient(server, port);
                _thread = new Thread(ThreadedWork);
                _thread.Start();
            }
            instances[0].primary = true;

        }
        else
            for (int i = 0; i < instances.Length; i++)
                if (!instances[i].primary)
                    Destroy(instances[i].gameObject);

        can.gameObject.SetActive(false);
    }


    void ThreadedWork()
    {
        _threadRunning = true;
        bool workDone = false;
        // This pattern lets us interrupt the work at a safe point if neeeded.
        while (_threadRunning && !workDone)
        {

            ReadData();
            Debug.Log(data.x + "  " + data.y);
        }
        _threadRunning = false;
    }
    void OnDisable()
    {
        // If the thread is still running, we should shut it down,
        // otherwise it can prevent the game from exiting correctly.
        if (_threadRunning)
        {
            // This forces the while loop in the ThreadedWork function to abort.
            _threadRunning = false;

            // This waits until the thread exits,
            // ensuring any cleanup we do after this is safe. 
            _thread.Join();
        }
        // Thread is guaranteed no longer running. Do other cleanup tasks.
    }

    private void Awake()
    {
        DontDestroyOnLoad(gameObject);
    }

    private void OnDestroy()
    {
        if (primary)
        {
            client.Dispose();
            NetMQConfig.Cleanup();
        }
    }
#endif
}