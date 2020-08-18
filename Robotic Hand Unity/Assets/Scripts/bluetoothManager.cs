using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using ArduinoBluetoothAPI;
using System;

public class bluetoothManager : MonoBehaviour
{
    private BluetoothHelper helper;
    SerialMonitor serialMonitor;
    private bool isScanning;
    private bool isConnecting;

    private string data;

    private string msg;

    private LinkedList<BluetoothDevice> devices;

    private void Awake()
    {
        serialMonitor = GetComponent<SerialMonitor>();
    }
    // Start is called before the first frame update
    void Start()
    {
        data = "";
        msg = "";
        try
        {
            BluetoothHelper.BLE = true;
            helper = BluetoothHelper.GetInstance();
            helper.OnConnected += OnConnected;
            helper.OnConnectionFailed += OnConnectionFailed;
            helper.OnScanEnded += OnScanEnded;
            helper.OnDataReceived += OnDataReceived;

            helper.setTerminatorBasedStream("\0"); //every messages ends with new line character


        }
        catch (Exception)
        {
            Debug.Log("Bluetooth Init Failed");
        }
    }

    public void Scan()
    {
        isScanning = helper.ScanNearbyDevices();
    }

    public void ConnectToBluetooth(string name)
    {
        helper.setDeviceName(name);
        try
        {
            helper.Connect();
            isConnecting = true;
        }
        catch (Exception)
        {
            isConnecting = false;
        }
    }

    public void sendData(byte[] dataToSend)
    {
        byte[] arr = { dataToSend[0], dataToSend[0] };
        helper.SendData(arr);

    }


    void OnDataReceived()
    {
        data += "\n<" + helper.Read();
    }

    void OnScanEnded(LinkedList<BluetoothDevice> devices)
    {
        this.isScanning = false;
        this.devices = devices;
        serialMonitor.SetPortOptions(devices);
    }

    void OnConnected()
    {
        isConnecting = false;
        Debug.Log("Connection Success");
        serialMonitor.OnBTConnection();
    }

    void OnConnectionFailed()
    {
        isConnecting = false;
        Debug.Log("Connection Failure");
        serialMonitor.OnBTFailedConnection();

    }
   
    void OnDestroy()
    {
        if (helper != null)
            helper.Disconnect();
    }
    private void OnApplicationQuit()
    {
        if(helper != null)
            helper.Disconnect();
    }
}
