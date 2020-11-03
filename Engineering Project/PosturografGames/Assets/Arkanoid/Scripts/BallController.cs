using System.Collections;
using System.Collections.Generic;
using UnityEngine;


namespace Arkanoid
{
    public class BallController : MonoBehaviour
    {
        public float speed;
        private Rigidbody rb;
        private bool coll;
        private float c;

        public Material activeMaterial;
        public Material deactiveMaterial;

        public bool inplay;

        public float velrb;
        private bool check = false;
        public Parameters param;

        public AudioClip bounce;

        private string playerName;


        void Start()
        {

            inplay = true;
            playerName = PlayerPrefs.GetString("Player", "Test");
            speed = PlayerPrefs.GetFloat(playerName + "arkBallSpeed", 256);
            if (param == null)
            {
                //param = FindObjectOfType<Parameters>();
                Invoke("Push", 0.1f);
            }
            rb = GetComponent<Rigidbody>();
            //speed = param.ballSpeed;
            //rb.mass = param.ballMass;
            rb.AddForce(new Vector3(0, 0, -1) * speed);

            // velrb = rb.velocity.magnitude;
        }

        void Push()
        {
            rb.AddForce(new Vector3(0, 0, -1) * speed);
            velrb = rb.velocity.magnitude;

            check = false;
           // Debug.Log(rb.velocity);
        }
           
        // Update is called once per frame
        void Update()
        {
            //  Debug.Log(rb.velocity.magnitude);
            if(check)
            {
                if (rb.velocity.magnitude != velrb)
                {
                    rb.velocity = rb.velocity.normalized * velrb;
                  //  Debug.Log(velrb);
                }
            }
            else
            {
                velrb = rb.velocity.magnitude;
                check = true;
            }

        }

        private void OnCollisionEnter(Collision collision)
        {
            if (collision.gameObject.CompareTag("Player"))
            {
                MusicManager.Instance.PlayEffect(bounce);
                inplay = true;
                GetComponent<Renderer>().material = activeMaterial;
                BounceParam bp = collision.gameObject.GetComponent<BounceParam>();
                if (bp.front)
                {
                    Vector3 bounce = rb.velocity;
                    bounce = bounce.normalized;
                    rb.velocity = new Vector3();
                    rb.AddForce(bounce * speed);
                }
                else
                {
                 //   Debug.Log(bp.angle);
                    Vector3 bounce = new Vector3();
                    switch (bp.angle)
                    {
                        case 60:
                            bounce = new Vector3(1, 0, 2);
                            break;
                        case 45:
                            bounce = new Vector3(1, 0, 1);
                            break;
                        case 30:
                            bounce = new Vector3(2, 0, 1);
                            break;
                    }
                    bounce = bounce.normalized;
                    if (bp.left) bounce.x *= -1;
                    rb.velocity = new Vector3();
                    rb.AddForce(bounce * speed);
                }
                return;
            }
            if (collision.gameObject.CompareTag("Bottom"))
            {
                if(FindObjectsOfType<BallController>().Length != 1)
                {
                    Destroy(this.gameObject);
                    return;
                }

                MusicManager.Instance.PlayEffect(bounce);

                inplay = false;
                GetComponent<Renderer>().material = deactiveMaterial;
            }
            if (collision.gameObject.CompareTag("Brick"))
            {
                MusicManager.Instance.PlayEffect(bounce);

                return;
            }
            MusicManager.Instance.PlayEffect(bounce);

        }


    }
}