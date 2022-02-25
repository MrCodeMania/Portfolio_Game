using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Xml;
using System;

public class MainMove : MonoBehaviour {
    public Camera Main;
    float MoveSpeed;
    bool rbool;
    // Use this for initialization
	void Start ()
    {
        rbool = false;
        MoveSpeed = 0.05f;
        GameObject.Find("Canvas2").GetComponent<Canvas>().enabled = false;
    }
	
	// Update is called once per frame
	void Update () {
        this.transform.position = new Vector3(this.transform.position.x + (MoveSpeed * 9), this.transform.position.y, this.transform.position.z);

        if (this.transform.position.x > 1000)
            this.transform.position = new Vector3(-750, this.transform.position.y, this.transform.position.z);

        if (Main.transform.position.x > 250)
            rbool = true;
        else if (Main.transform.position.x < 41)
            rbool = false;

        if(!rbool)
            Main.transform.position = new Vector3(Main.transform.position.x + MoveSpeed / 2, Main.transform.position.y, Main.transform.position.z);
        else
            Main.transform.position = new Vector3(Main.transform.position.x - MoveSpeed / 2, Main.transform.position.y, Main.transform.position.z);
    }

    public void StartButton()
    {
        GameObject.Find("Canvas2").GetComponent<Canvas>().enabled = true;
    }

    public void CancelButton()
    {
        GameObject.Find("Canvas2").GetComponent<Canvas>().enabled = false;
    }

    public void GameStart()
    {
        XmlDocument xmlDoc = new XmlDocument();
        TextAsset textAsset = (TextAsset)Resources.Load("Save");
        xmlDoc.LoadXml(textAsset.text);

        XmlNodeList Nodes = xmlDoc.SelectNodes("Saved/Location");

        foreach (XmlNode node in Nodes)
        {
            node.SelectSingleNode("Scene").InnerText = "";
            node.SelectSingleNode("x").InnerText = "";
            node.SelectSingleNode("y").InnerText = "";
            node.SelectSingleNode("z").InnerText = "";
        }

        XmlNodeList Nodes2 = xmlDoc.SelectNodes("Saved/Inventory/Stat/Child");

        foreach (XmlNode node2 in Nodes2)
        {
            node2.SelectSingleNode("NAME").InnerText = "0";
            node2.SelectSingleNode("LEVEL").InnerText = "0";
            node2.SelectSingleNode("EXP").InnerText = "0";
            node2.SelectSingleNode("MAXHP").InnerText = "0";
            node2.SelectSingleNode("MAXSP").InnerText = "0";
            node2.SelectSingleNode("ENHANCE").InnerText = "0";
            node2.SelectSingleNode("AP").InnerText = "0";
            node2.SelectSingleNode("DP").InnerText = "0";
            node2.SelectSingleNode("STEP").InnerText = "0";
        }

        XmlNodeList Nodes3 = xmlDoc.SelectNodes("Saved/Combi/First");
        XmlNodeList Nodes4 = xmlDoc.SelectNodes("Saved/Combi/Second");
        XmlNodeList Nodes5 = xmlDoc.SelectNodes("Saved/Combi/Third");
        XmlNodeList Nodes6 = xmlDoc.SelectNodes("Saved/Combi/Fourth");

        foreach (XmlNode node2 in Nodes3)
        {
            node2.SelectSingleNode("LEVEL").InnerText = "1";
            node2.SelectSingleNode("EXP").InnerText = "0";
            node2.SelectSingleNode("MAXHP").InnerText = "30";
            node2.SelectSingleNode("MAXSP").InnerText = "10";
            node2.SelectSingleNode("ENHANCE").InnerText = "0";
            node2.SelectSingleNode("AP").InnerText = "5";
            node2.SelectSingleNode("DP").InnerText = "5";
            node2.SelectSingleNode("STEP").InnerText = "10";
        }

        foreach (XmlNode node2 in Nodes4)
        {
            node2.SelectSingleNode("ID").InnerText = "0";
            node2.SelectSingleNode("NAME").InnerText = "0";
            node2.SelectSingleNode("LEVEL").InnerText = "0";
            node2.SelectSingleNode("EXP").InnerText = "0";
            node2.SelectSingleNode("MAXHP").InnerText = "0";
            node2.SelectSingleNode("MAXSP").InnerText = "0";
            node2.SelectSingleNode("ENHANCE").InnerText = "0";
            node2.SelectSingleNode("AP").InnerText = "0";
            node2.SelectSingleNode("DP").InnerText = "0";
            node2.SelectSingleNode("STEP").InnerText = "0";
        }

        foreach (XmlNode node2 in Nodes5)
        {
            node2.SelectSingleNode("ID").InnerText = "0";
            node2.SelectSingleNode("NAME").InnerText = "0";
            node2.SelectSingleNode("LEVEL").InnerText = "0";
            node2.SelectSingleNode("EXP").InnerText = "0";
            node2.SelectSingleNode("MAXHP").InnerText = "0";
            node2.SelectSingleNode("MAXSP").InnerText = "0";
            node2.SelectSingleNode("ENHANCE").InnerText = "0";
            node2.SelectSingleNode("AP").InnerText = "0";
            node2.SelectSingleNode("DP").InnerText = "0";
            node2.SelectSingleNode("STEP").InnerText = "0";
        }

        foreach (XmlNode node2 in Nodes6)
        {
            node2.SelectSingleNode("ID").InnerText = "0";
            node2.SelectSingleNode("NAME").InnerText = "0";
            node2.SelectSingleNode("LEVEL").InnerText = "0";
            node2.SelectSingleNode("EXP").InnerText = "0";
            node2.SelectSingleNode("MAXHP").InnerText = "0";
            node2.SelectSingleNode("MAXSP").InnerText = "0";
            node2.SelectSingleNode("ENHANCE").InnerText = "0";
            node2.SelectSingleNode("AP").InnerText = "0";
            node2.SelectSingleNode("DP").InnerText = "0";
            node2.SelectSingleNode("STEP").InnerText = "0";
        }

        xmlDoc.Save("D:/Unity/Combination/Assets/Assets/Combination/Combination/Resources/Save.xml");


        XmlNodeList Nodes7 = xmlDoc.SelectNodes("Saved/Child");

        int i = 0;
        foreach (XmlNode node2 in Nodes7)
        {
            i++;
            node2.SelectSingleNode("x" + i.ToString()).InnerText = "F";
        }

        xmlDoc.Save("D:/Unity/Combination/Assets/Assets/Combination/Combination/Resources/Save.xml");
        xmlDoc = null;
        
        LoadingSceneManager.LoadScene("CinemaScene");
    }

