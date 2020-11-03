using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ChecksCounter : MonoBehaviour
{
    public static int firstV = 7; // 4,2,1
    public static int secondV = 56; // 32,16,8
    public static int thirdV = 448; // 256,128,64
    public static int firstC = 73; //1,8,64
    public static int secondC = 146; // 2,16,128
    public static int thirdC = 292; // 4,32,256

    public Toggle[] tab;

    //zlica od prawego dolu po wierszach
    public int Check()
    {
        int temp = 0;
        for(int i = tab.Length-1; i >= 0; i--)
        {
            temp <<= 1;
            if (tab[i].isOn) temp++;
        }
        return temp;
    }

}
