import tkinter as tk
from tkinter import messagebox
import random
import string

class TypingProgram:

    def __init__(self, root):
        self.root = root
        self.root.title('打字程序')
        self.root.geometry('800x800')

        #用StringVar类对GUI中的文本信息初始化
        self.begin_text = tk.StringVar()
        self.length_text = tk.StringVar()
        self.label_text = tk.StringVar()
        self.entry_text = tk.StringVar()
        self.accuracy_text = tk.StringVar()
        self.success_text = tk.StringVar()
        self.info_bottom_text = tk.StringVar()

        #创建信息栏到界面顶部菜单栏
        self.main_menu = tk.Menu()
        self.root.config(menu=self.main_menu)

        #创建一级菜单和二级菜单选项
        self.info_menu = tk.Menu(self.main_menu, tearoff=False)
        self.main_menu.add_cascade(label='作者信息', menu=self.info_menu)
        self.info_menu.add_command(label='学号', command=self.info_id)
        self.info_menu.add_command(label='姓名', command=self.info_name)

        #self.generate_string()

        #以下为GUI主界面的各部分设计
        #开始提示栏
        self.begin_text.set('请输入生成字符长度')
        self.begin = tk.Label(root, textvariable=self.begin_text, font=('等线', 24))
        self.begin.pack(pady=20)

        self.length = tk.Entry(root, textvariable=self.length_text, font=('等线', 24), width=10)
        self.length.pack(pady=20)
        #开始按钮
        self.start_button = tk.Button(root, text='开始', command=self.generate_string, font=('等线', 24))
        self.start_button.pack(pady=20)
        #随机字符栏
        self.label = tk.Label(root, textvariable=self.label_text, font=('等线', 24))
        self.label.pack(pady=20)
        #输入框
        self.entry = tk.Entry(root, textvariable=self.entry_text, font=('等线', 24), width=50)
        self.entry.pack(pady=20)
        #检查按钮
        self.button = tk.Button(root, text='检查', command=self.check_accuracy, font=('等线', 24))
        self.button.pack(pady=20)
        #正确率栏
        self.accuracy_label = tk.Label(root, textvariable=self.accuracy_text, font=('等线', 24))
        self.accuracy_label.pack(pady=20)
        #正确与否栏
        self.success_label = tk.Label(root, textvariable=self.success_text, font=('等线', 24))
        self.success_label.pack(pady=20)
        #作者信息栏
        self.info_bottom_text.set('B21022515 李昭阳')
        self.info_bottom = tk.Label(root, textvariable=self.info_bottom_text, font=('等线', 24))
        self.info_bottom.pack(pady=20)

    #生成随机字符串
    def generate_string(self):
        length = self.get_number()#random.randint(5, 15)
        self.random_string = ''.join(random.choices(string.ascii_letters + string.digits, k=length))
        self.label_text.set(self.random_string)
        self.entry_text.set('')
        self.accuracy_text.set('')
        self.success_text.set('')


    def get_number(self):
        try:
            number = int(self.length_text.get())
            print(f"获取的数字是：{number}")
            return number
        except ValueError:
            print("输入的不是有效的整数")
    #检查输入的字符串是否正确及正确率
    def check_accuracy(self):
        input_string = self.entry_text.get()
        edit_distance = self.min_edit_distance(self.random_string, input_string)
        accuracy = (len(self.random_string) - edit_distance) / len(self.random_string) * 100
        self.accuracy_text.set(f'正确率: {accuracy:.2f}%')
        if accuracy == 100:
            self.success_text.set('正确')
        else:
            self.success_text.set('错误')
        #self.generate_string()

    #最小编辑距离计算
    def min_edit_distance(self, s1, s2):
        m, n = len(s1), len(s2)
        dp = [[0 for _ in range(n+1)] for _ in range(m+1)]

        for i in range(m+1):
            dp[i][0] = i
        for j in range(n+1):
            dp[0][j] = j

        for i in range(1, m+1):
            for j in range(1, n+1):
                if s1[i-1] == s2[j-1]:
                    dp[i][j] = dp[i-1][j-1]
                else:
                    dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1

        return dp[m][n]

    #显示作者信息响应函数
    def info_id(self):
        messagebox.showinfo('作者信息', '学号: B21022515')
    def info_name(self):
        messagebox.showinfo('作者信息', '姓名：李昭阳')   

if __name__ == '__main__':
    root = tk.Tk()
    tp = TypingProgram(root)
    root.mainloop()