    public void GameLoad()
    {
        XmlDocument xmlDoc = new XmlDocument();
        TextAsset textAsset = (TextAsset)Resources.Load("Save");
        xmlDoc.LoadXml(textAsset.text);
        
        XmlDocument xmlDoc2 = new XmlDocument();
        TextAsset textAsset2 = (TextAsset)Resources.Load("Inventory");
        xmlDoc2.LoadXml(textAsset2.text);

        XmlNodeList Nodes2 = xmlDoc.SelectNodes("Saved/Inventory/Stat/Child");

        XmlNodeList nodes3 = xmlDoc2.SelectNodes("Stat/Child");


        foreach (XmlNode node2 in nodes3)
        {
            foreach (XmlNode node3 in Nodes2)
            {
                if (node2.SelectSingleNode("ID").InnerText == node3.SelectSingleNode("ID").InnerText)
                {
                    node2.SelectSingleNode("ID").InnerText = node3.SelectSingleNode("ID").InnerText;
                    node2.SelectSingleNode("NAME").InnerText = node3.SelectSingleNode("NAME").InnerText;
                    node2.SelectSingleNode("LEVEL").InnerText = node3.SelectSingleNode("LEVEL").InnerText;
                    node2.SelectSingleNode("EXP").InnerText = node3.SelectSingleNode("EXP").InnerText;
                    node2.SelectSingleNode("MAXHP").InnerText = node3.SelectSingleNode("MAXHP").InnerText;
                    node2.SelectSingleNode("MAXSP").InnerText = node3.SelectSingleNode("MAXSP").InnerText;
                    node2.SelectSingleNode("ENHANCE").InnerText = node3.SelectSingleNode("ENHANCE").InnerText;
                    node2.SelectSingleNode("AP").InnerText = node3.SelectSingleNode("AP").InnerText;
                    node2.SelectSingleNode("DP").InnerText = node3.SelectSingleNode("DP").InnerText;
                    node2.SelectSingleNode("STEP").InnerText = node3.SelectSingleNode("STEP").InnerText;
                    break;
                }
            }
        }
        xmlDoc2.Save("D:/Unity/Combination/Assets/Assets/Combination/Combination/Resources/Inventory.xml");
        xmlDoc2 = null;
        
        XmlDocument xmlDoc3 = new XmlDocument();
        TextAsset textAsset3 = (TextAsset)Resources.Load("Combi");
        xmlDoc3.LoadXml(textAsset3.text);

        XmlNodeList Nodes3 = xmlDoc.SelectNodes("Saved/Combi/First");
        XmlNodeList Nodes4 = xmlDoc.SelectNodes("Saved/Combi/Second");
        XmlNodeList Nodes5 = xmlDoc.SelectNodes("Saved/Combi/Third");
        XmlNodeList Nodes6 = xmlDoc.SelectNodes("Saved/Combi/Fourth");

        XmlNodeList nodes4 = xmlDoc3.SelectNodes("Combi/First");
        XmlNodeList nodes5 = xmlDoc3.SelectNodes("Combi/Second");
        XmlNodeList nodes6 = xmlDoc3.SelectNodes("Combi/Third");
        XmlNodeList nodes7 = xmlDoc3.SelectNodes("Combi/Fourth");

        foreach (XmlNode node2 in nodes4)
        {
            foreach (XmlNode node3 in Nodes3)
            {
                node2.SelectSingleNode("ID").InnerText = node3.SelectSingleNode("ID").InnerText;
                node2.SelectSingleNode("NAME").InnerText = node3.SelectSingleNode("NAME").InnerText;
                node2.SelectSingleNode("LEVEL").InnerText = node3.SelectSingleNode("LEVEL").InnerText;
                node2.SelectSingleNode("EXP").InnerText = node3.SelectSingleNode("EXP").InnerText;
                node2.SelectSingleNode("MAXHP").InnerText = node3.SelectSingleNode("MAXHP").InnerText;
                node2.SelectSingleNode("MAXSP").InnerText = node3.SelectSingleNode("MAXSP").InnerText;
                node2.SelectSingleNode("ENHANCE").InnerText = node3.SelectSingleNode("ENHANCE").InnerText;
                node2.SelectSingleNode("AP").InnerText = node3.SelectSingleNode("AP").InnerText;
                node2.SelectSingleNode("DP").InnerText = node3.SelectSingleNode("DP").InnerText;
                node2.SelectSingleNode("STEP").InnerText = node3.SelectSingleNode("STEP").InnerText;
                break;
            }
        }

        foreach (XmlNode node2 in nodes5)
        {
            foreach (XmlNode node3 in Nodes4)
            {
                node2.SelectSingleNode("ID").InnerText = node3.SelectSingleNode("ID").InnerText;
                node2.SelectSingleNode("NAME").InnerText = node3.SelectSingleNode("NAME").InnerText;
                node2.SelectSingleNode("LEVEL").InnerText = node3.SelectSingleNode("LEVEL").InnerText;
                node2.SelectSingleNode("EXP").InnerText = node3.SelectSingleNode("EXP").InnerText;
                node2.SelectSingleNode("MAXHP").InnerText = node3.SelectSingleNode("MAXHP").InnerText;
                node2.SelectSingleNode("MAXSP").InnerText = node3.SelectSingleNode("MAXSP").InnerText;
                node2.SelectSingleNode("ENHANCE").InnerText = node3.SelectSingleNode("ENHANCE").InnerText;
                node2.SelectSingleNode("AP").InnerText = node3.SelectSingleNode("AP").InnerText;
                node2.SelectSingleNode("DP").InnerText = node3.SelectSingleNode("DP").InnerText;
                node2.SelectSingleNode("STEP").InnerText = node3.SelectSingleNode("STEP").InnerText;
                break;
            }
        }

        foreach (XmlNode node2 in nodes6)
        {
            foreach (XmlNode node3 in Nodes5)
            {
                node2.SelectSingleNode("ID").InnerText = node3.SelectSingleNode("ID").InnerText;
                node2.SelectSingleNode("NAME").InnerText = node3.SelectSingleNode("NAME").InnerText;
                node2.SelectSingleNode("LEVEL").InnerText = node3.SelectSingleNode("LEVEL").InnerText;
                node2.SelectSingleNode("EXP").InnerText = node3.SelectSingleNode("EXP").InnerText;
                node2.SelectSingleNode("MAXHP").InnerText = node3.SelectSingleNode("MAXHP").InnerText;
                node2.SelectSingleNode("MAXSP").InnerText = node3.SelectSingleNode("MAXSP").InnerText;
                node2.SelectSingleNode("ENHANCE").InnerText = node3.SelectSingleNode("ENHANCE").InnerText;
                node2.SelectSingleNode("AP").InnerText = node3.SelectSingleNode("AP").InnerText;
                node2.SelectSingleNode("DP").InnerText = node3.SelectSingleNode("DP").InnerText;
                node2.SelectSingleNode("STEP").InnerText = node3.SelectSingleNode("STEP").InnerText;
                break;
            }
        }

        foreach (XmlNode node2 in nodes7)
        {
            foreach (XmlNode node3 in Nodes6)
            {
                node2.SelectSingleNode("ID").InnerText = node3.SelectSingleNode("ID").InnerText;
                node2.SelectSingleNode("NAME").InnerText = node3.SelectSingleNode("NAME").InnerText;
                node2.SelectSingleNode("LEVEL").InnerText = node3.SelectSingleNode("LEVEL").InnerText;
                node2.SelectSingleNode("EXP").InnerText = node3.SelectSingleNode("EXP").InnerText;
                node2.SelectSingleNode("MAXHP").InnerText = node3.SelectSingleNode("MAXHP").InnerText;
                node2.SelectSingleNode("MAXSP").InnerText = node3.SelectSingleNode("MAXSP").InnerText;
                node2.SelectSingleNode("ENHANCE").InnerText = node3.SelectSingleNode("ENHANCE").InnerText;
                node2.SelectSingleNode("AP").InnerText = node3.SelectSingleNode("AP").InnerText;
                node2.SelectSingleNode("DP").InnerText = node3.SelectSingleNode("DP").InnerText;
                node2.SelectSingleNode("STEP").InnerText = node3.SelectSingleNode("STEP").InnerText;
                break;
            }
        }

        xmlDoc3.Save("D:/Unity/Combination/Assets/Assets/Combination/Combination/Resources/Combi.xml");
        xmlDoc3 = null;

        XmlDocument xmlDoc4 = new XmlDocument();
        TextAsset textAsset4 = (TextAsset)Resources.Load("Dictionary");
        xmlDoc4.LoadXml(textAsset4.text);

        XmlNodeList Nodes7 = xmlDoc.SelectNodes("Saved/Child");
        XmlNodeList nodes8 = xmlDoc4.SelectNodes("Child");

        int i = 0;
        foreach (XmlNode node2 in nodes8)
        {
            i++;
            foreach (XmlNode node3 in Nodes7)
            {
                node2.SelectSingleNode("x" + i.ToString()).InnerText = node3.SelectSingleNode("x" + i.ToString()).InnerText;
                break;
            }
        }

        xmlDoc4.Save("D:/Unity/Combination/Assets/Assets/Combination/Combination/Resources/Dictionary.xml");
        xmlDoc4 = null;
        xmlDoc = null;
        LoadingSceneManager.LoadScene("StartVillageScene");
    }

    public void GameExit()
    {
        Debug.Log("종료");
        Application.Quit();
    }
}
