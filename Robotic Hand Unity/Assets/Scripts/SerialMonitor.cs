
using UnityEngine;
using UnityEngine.UI;
using TMPro;

using System;
using System.IO.Ports;
using System.Collections.Generic;
using ArduinoBluetoothAPI;

public class SerialMonitor : MonoBehaviour
{
    [Header("DebugMode")]
    [SerializeField] bool debugMode;
    [Header("Bluetooth Mode")]
    [SerializeField] bool bluetoothMode;
    [Header("Dropdown")]
    [SerializeField] TMP_Dropdown portsDropdown;
    [Header("Sliders")]
    [SerializeField] Slider finger1;
    [SerializeField] Slider finger2, finger3, finger4, thumb;
    [SerializeField] Vector2Int[] ranges = new Vector2Int[5];
    Dictionary<Slider, char> sliderName = new Dictionary<Slider, char>();
    Dictionary<char, Slider> sliders = new Dictionary<char, Slider>();
    [Header("Select Buttons")]
    [SerializeField] Button finger1select;
    [SerializeField] Button finger2select, finger3select, finger4select, thumbselect;
    Dictionary<char, Button> buttons = new Dictionary<char, Button>();
    [Header("Config Buttons")]
    [SerializeField] Button setLowEndstop;
    [SerializeField] Button setHighEndstop, readCurrentPostion, connect, refresh, reset;
    [SerializeField] Button plusMaxPulse, minusMaxPulse, plusMinPulse, minusMinPulse;

    //Ports
    List<string> possiblePorts = new List<string>();
    SerialPort port;

    [Header("Connect Button Colours")] 
    [SerializeField] Color32 disconnectedColour;
    [SerializeField] Color32 connectedColour;
    [Header("Select Button Colours")]
    [SerializeField] Color32 selectColour;
    [SerializeField] Color32 normalColour;

    char selectedFinger = 'N';
    bool portOpen;

    bluetoothManager bluetoothManager;

    private void Awake()
    {
        bluetoothManager = GetComponent<bluetoothManager>(); ;
    }
    // Start is called before the first frame update
    void Start()
    {
        //Set up dictionary
        buttons.Add('A', finger1select);
        buttons.Add('B', finger2select);
        buttons.Add('C', finger3select);
        buttons.Add('D', finger4select);
        buttons.Add('E', thumbselect);

        //Set up translation dictionary
        sliderName.Add(finger1, 'A');
        sliderName.Add(finger2, 'B');
        sliderName.Add(finger3, 'C');
        sliderName.Add(finger4, 'D');
        sliderName.Add(thumb, 'E');

        //Set up slider dictionary
        sliders.Add('A', finger1);
        sliders.Add('B', finger2);
        sliders.Add('C', finger3);
        sliders.Add('D', finger4);
        sliders.Add('E', thumb);

        //Add methods to buttons
        finger1select.onClick.AddListener(delegate { SelectFinger('A'); });
        finger2select.onClick.AddListener(delegate { SelectFinger('B'); });
        finger3select.onClick.AddListener(delegate { SelectFinger('C'); });
        finger4select.onClick.AddListener(delegate { SelectFinger('D'); });
        thumbselect.onClick.AddListener(delegate { SelectFinger('E'); });

        finger1.onValueChanged.AddListener(delegate { AdjustSlider(finger1); });
        finger2.onValueChanged.AddListener(delegate { AdjustSlider(finger2); });
        finger3.onValueChanged.AddListener(delegate { AdjustSlider(finger3); });
        finger4.onValueChanged.AddListener(delegate { AdjustSlider(finger4); });
        thumb.onValueChanged.AddListener(delegate { AdjustSlider(thumb); });

        refresh.onClick.AddListener(delegate { CheckPorts(false); });
        connect.onClick.AddListener(delegate { ConnectToArdinuo(); });
        readCurrentPostion.onClick.AddListener(delegate {  });
        setHighEndstop.onClick.AddListener(delegate { SetHigh();  });
        setLowEndstop.onClick.AddListener(delegate { SetLow(); });
        reset.onClick.AddListener(delegate { ResetRanges(); });
        plusMaxPulse.onClick.AddListener(delegate { SendValue('I');  });
        minusMaxPulse.onClick.AddListener(delegate { SendValue('J'); });
        plusMinPulse.onClick.AddListener(delegate { SendValue('K'); });
        minusMinPulse.onClick.AddListener(delegate { SendValue('L'); });

        //Initialization
        port = new SerialPort("", 115200);
        CheckPorts(true);
        

        //Init connect button
        portOpen = false;
        connect.GetComponent<Image>().color = disconnectedColour;
        connect.transform.Find("Text (TMP)").GetComponent<TextMeshProUGUI>().text = "Connect";

        if(!debugMode)
        {
            SetInteractable(false);
        }
        

        
    }

