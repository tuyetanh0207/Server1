// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Server.h"
#include "afxsock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: code your application's behavior here.
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: code your application's behavior here.
            if (AfxSocketInit() == false) {
                cout << "Khong the khoi tao Socket Library";
                return false;
            }
            CSocket ServerSocket; // cha
            // Tao socket cho server, dang ky port la 1234,
            if (ServerSocket.Create(1234, SOCK_STREAM, NULL) == 0) //SOCK
            {
                cout << "Khoi tao that bai !!!" << endl;
                cout << ServerSocket.GetLastError();
                return false;
            }
            else {
                cout << "Server khoi tao thanh cong !!!" << endl;
                if (ServerSocket.Listen(1) == false) {
                    cout << "KHong the lang nghe port nay !!!\n";
                    ServerSocket.Close();
                    return false;
                }
            }
            CSocket Connector;
            // Khoi tao mot socket de duy tri viec ket noi va trao doi du lieu
            if (ServerSocket.Accept(Connector))
            {
                cout << "Da co Client ket noi" << endl << endl;
                char ServerMsg[100];
                int MsgSize;
                char* temp;
                do {
                    cout << "Server: ";
                    cin.getline(ServerMsg, 100);
                    MsgSize = strlen(ServerMsg);
                    // Gui di do dai thong diep de server biet duoc do dai
                    Connector.Send(&MsgSize, sizeof(MsgSize), 0);

                    // Gui di thong diep voi do dai la Magsize
                    Connector.Send(ServerMsg, MsgSize, 0);

                    // Nhan thong diep tu client 
                    Connector.Receive((char*)&MsgSize, sizeof(int), 0);
                    temp = new char[MsgSize + 1];
                    Connector.Receive((char*)temp, MsgSize, 0);

                    // In thong diep ra
                    temp[MsgSize] = '\0';
                    cout << "Client: " << temp << endl;
                    delete temp;

                } while (1);

            }
            Connector.Close();
            ServerSocket.Close();
        }
    }
    else
    {
        // TODO: change error code to suit your needs
        
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }

    return nRetCode;
}
