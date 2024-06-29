import tkinter as tk
from tkinter import Frame, Label, Menu, filedialog, messagebox, Text, simpledialog

class TextEditor:
    def __init__(self, root):
        self.root = root
        self.root.title('文本编辑器')
        self.root.geometry('800x600')

        # 创建一个 Frame，用于放置文本区域
        self.text_frame = Frame(self.root)
        self.text_frame.pack(side='left', fill='both', expand=1)

        self.text_area = Text(self.text_frame, undo=True)
        self.text_area.pack(fill='both', expand=1)

        # 在右侧创建一个新的 Frame
        self.right_frame = Frame(self.root)
        self.right_frame.pack(side='right', fill='both')

        # 在右侧的 Frame 中添加一个标签，作为示例
        self.right_label = Label(self.right_frame, text="作者信息：\n\n B21022515  \n\n李昭阳", font=("等线", 24))
        self.right_label.pack()

        self.main_menu = Menu()
        self.root.config(menu=self.main_menu)

        # 文件菜单
        self.file_menu = tk.Menu(self.main_menu, tearoff=False)
        self.main_menu.add_cascade(label='文件', menu=self.file_menu)
        self.file_menu.add_command(label='打开', command=self.open_file)
        self.file_menu.add_command(label='保存', command=self.save_file)

        # 编辑菜单
        self.edit_menu = tk.Menu(self.main_menu, tearoff=False)
        self.main_menu.add_cascade(label='编辑', menu=self.edit_menu)
        self.edit_menu.add_command(label='插入文本', command=self.insert_text)
        self.edit_menu.add_command(label='删除文本', command=self.delete_text)
        self.edit_menu.add_command(label='查找文本', command=self.find_text)
        self.edit_menu.add_command(label='清除查找内容', command=self.clear_text)
        self.edit_menu.add_command(label='替换文本', command=self.replace_text)

        self.info_menu = tk.Menu(self.main_menu, tearoff=False)
        self.main_menu.add_cascade(label='作者信息', menu=self.info_menu)
        self.info_menu.add_command(label='学号', command=self.info_id)
        self.info_menu.add_command(label='姓名', command=self.info_name)

        self.info = tk.Menu(self.main_menu, tearoff=False)
        self.main_menu.add_cascade(label=' B21022515 李昭阳', menu=self.info)
        
    #打开文件函数
    def open_file(self):
        self.file_path = filedialog.askopenfilename(defaultextension='.txt', filetypes=[('Text Files', '*.txt'), ('All Files', '*.*')])
        if self.file_path:
            self.text_area.delete(1.0, tk.END)
            with open(self.file_path, 'r', encoding='utf-8') as file:
                self.text_area.insert(tk.INSERT, file.read())

    #关闭文件函数
    def save_file(self):
        self.file_path = filedialog.asksaveasfilename(defaultextension='.txt', filetypes=[('Text Files', '*.txt'), ('All Files', '*.*')])
        if self.file_path:
            with open(self.file_path, 'w', encoding='utf-8') as file:
                file.write(self.text_area.get(1.0, tk.END))

    #插入文本函数
    def insert_text(self):
        self.insert_text = simpledialog.askstring("插入文本", "输入文本：")
        self.text_area.insert(tk.INSERT, self.insert_text)

    #删除文本函数
    def delete_text(self):
        if messagebox.askyesno('删除文本', '你确定要删除选定的文本吗？'):
            try:
                start = self.text_area.index('sel.first')
                end = self.text_area.index('sel.last')
                self.text_area.delete(start, end)
            except tk.TclError:
                messagebox.showerror('删除文本', '没有选定的文本')

    #查找文本函数
    def find_text(self):
        self.find_text = simpledialog.askstring("查找文本", "输入文本：")
        self.text_start = '1.0'
        while True:
            self.text_start = self.text_area.search(self.find_text, self.text_start, stopindex=tk.END)
            if not self.text_start:
                break
            self.text_end = f'{self.text_start.split(".")[0]}.{int(self.text_start.split(".")[1])+len(self.find_text)}'
            self.text_area.tag_add('found', self.text_start, self.text_end)
            self.text_area.tag_config('found', foreground='red')
            self.text_start = self.text_end  
    #清除搜索到的文本
    def clear_text(self):
        self.text_area.tag_config('found', foreground='black')

    #替换文本函数
    def replace_text(self):
        self.find_text = simpledialog.askstring("替换文本", "查找文本：")
        
        replace_window = tk.Toplevel(self.root)
        replace_window.title('替换文本')
        
        replace_label = tk.Label(replace_window, text="替换为：")
        replace_label.pack()
        
        replace_entry = tk.Entry(replace_window)
        replace_entry.pack()
        
        def replace_text_action():
            replace_text = replace_entry.get()
            self.text_content = self.text_area.get(1.0, tk.END)
            self.text_content = self.text_content.replace(self.find_text, replace_text)
            self.text_area.delete(1.0, tk.END)
            self.text_area.insert(tk.INSERT, self.text_content)
            replace_window.destroy()
        
        replace_button = tk.Button(replace_window, text="替换", command=replace_text_action)
        replace_button.pack()
        
        replace_window.geometry(f"+{self.root.winfo_rootx() + 50}+{self.root.winfo_rooty() + 50}")
        
        replace_entry.focus_set()


    #作者信息函数
    def info_id(self):
        messagebox.showinfo('作者信息', '学号: B21022515')

    def info_name(self):
        messagebox.showinfo('作者信息', '姓名：李昭阳')   

if __name__ == '__main__':
    root = tk.Tk()
    te = TextEditor(root)
    root.mainloop()
