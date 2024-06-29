import pandas as pd
import tkinter as tk
from tkinter import filedialog, messagebox, ttk

class GradeSystem:
    def __init__(self, root):
        self.root = root
        self.root.geometry('1200x800')
        self.root.title('学生成绩核算系统')
        self.sta = tk.StringVar()
        #创建frame容器
        self.tree_frame = ttk.Frame(self.root)
        self.tree_frame.pack(fill='both', expand=1)
        
        # 创建表格
        self.my_tree = ttk.Treeview(self.tree_frame)
        self.my_tree.pack(side='left', fill='both', expand=1)

        # 添加滚动条
        self.my_scroll = ttk.Scrollbar(self.tree_frame)
        self.my_scroll.pack(side='right', fill='y')
        self.my_tree.config(yscrollcommand=self.my_scroll.set)
        self.my_scroll.config(command=self.my_tree.yview)

        # 创建新的 Frame
        self.bottom_frame = ttk.Frame(self.root)
        self.bottom_frame.pack(fill='both', expand=1)

        # 在新的 Frame 中添加一个 Label
        self.my_label = ttk.Label(self.bottom_frame, textvariable=self.sta, font=('等线', 24))
        self.my_label.pack()

        self.my_info_label = ttk.Label(self.bottom_frame, text='B21022515 李昭阳', font=('等线', 24))
        self.my_info_label.pack(pady=20)
        # 创建菜单栏
        self.my_menu = tk.Menu(self.root)
        self.root.config(menu=self.my_menu)

        # 添加菜单栏项目
        self.file_menu = tk.Menu(self.my_menu, tearoff=False)
        self.my_menu.add_cascade(label='文件', menu=self.file_menu)
        self.file_menu.add_command(label='打开', command=self.file_open)
        self.file_menu.add_command(label='保存', command=self.file_save)
        self.calculate_menu = tk.Menu(self.my_menu, tearoff=False)
        self.my_menu.add_cascade(label='计算', menu=self.calculate_menu)
        self.calculate_menu.add_command(label='计算成绩及等级', command=self.calculate_grade)
        self.calculate_menu.add_command(label='按成绩等级排序', command=self.sort_by_grade)
        self.info_menu = tk.Menu(self.my_menu, tearoff=False)
        self.my_menu.add_cascade(label='作者信息', menu=self.info_menu)
        self.info_menu.add_command(label='学号', command=self.info_id)
        self.info_menu.add_command(label='姓名', command=self.info_name)
        self.info = tk.Menu(self.my_menu, tearoff=False)
        self.my_menu.add_cascade(label='  B21022515 李昭阳', menu=self.info)

    #打开文件函数
    def file_open(self):
        self.filename = filedialog.askopenfilename(initialdir='/', title='Select a File', filetype=(('CSV Files', '*.csv'), ('All Files', '*.*')))

        if self.filename:
            self.df = pd.read_csv(self.filename)
            self.df['总评成绩'] = '无'
            self.df['成绩等级'] = '无'

            self.my_tree['column'] = list(self.df.columns)
            self.my_tree['show'] = 'headings'

            for column in self.my_tree['column']:
                self.my_tree.heading(column, text=column)

            self.update_treeview()
    #更新表格
    def update_treeview(self):
        for row in self.my_tree.get_children():
            self.my_tree.delete(row)

        self.df_rows = self.df.to_numpy().tolist()

        for row in self.df_rows:
            self.my_tree.insert('', 'end', values=row)
    #保存文件函数
    def file_save(self):
        self.filename = filedialog.asksaveasfilename(initialdir='/', title='Save File', filetype=(('CSV Files', '*.csv'), ('All Files', '*.*')))

        if self.filename:
            self.df.to_csv(self.filename, index=False)
    #计算成绩及等级
    def calculate_grade(self):
        if self.df is not None:
            self.df['总评成绩'] = round((self.df['平时成绩']*0.3 + self.df['期中考试成绩']*0.3 + self.df['期末考试成绩']*0.4), 2)
            self.df['成绩等级'] = pd.cut(self.df['总评成绩'], bins=[0, 60, 70, 80, 90, 100], labels=['不及格', '及格', '中', '良', '优'])
            self.count_specific_grades()
            self.update_treeview()
    def count_specific_grades(self):
        if self.df is not None:
            grade_counts = self.df['成绩等级'].value_counts()
        grade_string = (f'不及格:{grade_counts.get("不及格", 0)}人  '
                        f'及格:{grade_counts.get("及格", 0)}人  '
                        f'中:{grade_counts.get("中", 0)}人  '
                        f'良:{grade_counts.get("良", 0)}人  '
                        f'优:{grade_counts.get("优", 0)}人')
        self.sta.set(('各等级人数    {}'.format(grade_string)))


    #按成绩等级排序
    def sort_by_grade(self):
        if self.df is not None:
            self.df = self.df.sort_values(by='总评成绩')
            self.update_treeview()
    #作者信息
    def info_id(self):
        messagebox.showinfo('作者信息', '学号: B21022515')
    def info_name(self):
        messagebox.showinfo('作者信息', '姓名：李昭阳')    
if __name__ == '__main__':
    root = tk.Tk()
    gradesys = GradeSystem(root)
    root.mainloop()
