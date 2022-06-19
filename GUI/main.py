from kivymd.app import MDApp
from kivy.lang import Builder
import plyer as pl

kivyFile = open("GUI\layout.kv","r")
layout = kivyFile.read()
kivyFile.close()

Notf = pl.notification

class Main(MDApp):

    def build(self):
        self.icon = "GUI/assets/appico.png"
        return Builder.load_string(layout)
        

    def text_Action(self):
        label = self.root.ids.Texto
        label.text = "Pulsaste el boton." 
        Notf.notify("Amongus", "A M O N G U S")
                
Main().run()