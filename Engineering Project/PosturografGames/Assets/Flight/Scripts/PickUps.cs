using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Flight
{
    public class PickUps : MonoBehaviour
    {
        public GameManager gm;
        public int points;
        public Camera cam;
        public float speed;
        

        // Start is called before the first frame update
        void Start()
        {
            gm = FindObjectOfType<GameManager>();
            cam = Camera.main;
        }

        // Update is called once per frame
        void Update()
        {
            transform.Translate(-1 * new Vector3(0,0,1) * Time.deltaTime * speed);
            //transform.Rotate(new Vector3(0, 1) * Time.deltaTime * speed);
            if (transform.position.z < cam.transform.position.z - 10)
            {
                Destroy(this.gameObject);
            }
        }

        private void OnTriggerEnter(Collider other)
        {
            if(other.gameObject.CompareTag("Player"))
            {
                gm.AddScore(points);
                Destroy(this.gameObject);
            }
        }
    }
}