using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Arkanoid
{
    public class MBBrick : MonoBehaviour
    {
        public GameManager gm;
        public int value;

        private void Start()
        {
            gm = FindObjectOfType<GameManager>();
        }

        void OnCollisionEnter(Collision other)
        {
            if (other.gameObject.GetComponent<BallController>().inplay)
            {
                gm.AddScore(value);
                ParticleSystem exp = Instantiate(gm.scoreParticle, this.transform.position, gm.scoreParticle.transform.rotation);
                exp.Play();
                GameObject ball = Instantiate(gm.playerBall, this.transform.position, gm.playerBall.transform.rotation);
                Destroy(gameObject);
            }
        }
    }
}