    private void Update()
    {
        //Check if port is open
        if (portOpen)
        {
            if (!port.IsOpen && !debugMode)
            {
                connect.GetComponent<Image>().color = disconnectedColour;
                connect.transform.Find("Text (TMP)").GetComponent<TextMeshProUGUI>().text = "Connect";
                portOpen = false;
            }
        }
    }

    void CheckPorts(bool firstTime)
    {
        if (bluetoothMode && !firstTime)
        {
            bluetoothManager.Scan();
            refresh.transform.Find("Text (TMP)").GetComponent<TextMeshProUGUI>().text = "Scanning..";
        }
        else
        {
            string[] allPorts = SerialPort.GetPortNames();
            possiblePorts = new List<string>();

            foreach (string port in allPorts)
            {
                if (port.Contains("usb"))
                {
                    possiblePorts.Add(port);
                    print(port);
                }
            }

            portsDropdown.options.Clear();

            foreach (string port in possiblePorts)
            {
                portsDropdown.interactable = true;
                portsDropdown.options.Add(new TMP_Dropdown.OptionData { text = port });
                portsDropdown.value = 1;
            }

            if (possiblePorts.Count == 0)
            {
                portsDropdown.interactable = false;
                portsDropdown.options.Add(new TMP_Dropdown.OptionData { text = "No Ports" });
                portsDropdown.value = 1;

            }
        }
    }

    public void SetPortOptions(LinkedList<BluetoothDevice> devices)
    {
        LinkedListNode<BluetoothDevice> node = devices.First;
        possiblePorts = new List<string>();
        portsDropdown.options.Clear();

        while(node != null)
        { 
            portsDropdown.interactable = true;
            portsDropdown.options.Add(new TMP_Dropdown.OptionData { text = node.Value.DeviceName });
            portsDropdown.value = 1;
            possiblePorts.Add(node.Value.DeviceName);
            node = node.Next;
        }

        if (possiblePorts.Count == 0)
        {
            portsDropdown.interactable = false;
            portsDropdown.options.Add(new TMP_Dropdown.OptionData { text = "No Ports" });
            portsDropdown.value = 1;

        }

        refresh.transform.Find("Text (TMP)").GetComponent<TextMeshProUGUI>().text = "Scan";
    }

    void SelectFinger(char finger)
    {
        if(selectedFinger != finger)
        {
            Debug.Log(finger);
            if(selectedFinger != 'N')
                buttons[selectedFinger].GetComponent<Image>().color = normalColour;
            buttons[finger].GetComponent<Image>().color = selectColour;
            selectedFinger = finger;
            SendValue(finger);
        }
        
    }

    void AdjustSlider(Slider slider)
    {
        Vector2Int range = ranges[(byte)sliderName[slider] - 65];
        if (slider.value < range.x)
        {
            slider.value = range.x;
        }
        else if(slider.value > range.y)
        {
            slider.value = range.y;
        }
        SelectFinger(sliderName[slider]);
        SendValue((short)Math.Round(slider.value));
    }

    void ConnectToArdinuo()
    {
        if (!debugMode)
        {
            if (bluetoothMode)
            {
                bluetoothManager.ConnectToBluetooth(portsDropdown.options[portsDropdown.value].text);
            }
            else
            {
                if (!portOpen)
                {
                    try
                    {
                        port = new SerialPort(portsDropdown.options[portsDropdown.value].text, 115200);//Set your board COM
                        port.Open();
                        if (port.IsOpen)
                        {
                            portOpen = true;
                            connect.GetComponent<Image>().color = connectedColour;
                            connect.transform.Find("Text (TMP)").GetComponent<TextMeshProUGUI>().text = "Disconnect";
                            SetInteractable(true);
                        }
                        else
                        {
                            portOpen = false;
                            connect.GetComponent<Image>().color = disconnectedColour;
                            connect.transform.Find("Text (TMP)").GetComponent<TextMeshProUGUI>().text = "Connect";
                            SetInteractable(false);
                        }

                    }
                    catch
                    {
                        portOpen = false;
                        connect.GetComponent<Image>().color = disconnectedColour;
                        connect.transform.Find("Text (TMP)").GetComponent<TextMeshProUGUI>().text = "Connect";
                        SetInteractable(false);
                    }
                }
                else
                {
                    port.Close();
                    portOpen = false;
                    connect.GetComponent<Image>().color = disconnectedColour;
                    connect.transform.Find("Text (TMP)").GetComponent<TextMeshProUGUI>().text = "Connect";
                    SetInteractable(false);
                }
            }
        }
        else
        {
            if (!portOpen)
            {

                portOpen = true;
                connect.GetComponent<Image>().color = connectedColour;
                connect.transform.Find("Text (TMP)").GetComponent<TextMeshProUGUI>().text = "Disconnect";
            }
            else
            {
                portOpen = false;
                connect.GetComponent<Image>().color = disconnectedColour;
                connect.transform.Find("Text (TMP)").GetComponent<TextMeshProUGUI>().text = "Connect";
            }

        }
    }

