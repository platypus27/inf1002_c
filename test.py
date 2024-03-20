import pyautogui
import pygetwindow as gw

def get_cmd():
    cmd_windows = gw.getWindowsWithTitle('Command Prompt')
    return cmd_windows[0] if cmd_windows else None

cmd = get_cmd()
if cmd:
    cmd.activate()
else:
    print("No Command Prompt found")

def on_button_click():
    pyautogui.typewrite("a.exe" + '\n')
    pyautogui.typewrite("test" + '\n')
    pyautogui.typewrite("2" + '\n')
    pyautogui.typewrite("cat" + '\n')
    pyautogui.typewrite("500" + '\n')
    pyautogui.typewrite("dog" + '\n')
    pyautogui.typewrite("1000" + '\n')
    pyautogui.typewrite("count" + '\n')
    pyautogui.typewrite("a" + '\n')
    print("Fire in the hole!!!")
    
on_button_click()