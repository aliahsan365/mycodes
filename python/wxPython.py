import wx
 
app = wx.App(False)  # Create a new app, don't redirect stdout/stderr to a window.
#frame = window (la instancia de la ventana en si)
#window es la clase de la cual todos los elementos visuales heredan
frame = wx.Frame(None, wx.ID_ANY, "Hello World") # A Frame is a top-level window.
frame.Show(True)     # Show the frame.
app.MainLoop()