    public void OnBTConnection()
    {
        portOpen = true;
        connect.GetComponent<Image>().color = connectedColour;
        connect.transform.Find("Text (TMP)").GetComponent<TextMeshProUGUI>().text = "Disconnect";
        SetInteractable(true);
    }

    public void OnBTFailedConnection()
    {
        portOpen = false;
        connect.GetComponent<Image>().color = disconnectedColour;
        connect.transform.Find("Text (TMP)").GetComponent<TextMeshProUGUI>().text = "Connect";
        SetInteractable(false);

        portsDropdown.options.Clear();
        portsDropdown.interactable = false;
        portsDropdown.options.Add(new TMP_Dropdown.OptionData { text = "Connection Failed!!!" });
        portsDropdown.value = 1;

        CheckPorts(false);

    }

    void SetInteractable(bool value)
    {
        //Select Buttons
        finger1select.interactable = value;
        finger2select.interactable = value;
        finger3select.interactable = value;
        finger4select.interactable = value;
        thumbselect.interactable = value;

        //Sliders
        finger1.interactable = value;
        finger2.interactable = value;
        finger3.interactable = value;
        finger4.interactable = value;
        thumb.interactable = value;
        
        //Config Buttons
        setLowEndstop.interactable = value;
        setHighEndstop.interactable = value;
        readCurrentPostion.interactable = value;
        reset.interactable = value;
    }

    void SetLow()
    {
        ranges[selectedFinger - 65].x = (int)sliders[selectedFinger].value;
        SendValue('F');
    }

    void SetHigh()
    {
        ranges[selectedFinger - 65].y = (int)sliders[selectedFinger].value;
        SendValue('G');
    }

    void ResetRanges()
    {
        ranges[selectedFinger - 65].x = 15;
        ranges[selectedFinger - 65].y = 244;
        SendValue('H');
    }

    void AdjustPulse(bool max, bool increase)
    {
        if(max)
        {
            if (increase)
            {
                SendValue('I');
            }
            else
            {
                SendValue('J');
            }
            sliders[selectedFinger].value = ranges[selectedFinger - 65].x;
        }
        else
        {
            if (increase)
            {
                SendValue('K');
            }
            else
            {
                SendValue('L');
            }
            sliders[selectedFinger].value = ranges[selectedFinger - 65].x;
        }
    }

    void SendValue(short value)
    {
        //if(debugMode)
        //{
        //    Debug.Log(BitConverter.GetBytes(value + 90)[0] + " " + BitConverter.GetBytes(value + 90)[1] + (byte)10);
        //}
        //else
        //{
        //    byte[] toSend = { BitConverter.GetBytes(value + 90)[0], BitConverter.GetBytes(value + 90)[1], (byte)10 };
        //    port.Write(toSend, 0, 3);
        //}
        if (debugMode)
        {
            Debug.Log(value);
        }
        else
        {
            byte[] toSend = { (byte)(value) };
            if(bluetoothMode)
            {
                bluetoothManager.sendData(toSend);
            }
            else
            {
                port.Write(toSend, 0, 1);
            }

            
        }
    }

    void SendValue(char character)
    {
        if(debugMode)
        {
            Debug.Log((int)character - 64 + " This is " + character);
        }
        else
        {
            byte[] toSend = { (byte)(character - 64) };
            if (bluetoothMode)
            {
                bluetoothManager.sendData(toSend);
            }
            else
            {
                port.Write(toSend, 0, 1);
            }
        }
    }

    private void OnApplicationQuit()
    {
        port.Close();
    }
}
