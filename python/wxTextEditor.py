import wx

class MyFrame(wx.Frame):
	def __init__(self,parent,title,x,y):
		wx.Frame.__init__(self, parent, title=title, size=(x,y))
		self.control = wx.TextCtrl(self, style=wx.TE_MULTILINE)
		self.Show(True)


app = wx.App(False)
frame = MyFrame(None, 'Small editor',200,200)
frame = MyFrame(None, 'Big editor',400,400)

app.MainLoop()

