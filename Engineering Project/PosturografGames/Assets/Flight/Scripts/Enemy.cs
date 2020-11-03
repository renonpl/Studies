using System.Collections;
using System.Collections.Generic;
using UnityEngine;


namespace Flight
{
    public class Enemy : MonoBehaviour
    {
        public GameManager gm;
        public int points;
        public Camera cam;
        public float speed;

        public GameObject[] raycastPoints;
        public ParticleSystem bumParticle;
        public AudioClip bum;

        // Start is called before the first frame update
        void Start()
        {
            gm = FindObjectOfType<GameManager>();
            cam = Camera.main;
        }

        // Update is called once per frame
        void Update()
        {
            transform.Translate(-1 * transform.forward * Time.deltaTime * speed);
            if (transform.position.z < cam.transform.position.z - 10)
            {
                Destroy(this.gameObject);
            }
        }

        private void OnTriggerEnter(Collider other)
        {
            if (other.gameObject.CompareTag("Player"))
            {
                ParticleSystem exp = Instantiate(bumParticle, this.transform.position, bumParticle.transform.rotation);
                exp.Play();
                MusicManager.Instance.PlayEffect(bum);

                gm.AddScore(-1*points);
                Destroy(this.gameObject);
            }
        }
    }
}
