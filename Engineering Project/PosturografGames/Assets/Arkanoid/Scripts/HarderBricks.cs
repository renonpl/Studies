using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Arkanoid
{
    public class HarderBricks : MonoBehaviour
    {
        public GameManager gm;
        public int value;

        public Material[] materials;
        private int count;
        private Renderer rd;

        private void Start()
        {
            gm = FindObjectOfType<GameManager>();
            rd = GetComponent<Renderer>();
            count = materials.Length - 1;
            rd.material = materials[count];
        }

        void OnCollisionEnter(Collision other)
        {
            if (other.gameObject.GetComponent<BallController>().inplay)
            {
                ParticleSystem exp = Instantiate(gm.scoreParticle, this.transform.position, gm.scoreParticle.transform.rotation);
                exp.Play();
                if (count == 0)
                {
                    gm.AddScore(count);
                    Destroy(gameObject);
                }
                else
                {
                    count--;
                    rd.material = materials[count]; 
                }
            }
        }
    }
}