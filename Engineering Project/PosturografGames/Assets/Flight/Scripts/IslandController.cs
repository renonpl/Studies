using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Flight
{
    public class IslandController : MonoBehaviour
    {

        public Camera cam;
        public float speed;
        public Spawner sp;
        // Start is called before the first frame update
        void Start()
        {
            cam = Camera.main;
        }

        // Update is called once per frame
        void Update()
        {
            transform.Translate(-1 * transform.forward * Time.deltaTime * speed);
            if (transform.position.z < cam.transform.position.z - 100)
            {
                sp.SpawnIsland();
                Destroy(this.gameObject);
            }
        }

        private void OnCollisionStay(Collision collision)
        {
            if(collision.gameObject.CompareTag("Enemy"))
            {
                Vector3 temp = collision.gameObject.transform.position;
                collision.gameObject.transform.position = temp + new Vector3(0, 1, 0);
            }
        }
    }
}