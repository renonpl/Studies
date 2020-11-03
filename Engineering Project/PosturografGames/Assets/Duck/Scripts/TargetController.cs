using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Duck
{
    public class TargetController : MonoBehaviour
    {
        public GameManger gm;
        public Vector3 target;
        Rigidbody body;
        float speed;
        public float maxSpeed;
        public float fallingSpeed;
        private Animator anim;
        public bool dead;
        int endRange = 5;
        Collider collid;

        private int timerCountdown;
        public bool movingBird = false;
        public bool staticBird = false;

        public int birdStayTimer;

        public AudioClip shootSound;
        public AudioClip duckSound;

        // Start is called before the first frame update
        void Start()
        {
            speed = maxSpeed;
            dead = false;
            anim = GetComponent<Animator>();
            body = GetComponent<Rigidbody>();
            transform.LookAt(target);
            collid = GetComponent<Collider>();
            CheckEnd();
        }

        // Update is called once per frame
        void Update()
        {
            if (!dead) transform.position = transform.position + transform.forward * Time.deltaTime * speed;
            else transform.position = transform.position - new Vector3(0, 1, 0) * Time.deltaTime * speed;
        }

        void CheckEnd()
        {
            if (dead) return;
            if ((transform.position - target).magnitude < endRange)
            {
                if (movingBird == true)
                {
                    Destroy(gameObject);
                    return;
                }
                else
                {
                    speed = 0;
                    transform.LookAt(Camera.main.transform);
                    timerCountdown = birdStayTimer;
                    Invoke("Countdown", 1f);
                }
            }
            Invoke("CheckEnd", 1f);
        }

        public void Die()
        {
            if (dead) return;
            if (staticBird) transform.LookAt(Camera.main.transform);
            MusicManager.Instance.PlayEffect(shootSound);
            Invoke("PlayKwak", 0.5f);
            speed = fallingSpeed;
            anim.SetTrigger("isDead");
            dead = true;
        }

        private void PlayKwak()
        {
            MusicManager.Instance.PlayEffect(duckSound);
        }

        private void OnCollisionEnter(Collision collision)
        {
            if (collision.gameObject.CompareTag("Terrain"))
            {
                speed = 0;
                Destroy(gameObject, 1f);
            }
            if (collision.gameObject.CompareTag("Enemy"))
            {
                Physics.IgnoreCollision(collid, collision.collider);
            }
        }


        void Countdown()
        {
            timerCountdown--;
            if (timerCountdown <= 0)
            {
                FlyAway();
                return;
            }
            Invoke("Countdown", 1f);
        }

        void FlyAway()
        {
            target = gm.upperFly.position;
            transform.LookAt(target);
            speed = maxSpeed;
            Destroy(gameObject, 20f);
        }
    }

}